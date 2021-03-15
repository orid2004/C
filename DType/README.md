# DType

Advanced integer data types to use for data management while programming applications in C. The data types were implemented with integers, but the project can constitute a proof of concept for generic data types.

## Langauge
C

## Date
Mar 2021

## Description
The following data types are implemented:
* N-dimensional Array
* Dict
* Stack
* Queue

## Usage

```
Array* array(int n_args, ...);
// Creates and returns an array object
// Example: array(3, 10, 10, 10) for a 10x10x10 matrix

void array_init(Array *a, int n_args, int shape[]);
// Allocates memory for integers
// Example: array_init(a, 3, shape) for a 10x10x10 matrix

int array_posToIndex__(Array *a, int *pos);
// Converts array position to index
// Example: array_posToIndex(a, pos) where pos is a 1-D shape array

void array_(Array *a, ...);
// Sets a value at a[i, j, k, ...]
// For example: array_(a, 1, 5, 9) for a 3-D array

int array_at(Array *a, ...);
// Returns the value at a certain position
// Example: array_at(a, 1, 5, 9)

void array_reshape(Array *a, int n_args, ...);
// Reshapes an array
// Example: array_reshape(a, 4, 20, 20, 20, 20) for a 20x20x20x20 matrix

int array_replace(Array *a, int old, int new);
// Replaces a value
// Example: array_replace(a, 10, 20)

void array_replaceAll(Array *a, int old, int new);
// Replaces all appearances of an integer
// Example: array_replaceAll(a, 10, 20)

Array* array_copyof(Array *a);
// Creates a copy of an array
// Example: Array *b = array_copyof(a)

void array_print(Array *a);
// Prints an array
// Example: array_print(a)

void array_print__(Array *a, int *pos, int d);
// A recursive private function to print an array
// Example: array_print__(a, pos, 0) to print an entire array (from depth 0)

void array_free(Array *a);
// Free an array
// Example: array_free(a)
```

```
Dict* dict();
// Creates and returns a dict
// Example: Dict *d = dict()

void dict_(Dict *d, int n_pairs, ...);
// Insert pairs of data into a dict
// Example: dict_(d, 3, 10, 20, 100, 200, 1000, 2000)

void dict_set(Dict *d, int key, int value);
// Add a new key / overwrite a value
// Example: dict_set(d, 10, 20)

int dict_valueof(Dict *d, int key);
// Returns the value of a key
// Example: dict_valueof(d, 10)

int dict_delkey(Dict *d, int key);
// Deletes a key from a dict
// Example: dict_delkey(d, 10)

int dict_isEmpty(Dict *d);
// Returns true of a dict is empty
// Example: dict_isEmpty(d)

Dict* dict_mergeof(int n_args, ...);
// Merges N dictionaries and returns the new dict
// Example: Dict *m = dict_mergaof(4, d1, d2, d3, d4)

void dict_keys(Dict *d, int buffer[]);
// Copies all keys into a buffer
// Example: dict_keys(d, keys)

void dict_values(Dict *d, int buffer[]);
// Copies all values into a buffer
// Example: dict_values(d, values)

void dict_print(Dict *d);
// Prints a dict
// Example: dict_print(d)

void dict_free(Dict *d);
// Free a dict
// Example: dict_free(d)
```

```
Stack* stack();
// Creates and returns a new stack
// Example: Stack *s = stack()

int stack_head(Stack *s);
// Returns the head of a stack, if not empty
// Example: stack_head(s)

void stack_push(Stack *s, int x);
// Push a value to a stack
// Example: stack_push(s, 10)

int stack_pop(Stack *s);
// Pop a value from a stuck, if not empty
// Example: stack_pop(s)

int stack_isEmpty(Stack *s);
// Returns true if a stack is empty
// Example: if(stack_isEmpty(s))

void stack_free(Stack *s);
// Free a stack
// Example: stack_free(s)
```

```
Queue* queue();
// Creates and returns a new queue
// Example: Queue *q = queue()

int queue_head(Queue *q);
// Returns the head of a queue, if not empty
// Example; queue_head(q)

void queue_enqueue(Queue *q, int x);
// Enqueue into a queue
// Example: queue_enqueue(q, 10)

int queue_dequeue(Queue *q);
// Dequeue from a queue
// Example: queue_dequeue(q)

int queue_isEmpty(Queue *q);
// Returns true if a queue is empty
// Example: queue_isEmpty(q)

void queue_free(Queue *q);
// Free a queue
// Example: queue_free(q)
```