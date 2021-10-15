/* command_action.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <command/command_actions.h>
#include <config/config_handler.h>
#include <parsing/argument_parser.h>
#include <mem/mem.h>

#define TRUE  1
#define FALSE 0

#define INSTRUCTION_ARRAY_S 12

struct command_instructions {
    char  *c_name;          // command name.
    char  *c_attributes[2]; // command attributes.
};

// TODO - Fill the below array.
struct command_instructions c_instructions_array[INSTRUCTION_ARRAY_S] = {
        {.c_name = LIST_OPTIONS, .c_attributes[0] = C_INTERVAL_OP, .c_attributes[1] = CHECK_ID},
        {.c_name = LIST_CHECKS, .c_attributes[0] = CHECK_ID, .c_attributes[1] = CHECK_ID_D}
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

static inline int get_instructions(const char *c_name) {
    for (int instructions = 0; instructions < INSTRUCTION_ARRAY_S; instructions++) {
        if (strcmp(c_instructions_array[instructions].c_name, c_name) == 0)
            return instructions;
    }

    return -1;
}

void list_command(const char *what_to_list) {
    int index_of_instruction = get_instructions(what_to_list);
    if (index_of_instruction == -1) return;

    struct command_instructions instructions = c_instructions_array[index_of_instruction];
    // Read the config file.
    char *config = read_config();
    if (config == NULL) return;

    char *location_of_interest = strstr(config, instructions.c_attributes[0]);
    if (!location_of_interest) {
        free(config);
        return;
    }

    // Make a copy of the location_of_interest, so we do not break the data of config.
    char tmp[strlen(location_of_interest + 1)];
    strcpy(tmp, location_of_interest);

    char *current_element = strtok(location_of_interest, "\n");
    int row = 1;

    int skip_first = FALSE;
    if (!strcmp(instructions.c_name, LIST_CHECKS) || !strcmp(instructions.c_name, LIST_TARGETS))
        skip_first = TRUE;

    while (current_element != NULL && strcmp(current_element, instructions.c_attributes[1]) != 0) {
        if (row == 1 && skip_first) current_element = strtok(NULL, "\n");

        printf("%d: %s\n", row, current_element);
        row++;
        current_element = strtok(NULL, "\n");
    }

    free(config);
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
