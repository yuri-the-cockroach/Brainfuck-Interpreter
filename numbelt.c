#ifndef NUMBELT
#define NUMBELT

#include <stdlib.h>

struct numbelt{
    int value;
    struct numbelt * next;
    struct numbelt * prev;
    int pos;
} typedef numbelt; 

// numbelt functions
numbelt * initNum() {
    numbelt *new_belt = (numbelt*)malloc(sizeof(numbelt));
    new_belt->value = 0;
    new_belt->next = 0;
    new_belt->prev = 0;
    new_belt->pos = 0;
    return new_belt;
}

// Gets the next number in the belt
// If it's not instanciated, creates and instanciats it
// The next number is guaranteed to be returned
// The only purpose of this function it to make sure, that the next number exists
numbelt * getRight(numbelt * cur_number) {
    if ( cur_number->next == 0 ) {
        numbelt *new_number = initNum();
        new_number->pos = cur_number->pos + 1;
        new_number->prev = cur_number;
        cur_number->next = new_number;
    }
    return cur_number->next;
}

// Same as above, but for prev number
// Mostly to be sure
numbelt * getLeft(numbelt * cur_number) {
    if ( cur_number->prev == 0 ) {
        numbelt *new_number = initNum();
        new_number->pos = cur_number->pos - 1;
        new_number->next = cur_number;
        cur_number->prev = new_number;
    }
    return cur_number->prev;
}

// Redundend, but for the sake of completeness it will stay
void incNum(numbelt * cur_number) {
    cur_number->value++;
}

// Same as above
void decNum(numbelt * cur_number) {
    cur_number->value--;
}

// Gets the current number
// Exists for the sake of completeness
int fetchNum(numbelt * cur_number) {
    return cur_number->value;
}

// Sets the current number to new_value
void setNum(numbelt * cur_number, int new_value) {
    cur_number->value = new_value;
}

#endif
