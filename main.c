#include <stdarg.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "./dyn_string.c"
#include "./numbelt.c"

bool static volatile keep_running = 1; // run, untill this is set to 0. This flag can be set only by SIGINT
bool static volatile show_debug = 0; // if true, print debuging info
bool static volatile print_as_char = 0; // if true, print bytes as char

struct {
    uint key;
    uint value;
} typedef pos_pair;

/* This small debuging function allows to pass any parameters as follows:*/
/* {format} [info] [append_new_line]*/
/*    *char \*format* -- string that follows printf format standard*/
/*    *int info* -- information to be passed to formater*/
/*    *bool append_new_line* -- whether to append a new line to the end*/
void debug(char *format, ...) {
    if ( !show_debug ) {
        return;
    }

    int append_nl = 0;
    int info = 0;

    va_list ap;
    va_start(ap, format);

    info = va_arg(ap, int);
    append_nl = va_arg(ap, int);

    if ( append_nl ) {
        uint len = strlen(format);
        char *newstring = malloc(sizeof(char) * (len + 1));
        strcpy(newstring, format);
        newstring[len + 1] = '\n';
        format = newstring;
    }
    printf(format, info);
}

/* Sets keep_running flag to 0 in case the SIGINT is passed.
 * The keep_running flag is ment to be handeld in a while loop. If it is not handled it won't do anything */
void signalHandler(int signum) {
    if ( signum == SIGINT ) keep_running = 0;
    printf("Got SIGINT\n");
}

// This one will parse the command list,
// Check if all the brackets have a coresponding pair and for syntax correctness.
// If not, throw an error and terminate the program.
// If all goes well, returns a pointer to the list, where
// key and it's value are coresponding brackets. Sort of a hash table.
uint *parse_loops(string *command_list) {
    if ( command_list->len < 1 ) {
        errno = ERANGE;
        perror(
                "An empty string was passed, or string->len is wrong"
              );
        exit(errno);
    }

    int op_buff_count = 0;
    uint op_buff[command_list->len]; // buffer for the last opsitions of opening brackets
    uint *final_list_ptr = calloc(command_list->len, sizeof(uint)); // List that will be returned as a *map* of sort

    for ( uint i = 0; i < command_list->len; i++ ) {
        char current = command_list->char_ptr[i];

        if ( current == '[' ) {
            op_buff[op_buff_count] = i;
            op_buff_count++;
        }

        if ( current == ']' ) {
            if ( op_buff_count < 1 ){
              errno = ERANGE;
              perror(
                  "Closing brackets encountered, without a corresponding opening one"
                  );
              exit(errno);
            }
            final_list_ptr[i] = op_buff[op_buff_count - 1];
            final_list_ptr[op_buff[op_buff_count - 1]] = i;
            op_buff[op_buff_count - 1] = 0;
            op_buff_count--;
        }
    }

    debug("Finished parsing\n");
    return final_list_ptr;

}

// The program
int main(int argc, char *argv[])
{
    char *filename = calloc(64, sizeof(char));
    signal(SIGINT, signalHandler);
    // Check if code file provided

    if ( argc < 3 ) {
        fprintf(stderr, "Not enogth arguments\n");
    }

    for ( uint i = 0; i < argc; i++ ) {
        if ( strcmp(argv[i], "--debug") == 0 ) {
                show_debug = 1;
                continue;
            }

        if ( strcmp(argv[i], "--file") == 0 ) {
            debug(argv[i + 1], true);
            filename = argv[i + 1];
            continue;
        }

        if ( strcmp(argv[i], "--char") == 0 ) {
            debug("Got --char, printing output as characters\n");
            print_as_char = 1;
            continue;
        }
    }

    if ( !filename ) {
        debug(filename, 0, true);
        fprintf(stderr, "No code file provided\n");
        return 1;
    }

    // check if code file can be read
    if ( access( filename, R_OK ) != 0) {
        debug(filename, 0, true);
        fprintf(stderr, "File doesn't exists or it cannot be read\n");
        return 2;
    }

    numbelt *belt_ptr = initNum(); // Create and instanciate the first number link

    string instr_str = initString(8); // Create an instance of scanlable string with size of 8 chunks

    // Surrounded that part in brackets, so there is no way to call *bfcodefile* after *fclose*
    {
        FILE *bfcodefile = fopen(filename, "r"); // Open the file with read-only access
        char instr_char = 0;

        do {
            instr_char = fgetc(bfcodefile);
            stringAppend(&instr_str, instr_char);
        } while (instr_char != EOF && keep_running);

        fclose(bfcodefile);
    }

    instr_str.read_only = true; // Just in case

    uint *bracket_table = parse_loops(&instr_str);

    if (show_debug) {
      for (uint i = 0; i < instr_str.len; i++) {
        if (bracket_table[i] != 0)
          printf("%d == %d\n", i, bracket_table[i]);
      }
    }


    uint cursor = 0; // cursor that will indicate the position of an instruction to read
    while (keep_running) {
        char current = instr_str.char_ptr[cursor];

        if ( cursor == instr_str.len - 1 ) {
            break;
        }


        switch (current) {
            case '>':
                belt_ptr = getRight(belt_ptr);
                break;

            case '<':
                belt_ptr = getLeft(belt_ptr);
                break;

            case '+':
                incNum(belt_ptr);
                break;
            
            case '-':
                decNum(belt_ptr);
                break;

            case '.':
                if ( print_as_char ) printf("%c", fetchNum(belt_ptr));
                else printf("%d", fetchNum(belt_ptr));
                break;

            case ',':
                {
                    // Read the next byte and insert it's int representation as a value
                    int to_insert = instr_str.char_ptr[cursor + 1];
                    setNum(belt_ptr, to_insert);
                }
                break;

            case '[':
                if ( fetchNum(belt_ptr) == 0 ) {
                    cursor = bracket_table[cursor];
                }
                break;

            case ']':
                if ( fetchNum(belt_ptr) != 0 ) {
                    cursor = bracket_table[cursor];
                }
                break;

            default:
                cursor++;
                continue;
        }

        debug( "\n");
        debug("instr:    %c\n", current);
        debug("curs pos: %d\n", cursor);
        debug("nb pos:   %d\n", belt_ptr->pos);
        debug("nb val:   %d\n", belt_ptr->value);
        debug("\n");

        cursor++;

    }
    return 0;
}
