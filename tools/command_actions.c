/* command_action.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int    c_is_int;
};

struct command_instructions c_instructions_array[INSTRUCTION_ARRAY_S] = {
        {.c_name = SET_CHECK_INTERVAL,   .c_attributes[0] = C_INTERVAL_OP,  .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = SET_PARSE_INTERVAL,   .c_attributes[0] = P_INTERVAL_OP,  .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = SET_DEBUG_LOG,        .c_attributes[0] = D_ENABL_OP,     .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = SET_DEFAULT_DIR_PATH, .c_attributes[0] = D_PATH_OP,      .c_attributes[1] = NULL,        .c_is_int = FALSE},
        {.c_name = SET_ENABLE_DEF_DIR,   .c_attributes[0] = D_ENABL_OP,     .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = ADD_CHECK,            .c_attributes[0] = CHECK_ID,       .c_attributes[1] = CHECK_ID_D,  .c_is_int = FALSE},
        {.c_name = ADD_TARGET,           .c_attributes[0] = TARGET_ID,      .c_attributes[1] = TARGET_ID_D, .c_is_int = FALSE},
        {.c_name = REMOVE_CHECK,         .c_attributes[0] = CHECK_ID,       .c_attributes[1] = CHECK_ID_D,  .c_is_int = FALSE},
        {.c_name = REMOVE_TARGET,        .c_attributes[0] = TARGET_ID,      .c_attributes[1] = TARGET_ID_D, .c_is_int = FALSE},
        {.c_name = LIST_OPTIONS,         .c_attributes[0] = C_INTERVAL_OP,  .c_attributes[1] = CHECK_ID,    .c_is_int = FALSE},
        {.c_name = LIST_TARGETS,         .c_attributes[0] = TARGET_ID,      .c_attributes[1] = TARGET_ID_D, .c_is_int = FALSE},
        {.c_name = LIST_CHECKS,          .c_attributes[0] = CHECK_ID,       .c_attributes[1] = CHECK_ID_D,  .c_is_int = FALSE}
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

static int is_integer(const char *value) {
    char *digits = "0123456789";
    int found = FALSE;
    char *digits_first_address = &digits[0];

    while (*value) {
        digits = digits_first_address;
        found = FALSE;
        while (*digits) {
            if (*value == *digits)
                found = TRUE;
            digits++;
        }
        if (!found) return FALSE;
        value++;
    }

    return TRUE;
}

static char **config_to_array(const char *config, size_t *size) {
    // Here we are going to store all the content of the config as an array.
    char **config_array;
    ALLOCATE_MEMORY(config_array, 1, sizeof(char *));

    // Copy the config file into the tmp, to not break the original config.
    char tmp[strlen(config) + 1];
    strcpy(tmp, config);

    char *current_element = strtok(tmp, "\n");

    size_t config_array_s = 0;
    // Get each element on the config.
    while (current_element != NULL) {
        ALLOCATE_MEMORY(config_array[config_array_s], strlen(current_element) + 1, sizeof(char));
        strcpy(config_array[config_array_s], current_element);

        ++config_array_s;
        REALLOCATE_MEMORY(config_array, config_array_s + 1, sizeof(char *));
        current_element = strtok(NULL, "\n");
    }
    *size = config_array_s;
    return config_array;
}

static char *array_to_config(const char **array, size_t array_s) {
    // TODO - Make this function.
    return NULL;
}

void set_value(const char *option, const char *new_value) {
    int index_of_instructions = get_instructions(option);
    if (index_of_instructions == -1) return;

    struct command_instructions instructions = c_instructions_array[index_of_instructions];
    // Check if we want the new_value to be integer.
    if (instructions.c_is_int) {
        if (!is_integer(new_value)) return;
    }

    char *config = read_config();
    if (config == NULL) return;

    // Here we replace the old value with the new.
    size_t config_array_s = 0;
    char **config_array = config_to_array(config, &config_array_s);

    int index_of_interest = 0;
    for (int curr_option = 0; curr_option < config_array_s; curr_option++) {
        if (strstr(config_array[curr_option], instructions.c_attributes[0])) index_of_interest = curr_option;
    }
    if (index_of_interest == 0) return;

    // Form the changed option.
    char *changed_option;
    ALLOCATE_MEMORY(changed_option, strlen(instructions.c_attributes[0]) + strlen(new_value) + 2, sizeof(char));
    strcpy(changed_option, instructions.c_attributes[0]);
    strcat(changed_option, " ");
    strcat(changed_option, new_value);

    // Set the changed option in the right place.
    config_array[index_of_interest] = changed_option;

    // Rebuild the config file.
    free(config);
    config = array_to_config((const char **) config_array, config_array_s);
    // TODO - Write the result back the the config.conf

    FREE_ARRAY(config_array, config_array_s);
    free(changed_option);
    free(config);
}

void add_target(const char *new_target) {
    // TODO - add the target @new_target in the targets.
}

void add_check(const char *new_check) {
    // TODO - add the check @new_check in the checks.
}

void remove_target(int row_line) {
    // TODO - remove target in line @row_line.
}

void remove_check(int row_line) {
    // TODO - remove check in line @row_line.
}
