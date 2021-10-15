/* argument_parser.c */
#include <string.h>

#include <parsing/argument_parser.h>
#include <command/command_actions.h>

/* functions types */
typedef void func_arg_1(const char *);
typedef void func_arg_2(const char *, const char *);

/* number of the commands. */
#define NUMBER_OF_COMMANDS 12

// each row represent one command.
// each column represent one property of this specific command.
/*const struct command_p commands[NUMBER_OF_COMMANDS] = {
        // TODO - Fill the array here.
};*/


/**
 * @param name The name of the command we are searching.
 * @return The index of the command in the commands array or -1.
 */
static inline int find_command(const char *name) {
    // TODO - Make find command.
    return 0;
}

void parse_args(int argc, char **argv) {
    
}

