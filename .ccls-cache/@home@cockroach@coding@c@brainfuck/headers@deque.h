#ifndef DEQUE_H
#define DEQUE_H
#include <stdlib.h>

// Deque structure. First in last out. Allways call deque_create to create new deque. deque.size on a new deque must be 0, otherwise behavior will be undefined
struct deque {
    uint size;
    uint * deque;
} typedef deque;

// Creates a new deque and returns it
deque deque_create();

// Expands deque by one element. Returns 0 if successful, ENOMEM If realloc returned a NULL pointer
int deque_expand(deque * dq);

// Shrink deque by one element. Returns 0 if successful, ENOMEM If realloc returned a NULL pointer
int deque_shrink(deque * dq);

// Push an element to the deque
int deque_push(deque * dq, uint what);

// Pulls the first element in the deque
// Allways check perror befor using the return value
// Panics with -1 if deque_shrink didn't return 0
int deque_pull(deque * dq);

#endif
