# Brainfuck Interpreter

Written in C

> From Wikipedia, the free encyclopedia:
>
> Brainfuck is an esoteric programming language created in 1993 by Urban Müller. Notable for its extreme minimalism, the language consists of only eight simple commands, a data pointer and an instruction pointer.

## Building:

``git clone https://gitlab.com/yuri-the-cockroach/brainfuck-interpreter.git && cd brainfuck-interpreter && make build``

## Usage:

### Running:
``$./bf-run {--file {path/to/file}} [--debug] [--char]``

meaning:
* --file  -- path to the file containing brainfuck code. For example hellow_world.bf
* --debug -- enable debug output
* --char  -- interpret the output as characters instead of integers

### Syntax:
| Character | Meaning                                                                                                                                                                           |
|:---------:|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| >         | Increment the data pointer by one (to point to the next cell to the right).                                                                                                       |
| <         | Decrement the data pointer by one (to point to the next cell to the left).                                                                                                        |
| +         | Increment the byte at the data pointer by one.                                                                                                                                    |
| \-        | Decrement the byte at the data pointer by one.                                                                                                                                    |
| .         | Output the byte at the data pointer.                                                                                                                                              |
| ,         | Accept one byte of input, storing its value in the byte at the data pointer.                                                                                                      |
| [         | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command. |
| ]         | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command. |

Any character that is not on this table will be ignored.

For licensing questions pleace see the [LICENSE](./LICENSE.md)
