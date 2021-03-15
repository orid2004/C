// Source code for dtype
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "include/dtype.h"
#include "include/exceptions.h"
#include "include/settings.h"

// defines
#define RESET "\033[0m"

Array* array(int n_args, ...) {
    // Created and returns an array object
    Array *a = malloc(sizeof(Array)); // allocate memory for struct
    int shape[n_args], hasZero = 0; // create shape array
    va_list ap;
    va_start(ap, n_args);
    for (int i = 0; i < n_args; i++) {
        shape[i] = va_arg(ap, int); // insert args into shape array
        if (shape[i] == 0) hasZero = 1; // update hasZero flag
    }
    va_end(ap);
    if (hasZero) {
        // Create an empty array without initialization
        a->size = 0;
        a->length = 0;
    }
    else if (n_args > 0 && !hasZero) array_init(a, n_args, shape); // allocate memory for integers
    return a;
}

void array_init(Array *a, int n_args, int shape[]) {
    // Allocate memory to integers
    int size = 0, count = 1;
    for (int i = 0; i < n_args; i++) {
        count *= shape[i]; // count number of elements
        a->shape[size] = shape[i]; // update array shapep
        if (shape[i] <= 0) {
            // Raise index error
            char ex[64];
            snprintf(ex, sizeof(ex), "value %i at index %i", shape[i], size);
            raise(INVALID_SHAPE, ex);
        }
        size++;
    }
    a->size = size; // update array size (number of dimensions)
    a->carr = malloc(sizeof(int) * count); // allocate memory;
    a->length = count; // update array length ()
}

int array_posToIndex__(Array *a, int *pos) {
    // Convert array position to index
    int index = 0, block_size;
    for (int i = 0; i < a->size; i++) {
        if (pos[i] >= a->shape[i]) raise(INDEX_ERROR, "");  // raise index error
        block_size = 1; // elements to take into account
        for (int j = i+1; j < a->size; j++) block_size *= a->shape[j]; // count elements
        index += block_size * pos[i]; // add to index
    }
    return index;
}

void array_(Array *a, ...) {
    // Set a value at a[i, j, k, ...]
    va_list ap;
    va_start(ap, a->size);
    int *shape = malloc(a->size * sizeof(int)); // create a shape array
    for (int i = 0; i < a->size; i++) shape[i] = va_arg(ap, int); // insert args to shape array
    int index = array_posToIndex__(a, shape); // convert position to index [0, length - 1]
    if (index < a->length) a->carr[index] = va_arg(ap, int); // set the element to last arg (value)
    else raise(INDEX_ERROR, ""); // raise index error
    va_end(ap);
}


int array_at(Array *a, ...) {
    // Return the [i'th, j'th, k'th, ...] element of array
    va_list ap;
    va_start(ap, a->size);
    int index, *shape = malloc(a->size * sizeof(int)); // create a shape array
    for (int i = 0; i < a->size; i++) shape[i] = va_arg(ap, int); // insert args to shape array
    index = array_posToIndex__(a, shape); // convert position to index
    if (index >= a->length) raise(INDEX_ERROR, ""); // raise index error
    return a->carr[index]; // return the element
    va_end(ap);
}

void array_reshape(Array *a, int n_args, ...) {
    // Reshape an array
    // The values (or some of them) are copied to the new array
    va_list ap;
    int shape[n_args], hasZero = 0; // create a shape array
    va_start(ap, n_args);
    for (int i = 0; i < n_args; i++) {
        shape[i] = va_arg(ap, int); // insert args to shape array
        if (shape[i] == 0) hasZero = 1; // update hasZero flag
    }
    int *save = malloc(sizeof(int) * a->length), old_size = a->length; // create a backup array
    memcpy(save, a->carr, sizeof(int) * a->length); // copy the elements to backup array
    free(a->carr); // free the data
    if (hasZero) {
        // Create a new empty array
        a->size = 0;
        a->length = 0;
    }
    else array_init(a, n_args, shape); // allocate new memory
    memcpy(a->carr, save, sizeof(int) * old_size); // copy the old values (or some of them) to the new array
    va_end(ap);
}


