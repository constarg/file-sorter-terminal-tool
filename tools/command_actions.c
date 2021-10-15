/* command_action.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <command/command_actions.h>
#include <config/config_handler.h>
#include <parsing/argument_parser.h>

#define INSTRUCTION_ARRAY_S 12

#define GET_COMMAND_INSTRUCTIONS(RESULT, C_NAME, INSTRUCTION_ARRAY) do {                \
        for (int instruction = 0; instructon < INSTRUCTION_ARRAY_S; instruction++) {    \
            if (strcmp(INSTRUCTION_ARRAY[instruciton], C_NAME) == 0)                    \
                RESULT = INSTRUCTION_ARRAY[instruction];                                \
        }                                                                               \
    } while (0)


struct command_instructions {
    char *c_name;          // command name.
    char *c_attributes[2]; // command attributes.
};

// TODO - Fill the below array.
struct command_instructions c_instructions_array[INSTRUCTION_ARRAY_S] = {
};


void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--set-check-interval      [value] Change the value of check interval.\n"
           "\t--set-parse-interval      [value] Change the value of parse interval.\n"
           "\t--set-default-dir-path    [path] Change the default directory path.\n"
           "\t--set-enable-default-dir  [value] 0:1 Enable the to transfer files in default dir.\n"
           "\t--set-debug-log           [value] 0:1 Change the log to debug mode (1).\n"
           "\t--add-check               [path] Add new check.\n"
           "\t--add-target              [ext] [path] Add new target.\n"
           "\t--remove-check            [row number] remove check.\n"
           "\t--remove-target           [row number] remove target.\n"
           "\t--list-checks list checks.\n"
           "\t--list-targets list targets.\n"
           "\t--list-options list options.\n");

    exit(0);
}


void list_command(const char *what_to_list) {
    // TODO - List the contents of the @what_to_list.
}

void set_value(const char *option, const char *new_value) {
    // TODO - Set new value to the option @option.
}

void add_target(const char *new_target) {
    // TODO - add the target @new_target in the targets.
}

void add_new_check(const char *new_check) {
    // TODO - add the check @new_check in the checks.
}

void remove_target(int row_line) {
    // TODO - remove target in line @row_line.
}

void remove_check(int row_line) {
    // TODO - remove check in line @row_line.
}
