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

// Check syntax for unmaching brackets. Returns true if they match and false if not.
// fpt -- file pointer for the executable
// opb_deque -- deque * to the deque that will have positions of opening brackets 
bool check_syntax(FILE * fpt,  deque * opb_deque, deque * clb_deque) {
    char str[2];
    int br_count = 0;
    if ( opb_deque->size != 0 || clb_deque->size != 0) {
        perror("Op or Cl deque provided is not empty!");
        exit(EXIT_FAILURE);
    }

    while (fgets(str, 2, fpt)) {
        fpos_t pos;
        switch ( str[0] ) {
            case '[':
                fgetpos(fpt, &pos);
                deque_push(opb_deque, pos);
                br_count++;
                break;

            case ']':
                fgetpos(fpt, &pos);
                deque_push(clb_deque, pos);
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
    deque opb_deque = deque_create(); // Opening brackest deque
    deque clb_deque = deque_create(); // Closing brackest deque

    tape work_tape = init_tape();
    FILE *fpt;
    fpt = fopen("./test.bf", "r");
    printf("Is corrent = %i\n", check_syntax(fpt, ));
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