int array_replace(Array *a, int old, int new) {
    // Replace an integer with another
    // Return -1 if hasn't find old
    for (int i = 0; i < a->length; i++) {
        if (a->carr[i] == old) {
            a->carr[i] = new;
            return 0;
        }
    }
    return -1;
}

void array_replaceAll(Array *a, int old, int new) {
    // Replace (all) integer with another
     while (array_replace(a, old, new) == 0);
}

Array* array_copyof(Array *a) {
    // Create a copy of array
    Array *new = malloc(sizeof(Array)); // new array object
    int shape[a->size]; // create a shape array
    memcpy(shape, a->shape, sizeof(int) * a->size); // clone the shape
    array_init(new, a->size, shape); // allocate memory
    memcpy(new->carr, a->carr, sizeof(int) * a->length); // clone the data
    return new;
}


void array_print(Array *a) {
    // Print an array
    int *pos = malloc(sizeof(int) * a->size);
    printf("{ ");
    array_print__(a, pos, 0);
    printf(" }\n");
}

void array_print__(Array *a, int *pos, int d) {
    // Recursive private function to print an array
    if (d == a->size -1) {
        // Final depth is reached
        for (int i = 0; i < a->shape[d]; i++) {
            // Update shape array and print the elements
            pos[d] = i;
            printf("%i, ", a->carr[array_posToIndex__(a, pos)]);
        }
        printf("\b\b");
    } else {
        char color[16];
        snprintf(color, sizeof(color), "\x1b[%im", 31 + d);
        for (int i = 0; i < a->shape[d]; i++) {
            // Print each array in another depth
            printf("%s[%s ", color, RESET);
            pos[d] = i; // Update shape array according to depth
            array_print__(a, pos, d + 1); // Print the sub-array
            printf(" %s]%s", color, RESET);
        }
    }
}

void array_free(Array *a) { free(a->carr); } // Free array data

Dict* dict() {
    // Create and return a dict object
    Dict *d = malloc(sizeof(Dict)); // allocate struct
    d->size = 0; // set size to 0
    return d;
}

void dict_(Dict *d, int n_pairs, ...) {
    // Insert pairs of data into a dict
    if (n_pairs > 0) {
        va_list ap;
        va_start(ap, n_pairs * 2); // Read function arguments
        int key, value;
        for (int i = 0; i < n_pairs; i++) {
            key = va_arg(ap, int); // key arg
            value = va_arg(ap, int); // value arg
            dict_set(d, key, value); // set the value
        }
        va_end(ap);
    }
}

void dict_set(Dict *d, int key, int value) {
    // Set a dict value
    for (int i = 0; i < d->size * 2; i += 2) {
        if (d->data[i] == key) {
            d->data[i + 1] = value; // Change an existing key
            return;
        }
    }
    int *save = malloc(sizeof(int) * d->size * 2);  // create a backup array
    memcpy(save, d->data, sizeof(int) * d->size * 2); // copy the elements
    free(d->data); // free the data
    d->data = malloc(sizeof(int) * (d->size + 1) * 2); // add new memory
    memcpy(d->data, save, sizeof(int) * d->size * 2); // load back the data
    d->data[d->size * 2] = key; // save the key
    d->data[d->size * 2 + 1] = value; // save the value
    d->size++;
}

int dict_valueof(Dict *d, int key) {
    // Return the value of key
    for (int i = 0; i < d->size * 2; i+=2) {
        if (d->data[i] == key) return d->data[i + 1]; // Search for a key
    }
    // Otherwise raise an index error
    char ex[32];
    snprintf(ex, sizeof(ex), "key %i not found", key);
    raise(INDEX_ERROR, ex);
}

int dict_delkey(Dict *d, int key) {
    // Delete a key from a dicy
    for (int i = 0; i < d->size * 2; i += 2) {
        if (d->data[i] == key) { // Search for the key
            int value = d->data[i + 1]; // Save the value before overwriting
            for (int j = i; j < (d->size - 1) * 2; j += 2) {
                // Shrink the array accordingly
                d->data[j] = d->data[j + 2];
                d->data[j + 1] = d->data[j + 3];
            }
            d->size--; // decrease the size
            return value; // return the value
        }
    }
    // Otherwise raise an index error
    char ex[32];
    snprintf(ex, sizeof(ex), "key %i", key);
    raise(INDEX_ERROR, ex);
}

