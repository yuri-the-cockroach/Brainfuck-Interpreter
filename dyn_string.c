#ifndef DYNSTR_H
#define DYNSTR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

// The dynamic string structure
struct string {
    bool read_only;
    char * char_ptr;
    size_t len; // Number of characters in the string 
    size_t chunk_size; // The size by which to grow the string if needed
    size_t alloced_size; // Real size that the string has
} typedef string;

// string functions

// Returnes a new string consisting of chunk_size, initialized with 0, bytes
string initString(size_t chunk_size) {

    // Instanciate everything

    string to_return; // The struct that will be returned
    to_return.read_only = false;
    to_return.chunk_size = chunk_size; // Set the chunk_size
    to_return.char_ptr = calloc(chunk_size, sizeof(char)); // Allocate the char array and instanciate it in place

    // Check if allocation was successful.
    // If not, panic and terminate
    if ( !to_return.char_ptr ) {
        errno = EFAULT;
        perror("malloc returned a null pointer in initString function");
        exit(errno);
    }

    // Assuming, that everything went well
    to_return.alloced_size = chunk_size; // Set the real size
    to_return.len = 0; // Instanciate the length (yeah, no shit)

    return to_return;
}

// This function will grow the string by string.chunk_size
// and update the string.alloced_size is successful
// If an error occured in allocation, it panics and terminates the program
int growString(string * the_string) {
    // Tries to reallocate the string so it is bigger by chunk_size chars that it was
    the_string->char_ptr = realloc(the_string->char_ptr, sizeof(char) * ( the_string->alloced_size + the_string->chunk_size ) );
    // Check if realloc didn't return NULL
    if ( !the_string->char_ptr ) {
        // If it did, panic and terminate
        errno = EFAULT;
        perror("malloc returned a null pointer in growString function");
        exit(errno);
    }

    // Instanciate all new allocated chars to \0
    for (int i = the_string->alloced_size; i < the_string->alloced_size + the_string->chunk_size; i++) {
        the_string->char_ptr[i] = 0;
    }

    // Finally update the allocated(real) size of the string and return
    the_string->alloced_size += the_string->chunk_size;
    return 0; // if everything was successful
}

// Append a value to the end of the string while handelling (hopefully) all of the edge cases
int stringAppend(string * the_string, char what) {

    // Make sure that the length of the string is not bigger
    // than it's allocated size.
    // If it is, it means that there is an error in counting either
    // This is critical, so it exists with error
    if (the_string->len > the_string->alloced_size) {
        errno = ERANGE;
        perror(
                "String length is more than it's allocated space which resulted in panic. Terminating now."
              );
        exit(errno);
    }

    if (the_string->read_only) {
        errno = EACCES;
        perror(
                "Atempted to modify a read-only string"
              );
        exit(errno);
    }

    // If string length is the same as it's allocated size, it means
    // that, the string is full and must be grown.
    if (the_string->len == the_string->alloced_size) {
        growString(the_string);
    }

    
    the_string->char_ptr[the_string->len] = what; // Sets last + 1 char to passed value
    the_string->len++; // Incriments the length
    return 0; // Hopefully successful
}

int deInit(string * the_string) {
    free(the_string->char_ptr);
    free(the_string);
}

#endif
