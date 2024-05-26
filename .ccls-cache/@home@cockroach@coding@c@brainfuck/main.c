#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if ( argv[1] == NULL ) {
        fprintf(stderr, "No code file provided\n");
        return 1;
    }
    if ( access(argv[1], R_OK) != 0) {
        fprintf(stderr, "File doesn't exists or it cannot be read\n");
        return 1;
    }

    FILE bfcodefile;

    fopen(const char *, const char *)

    return 0;
}
