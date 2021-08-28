#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <command/command_actions.h>
#include <config/config_handler.h>
#include <parsing/argument_parser.h>

#define OPTION_NUMBER           5
#define SPLITTER                "\n"
#define CHANGE_LINE		        "\n"

#define TARGET_IDENTIFIER       "[targets]"
#define CHECK_IDENTIFIER        "[check]"
#define CHECK_DONE_IDENTIFIER   "[done_check]"

#define OPTIONS_START           "checkInterval"

void list(char *begin, char *end);

void replace_option(char *option, int option_index, char *new_value, int is_integer);

void set_option(char *option, char **options, char *new_value, int index, char *missing, size_t prev_conf_size);

void add(char *location_of_items, char *missing, char *to_add, int items_count, char **options, char *begin, char *end);

int is_valid_int_value(char *value, char **result, int return_int_res);

char *convert_array_to_string(char **array, int array_size);

char *get_missing_part(char *config, char *begin, char *end, int item_count);

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
    replace_option(c_command_p.id_one, c_command_p.index, new_value, c_command_p.is_add_or_integer);
}

void list_content(struct command_p c_command_p) {
    list(c_command_p.id_one, c_command_p.id_two);
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
    char **options = calloc(OPTION_NUMBER + 1, sizeof(char *));
    strcpy(tmp, config);
    tmp_options = strstr(tmp, OPTIONS_START);

    options[0] = "[basic_config]";
    options[1] = strtok(tmp_options, SPLITTER);
    for (int option = 2; option < OPTION_NUMBER; option++) options[option] = strtok(NULL, SPLITTER);

    // go to where the items is.
    char *location_of_interest = strstr(config, c_command_p.id_one);
    int item_count = count_items(location_of_interest, c_command_p.id_one, c_command_p.id_two);
    char *missing_part = get_missing_part(config, c_command_p.id_one, c_command_p.id_two, item_count);

    if (c_command_p.is_add_or_integer) {
        if (c_command_p.argc >= 2) {
            char *to_add = calloc(strlen(to_delete_or_add[2]) + strlen(to_delete_or_add[3]) + 2, sizeof(char));
            strcat(to_add, to_delete_or_add[2]);
            strcat(to_add, " ");
            strcat(to_add, to_delete_or_add[3]);
            // in case of target.
            add(location_of_interest, missing_part, to_add, item_count, options, c_command_p.id_one, c_command_p.id_two);
        }
        else {
            add(location_of_interest, missing_part, to_delete_or_add[2], item_count, options, c_command_p.id_one, c_command_p.id_two);
        }

    }

    // TODO here you have to call the remove function.

    free(options);
    free(tmp);
    free(config);
}

void add(char *location_of_items,
         char *missing,
         char *to_add,
         int items_count,
         char **options,
         char *begin,
         char *end) {

    // Allocate enough space for the previous item plus the new.
    char **items = calloc(items_count + 2, sizeof(char *));
    strtok(location_of_items, SPLITTER);

    int curr_item_index = 0;
    // temporary save the items in array.
    for (int item = 0; item < items_count; item++) items[item] = strtok(NULL, SPLITTER);
    items[items_count] = to_add;
    items[items_count + 1] = end;

    // get the required strings.
    char *options_string_form = convert_array_to_string(options, OPTION_NUMBER);
    char *items_string_form = convert_array_to_string(items, items_count + 2);

    // calculate the size of the new config.
    size_t new_config_size = strlen(options_string_form) + strlen(items_string_form) + strlen(missing) + strlen(begin);
    // allocate the space for the new config.
    char *new_config = calloc(new_config_size + 6, sizeof(char));

    // build the config.
    // set options.
    strcat(new_config, options_string_form);
    strcat(new_config, CHANGE_LINE);

    if (strcmp(begin, TARGET_IDENTIFIER) == 0) {
        strcat(new_config, missing);
        strcat(new_config, CHANGE_LINE);
        strcat(new_config, begin);
        strcat(new_config, CHANGE_LINE);
        strcat(new_config, items_string_form);
    }
    else {
        strcat(new_config, begin);
        strcat(new_config, CHANGE_LINE);
        strcat(new_config, items_string_form);
        strcat(new_config, CHANGE_LINE);
        strcat(new_config, missing);
    }

    write_config(new_config, new_config_size + 3);

    free(options_string_form);
    free(items_string_form);
    free(new_config);
    free(missing);
}

