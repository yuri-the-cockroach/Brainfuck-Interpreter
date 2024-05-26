#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
    char * string = "something asdc";
    printf("%lu", malloc_usable_size(&string));
    return 0;
}
