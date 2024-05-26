#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "./dyn_string.c"
#include "./numbelt.c"



struct {
    uint key;
    uint value;
} typedef pos_pair;

// This one will parse the command list
// Check if all brackets have a coresponding pair and don't brake syntax
// If not, throw an error and terminate the program
// If all goes well, returns a pointer to the list, where
// key and it's value are coresponding brackets. Sorta hash table
uint * parse_loops(string * command_list, int * loops_pos) {


    if ( command_list->len < 1 ) {
        errno = ERANGE;
        perror(
                "An empty string was passed, or string->len is wrong"
              );
        exit(errno);
    }

    int op_buff_count = 0;
    uint op_buff[command_list->len]; // buffer for the last opsitions of opening brackets
    uint final_list[command_list->len]; // List that will be returned as a *map* of sort

    for ( uint i = 0; i < command_list->len; i++ ) {
        char current = command_list->char_ptr[i];
        if ( current == EOF ) {
            printf("EOF\n");
            /* errno = EINVAL; */
            /* perror("An unexpected EOF encountered" */
            /*        "either string->len is wrong, or string was changed manualy"); */
            /* exit(errno); */
        }

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
            final_list[op_buff[op_buff_count - 1]] = i;
            op_buff[op_buff_count - 1] = 0;
            op_buff_count--;
        }
    }
    return final_list;

}

// The program
int main(int argc, char* argv[])
{
    // Check if code file provided
    if ( !argv[1] ) {
        fprintf(stderr, "No code file provided\n");
        return 1;
    }

    // check if code file can be read
    if ( access(argv[1], R_OK) != 0) {
        fprintf(stderr, "File doesn't exists or it cannot be read\n");
        return 2;
    }

    char * filename = argv[1];
    FILE * bfcodefile = fopen(filename, "r"); // Open the file with read-only access
    numbelt * belt_ptr = initNum(); // Create and instanciate the first number link

    string instr_str = initString(8); // Create an instance of scanlable string with size of 8 chunks
    char instr_char = fgetc(bfcodefile);

    while (instr_char != EOF){
        instr_char = fgetc(bfcodefile);
        stringAppend(&instr_str, instr_char);
    };
    fclose(bfcodefile);
    instr_str.read_only = true;


    uint cursor = 0; // cursor that will indicate the position of an instruction to read

    while (true) {
        char current = instr_str.char_ptr[cursor];

        if ( instr_str.char_ptr[cursor] == '\0' ) {
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
                printf("%i", fetchNum(belt_ptr));
                break;

            case ',':
                {
                    // Read the next byte and insert it's int representation as a value
                    int to_insert = fgetc(bfcodefile);
                    setNum(belt_ptr, to_insert);
                }
                break;

            case '[':
                
                break;

            case ']':

                break;
        }
    }
    return 0;
}