int dict_isEmpty(Dict *d) { return (d->size == 0); }


Dict* dict_mergeof(int n_args, ...) {
    // Merge dictionaries and return the new dict_
    va_list ap;
    va_start(ap, n_args);
    Dict *new = dict(), *d; // create a new dict and a pointer
    Array *keys = array(1, 1), *values = array(1, 1); // create a keys and values arrays
    for (int i = 0; i < n_args; i++) {
        d = va_arg(ap, Dict*); // Set next dict to copy
        array_reshape(keys, 1, d->size); // reshape the keys array
        array_reshape(values, 1, d->size); // reshape the values array
        dict_keys(d, keys->carr); // copy the keys
        dict_values(d, values->carr); // copy the values
        for (int j = 0; j < d->size; j++) dict_set(new, array_at(keys, j), array_at(values, j)); // Paste the values into new dict
    }
    va_end(ap);
    return new;
}

void dict_keys(Dict *d, int buffer[]) {
    // Copy keys to a buffer
    for (int i = 0; i < d->size * 2; i += 2) buffer[i / 2] = d->data[i];
}
void dict_values(Dict *d, int buffer[]) {
    // Copy values to a buffer
    for (int i = 1; i < d->size * 2; i += 2) buffer[i / 2] = d->data[i];
}

void dict_print(Dict *d) {
    // Print a dictionary
    if (d->size > 0) {
        printf("{ ");
        for (int i = 0; i < d->size * 2; i += 2) {
            printf("[%i: %i] ", d->data[i], d->data[i+1]);
        }
        printf("}\n");
    }
    else printf("Empty Dict at %p\n", d);
}

void dict_free(Dict *d) { free(d->data); } // Free a dict


Stack* stack() {
    // Create and return a new stack
    Stack *s = malloc(sizeof(Stack)); // allocate struct
    s->data = array(1, 0); // set data to an empty array
    return s;
}

int stack_head(Stack *s) {
    // Return the head of a stack if not empty
    if (s->data->size < 1) raise(INDEX_ERROR, "stack is empty");
    return array_at(s->data, s->data->shape[0] - 1);
}

void stack_push(Stack *s, int x) {
    // Push a value to a stack
    array_reshape(s->data, 1, s->data->shape[0] + 1); // reshape the data
    array_(s->data, s->data->shape[0] - 1, x); // save the integer
}

int stack_pop(Stack *s) {
    // Pop a value from a struct
    if (s->data->shape[0] < 1) raise(INDEX_ERROR, "stack is empty"); // raise an index error if empty
    int x = array_at(s->data, s->data->shape[0] - 1); // save the head
    array_reshape(s->data, 1, s->data->shape[0] - 1); // reshape the data, size decreased by 1
    return x; // return the value
}

int stack_isEmpty(Stack *s) { return s->data->size == 0; } // Check if a stack is empty

void stack_free(Stack *s) { array_free(s->data); }

Queue* queue() {
    // Create and return a new queue
    Queue *q = malloc(sizeof(Queue)); // cllocate struct
    q->data = array(1, 0); // create an empty data array
    return q;
}

int queue_head(Queue *q) { return array_at(q->data, 0); }

void queue_enqueue(Queue *q, int x) {
    // Enqueue a value
    array_reshape(q->data, 1, q->data->shape[0] + 1); // reshape the data array
    array_(q->data, q->data->shape[0] - 1, x); // set the last value
}

int queue_dequeue(Queue *q) {
    // Dequeue a value
    if (q->data->shape[0] < 1) raise(INDEX_ERROR, "queue is empty"); // raise an index error if empty
    int x = array_at(q->data, 0); // Save the head
    for (int i = 0; i < q->data->shape[0] - 1; i++) {
        array_(q->data, i, array_at(q->data, i + 1)); // shrink the queue
    }
    array_reshape(q->data, 1, q->data->shape[0] - 1); // reshape accordingly
    return x; // return the head
}

int queue_isEmpty(Queue *q) { return q->data->size == 0; } // Check if a queue is empty

void queue_free(Queue *q) { array_free(q->data); } // Free a queue
