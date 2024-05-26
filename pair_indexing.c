
#ifndef DYNSTR_H
#define DYNSTR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// The dynamic string structure

struct uint_pair {
    uint key;
    uint value;
} typedef uint_pair;


// Append a value to the end of the string while handelling (hopefully) all of the edge cases
int indexAppend(uint_pair * index_ptr, uint_pair the_pair) {


    return 0; // Hopefully successful
}

#endif
