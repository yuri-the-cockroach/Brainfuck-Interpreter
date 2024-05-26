#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include "headers/deque.h"

struct tape {
    int array[UINT16_MAX];
} typedef tape;

struct int_pair {
    int key;
    int value;
} typedef int_pair;

tape init_tape() {
    tape return_tape;
    for (int i = 0; i < UINT16_MAX; i++){
        return_tape.array[i] = 0;
    }
    return return_tape;
};

bool check_syntax(FILE * fpt) {
    char str[2];
    int br_count = 0;

    while (fgets(str, 2, fpt)) {
        switch ( str[0] ) {
            case '[':
                br_count++;
                break;

            case ']':
                br_count--;
                break;
        }
        if (br_count < 0) return false;
    }
    if (br_count != 0) return false;
    return true;
}

int main()
{   
    setlocale(LC_NUMERIC, "");
    uint16_t position = 0;
    char input;
    int what;
    deque dq = deque_create();

    tape work_tape = init_tape();
    FILE *fpt;
    fpt = fopen("./test.bf", "r");
    printf("Is corrent = %i\n", check_syntax(fpt));
    fclose(fpt);
    do {
        scanf("%c", &input);
        switch (input) {
            case '<':
                position--;
                break;

            case '>':
                position++;
                break;

            case '+':
                work_tape.array[position]++;
                break;

            case '-':
                work_tape.array[position]--;
                break;

            case '.':
                printf("%i\n", work_tape.array[position]);
                break;

            case ',':
                scanf("%i", &what);
                break;

            case '[':
                deque_push(&dq, ftell(fpt));
                if ( work_tape.array[position] == 0 ) {
                    while (str != ']') {
                        TARGET
                    }
                }
                break;

            case ']':
                break;

        };
    } while (true);

    return 0;
}
