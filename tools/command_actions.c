#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/command_actions.h"
#include "include/config_handler.h"
#include "include/argument_parser.h"

#define OPTION_NUMBER 5
#define SPLITTER "\n"

#define TARGET_IDENTIFIER "[targets]"
#define CHECK_IDENTIFIER "[check]"
#define CHECK_DONE_IDENTIFIER "[done_check]"

void list(char *begin, char *end);

void replace_option(char *option, int option_index, char *new_value, int is_integer);

void set_option(char *option, char **options, char *new_value, int index, char *missing, size_t prev_conf_size);

void add(char *location_of_items, int items_count, char **options, char *begin, char *end);

int is_valid_int_value(char *value, char **result, int return_int_res);

int count_items(char *items, char *begin, char *end);

void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--set-check-interval [value] Change the value of check interval.\n"
           "\t--set-parse-interval [value] Change the value of parse interval.\n"
           "\t--set-default-dir-path [path] Change the default directory path.\n"
           "\t--set-debug-log [value] 0:1 Change the log to debug mode (1).\n"
           "\t--add-check [path] Add new check.\n"
           "\t--add-target [ext] [path] Add new target.\n"
           "\t--remove-check [row number] remove check.\n"
           "\t--remove-target [row number] remove target.\n"
           "\t--list-checks list checks.\n"
           "\t--list-targets list targets.\n"
           "\t--list-options list options.\n");

    exit(0);
}

void setter(struct command_p c_command_p, char *new_value) {
    replace_option(c_command_p.identifier_one, c_command_p.index, new_value, c_command_p.is_add_or_integer);
}

void list_content(struct command_p c_command_p) {
    list(c_command_p.identifier_one, c_command_p.identifier_two);
}

void replace_option(char *option, int option_index, char *new_value, int is_integer) {
    char *config = NULL;
    // read the config file.
    if (read_config(&config) == -1) return;

    size_t conf_size = strlen(config);
    // allocate space to save all the previous options.
    char **options = calloc(OPTION_NUMBER, sizeof(char *));
    char *missing = calloc(conf_size + 1, sizeof(char));

    strncpy(missing, config, conf_size);
    // save the checks and targets.
    char *missing_fields = strstr(missing, "[check]");
    // save the options.
    options[0] = strtok(config, SPLITTER);

    for (int index = 1; index < OPTION_NUMBER; index++)
        options[index] = strtok(NULL, SPLITTER);

    // check if is an integer.
    if (is_integer) {
        char *integer_value;
        if (is_valid_int_value(new_value, &integer_value, 0))
            set_option(option, options, new_value, option_index, missing_fields, conf_size);

        free(integer_value);
    } else set_option(option, options, new_value, option_index, missing_fields, conf_size);

    free(missing);
    free(options);
    free(config);
}

void add_or_remove(struct command_p c_command_p, char **to_delete_or_add) {
    char *config = NULL;

    // get the config.
    if (read_config(&config) == -1) return;

    // save the options.
    char *tmp = calloc(strlen(config) + 1, sizeof(char));
    char *tmp_options;
    char **options = calloc(OPTION_NUMBER, sizeof(char*));
    strcpy(tmp, config);
    tmp_options = strstr(tmp, c_command_p.identifier_one);
    options[0] = strtok(tmp_options, SPLITTER);

    for (int option = 1; option < OPTION_NUMBER; option++) options[option] = strtok(NULL, SPLITTER);

    // go to where the items is.
    char *location_of_interest = strstr(config, c_command_p.identifier_one);
    int item_count = count_items(location_of_interest, c_command_p.identifier_one, c_command_p.identifier_two);

    if (c_command_p.is_add_or_integer)
        add(location_of_interest, item_count, options, c_command_p.identifier_one, c_command_p.identifier_two);

    free(options);
    free(config);
}

void add(char *location_of_items,
         int items_count,
         char **options,
         char *begin,
         char *end) {

    // Allocate enough space for the previous item plus the new.
    char **items = calloc(items_count + 1, sizeof(char*));
    strtok(location_of_items, SPLITTER);

    // temporary save the items in array.
    for (int item = 0; item < items_count; item++) items[item] = strtok(NULL, SPLITTER);

    free(items);
}

int count_items(char *items, char *begin, char *end) {
    // copy the same items as the original, in the tmp.
    char *tmp = calloc(strlen(items) + 1, sizeof(char));
    strcpy(tmp, items);
    // go to the desire location
    char *tmp_items = strstr(tmp, begin);

    // count the items.
    int count = 0;
    char *curr_item = strtok(tmp_items, SPLITTER);
    while (strcmp(curr_item, end) != 0) {
        count++;
        curr_item = strtok(NULL, SPLITTER);
    }
    free(tmp);
    return count - 1;
}

void set_option(char *option,
                char **options,
                char *new_value,
                int index,
                char *missing,
                size_t prev_conf_size) {

    // Allocate space for the interested string.
    size_t new_option_size = strlen(option) + strlen(new_value) + 2;
    char *changed_option = calloc(new_option_size, sizeof(char));
    // form the new option.
    strcpy(changed_option, option);
    strcat(changed_option, " ");
    strcat(changed_option, new_value);

    // calculate the size of the new config.
    size_t old_option_size = strlen(options[index]);
    size_t def_of_size = (new_option_size > old_option_size) ? (new_option_size - old_option_size) : (old_option_size - new_option_size);
    size_t new_conf_size = (new_option_size > old_option_size) ? (prev_conf_size + def_of_size) : (prev_conf_size - def_of_size);

    // temporary save the changed option.
    options[index] = changed_option;
    // form the new config.
    char *new_config = calloc(new_conf_size, sizeof(char));

    strcpy(new_config, options[0]);
    for (int save = 1; save < OPTION_NUMBER; save++) {
        strcat(new_config, "\n");
        strcat(new_config, options[save]);
    }
    strcat(new_config, "\n\n");
    strcat(new_config, missing);

    // save the changes.
    write_config(new_config, new_conf_size - 1);
    free(new_config);
    free(changed_option);
}

int is_valid_int_value(char *value, char **result, int return_int_res) {

    char *integer = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(integer, value);

    int check = strtol(value, &value, 10);

    if (check == 0 && integer[0] != '0') {
        return -1;
    }
    if (return_int_res) return check;

    *result = integer;
    return 1;
}

void list(char *begin, char *end) {
    char *config = NULL;

    if (read_config(&config) == -1) return;

    char *start = strstr(config, begin);
    char *curr_item = strtok(start, SPLITTER);
    int counter = 1;

    if (start != NULL) {
        while (curr_item != NULL && strcmp(curr_item, end) != 0) {
            if (strcmp(begin, curr_item) == 0) {
                curr_item = strtok(NULL, SPLITTER);
                continue;
            }
            printf("[*] [%d] %s\n", counter, curr_item);
            curr_item = strtok(NULL, SPLITTER);
            counter++;
        }

    }
    free(config);
}