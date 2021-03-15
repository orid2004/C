// Header file for dtype
#include "settings.h"

typedef struct Array {
    int shape[MAX_D];
    int size;
    int length;
    int *carr;
} Array;

typedef struct Dict {
    int *data, size;
} Dict;

typedef struct Stack {
    Array *data;
} Stack;

typedef struct Queue {
    Array *data;
}  Queue'

Array* array(int n_args, ...);
void array_init(Array *a, int n_args, int shape[]);
int array_posToIndex__(Array *a, int *pos);
void array_(Array *a, ...);
int array_at(Array *a, ...);
void array_reshape(Array *a, int n_args, ...);
int array_replace(Array *a, int old, int new);
void array_replaceAll(Array *a, int old, int new);
Array* array_copyof(Array *a);
void array_print(Array *a);
void array_print__(Array *a, int *pos, int d);
void array_free(Array *a);

Dict* dict();
void dict_(Dict *d, int n_pairs, ...);
void dict_set(Dict *d, int key, int value);
int dict_valueof(Dict *d, int key);
int dict_delkey(Dict *d, int key);
int dict_isEmpty(Dict *d);
Dict* dict_mergeof(int n_args, ...);
void dict_keys(Dict *d, int buffer[]);
void dict_values(Dict *d, int buffer[]);
void dict_print(Dict *d);
void dict_free(Dict *d);

Stack* stack();
int stack_head(Stack *s);
void stack_push(Stack *s, int x);
int stack_pop(Stack *s);
int stack_isEmpty(Stack *s);
void stack_free(Stack *s);

Queue* queue();
int queue_head(Queue *q);
void queue_enqueue(Queue *q, int x);
int queue_dequeue(Queue *q);
int queue_isEmpty(Queue *q);
void queue_free(Queue *q);