char *get_missing_part(char *config, char *begin, char *end, int item_count) {
    // BackUp the items.
    char *tmp = calloc(strlen(config) + 1, sizeof(char));
    strcpy(tmp, config);

    char *missing_part;
    char *start;
    if (strcmp(begin, CHECK_IDENTIFIER) == 0) {
        start = strstr(tmp, TARGET_IDENTIFIER);
        missing_part = calloc(strlen(start) + 1, sizeof(char));
        strcpy(missing_part, start);
        free(tmp);
        return missing_part;
    }
    start = strstr(tmp, CHECK_IDENTIFIER);
    // if check.
    // store all the check items.
    char **items_tmp = calloc(item_count + 1, sizeof(char *));
    start = strtok(start, SPLITTER);

    // save the items.
    int curr_item = 0;
    size_t curr_len;
    size_t total_len = 0;
    while (strcmp(start, CHECK_DONE_IDENTIFIER) != 0) {
        curr_len = strlen(start);
        items_tmp[curr_item] = calloc(curr_len + 1, sizeof(char));
        strcpy(items_tmp[curr_item], start);
        start = strtok(NULL, SPLITTER);
        total_len += curr_len;
        curr_item++;
    }
    // allocate enough space in tmp and form the missing string.
    missing_part = calloc(total_len + strlen(end) + curr_item + 4, sizeof(char));
    // save the items.
    for (int item = 0; item < curr_item; item++) {
        strcat(missing_part, items_tmp[item]);
        strcat(missing_part, CHANGE_LINE);
    }
    strcat(missing_part, CHANGE_LINE);
    strcat(missing_part, CHECK_DONE_IDENTIFIER);
    strcat(missing_part, CHANGE_LINE);

    for (int item = 0; item < curr_item; item++) free(items_tmp[item]);
    free(items_tmp);
    free(tmp);

    return missing_part;
}

char *convert_array_to_string(char **array, int array_size) {
    size_t total_size = 0;

    // calculate the total size of the new string.
    for (int element = 0; element < array_size; element++) total_size += strlen(array[element]);

    // allocate the space of the new string.
    char *string_form = calloc(total_size + array_size + 1, sizeof(char));
    // save each element on the as sequence of strings.
    for (int element = 0; element < array_size; element++) {
        strcat(string_form, array[element]);
        strcat(string_form, CHANGE_LINE);
    }


    return string_form;
}

// TODO make the remove function.


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

void set_option(char *option, char **options,
                char *new_value, int index,
                char *missing, size_t prev_conf_size) {

    // Allocate space for the interested string.
    size_t new_option_size = strlen(option) + strlen(new_value) + 2;
    char *changed_option = calloc(new_option_size, sizeof(char));
    // form the new option.
    strcpy(changed_option, option);
    strcat(changed_option, " ");
    strcat(changed_option, new_value);

    // calculate the size of the new config.
    size_t old_option_size = strlen(options[index]);
    size_t def_of_size = (new_option_size > old_option_size) ? (new_option_size - old_option_size) : (old_option_size -
                                                                                                      new_option_size);
    size_t new_conf_size = (new_option_size > old_option_size) ? (prev_conf_size + def_of_size) : (prev_conf_size -
                                                                                                   def_of_size);

    // temporary save the changed option.
    options[index] = changed_option;
    // form the new config.
    char *new_config = calloc(new_conf_size, sizeof(char));

    strcpy(new_config, options[0]);
    for (int save = 1; save < OPTION_NUMBER; save++) {
        strcat(new_config, CHANGE_LINE);
        strcat(new_config, options[save]);
    }
    strcat(new_config, CHANGE_LINE);
    strcat(new_config, CHANGE_LINE);
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
