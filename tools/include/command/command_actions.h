/* command_actions.h */
#ifndef FILE_SORTER_TERMINAL_TOOL_COMMAND_ACTIONS_H
#define FILE_SORTER_TERMINAL_TOOL_COMMAND_ACTIONS_H

#include <parsing/argument_parser.h>
#include <string.h>

/**
 * Display unrecognized message.
 */
void unrecognized_option();

/**
 * Display a help message for the user.
 */
extern void help();

/**
 * Change the value of an option in the config file.
 * @param option The option to be change.
 * @param new_value The value that's gonna replace the old value.
 */
extern void set_value(const char *option, const char *new_value);

/**
 * Adds a new element on a specific list.
 * @param option The option that contains the list.
 * @param value_to_add The element to be added.
 */
extern void add_to_list(const char *option, const char *value_to_add);

/**
 * Removes an element from a specific list.
 * @param from_where The option that contains the list.
 * @param row_number The the position of the element to be deleted.
 */
extern void remove_from_list(const char *from_where, char *row_number);

/**
 * List the contents of a specific element.
 * @param what_to_list The element to be listed in the terminal.
 */
extern void list_command(const char *what_to_list);

/**
 * Change the value of check interval.
 */
static inline void set_check_interval(const char *new_value) {
    set_value(SET_CHECK_INTERVAL, new_value);
}

/**
 * Change the value of parse interval.
 */
static inline void set_parse_interval(const char *new_value) {
    set_value(SET_PARSE_INTERVAL, new_value);
}

/**
 * Change the value of debug.
 */
static inline void set_debug_log(const char *new_value) {
    set_value(SET_DEBUG_LOG, new_value);
}

/**
 * Change the location of the default dir path.
 */
static inline void set_default_dir_path(const char *new_value) {
    set_value(SET_DEFAULT_DIR_PATH, new_value);
}

/**
 * Enable default dir path.
 */
static inline void set_enable_def_dir(const char *new_value) {
    set_value(SET_ENABLE_DEF_DIR, new_value);
}

/**
 * Append a new check to the config file, in the section
 * of targets.
 * @param new_check The new check to be appended.
 */
static inline void add_check(const char *new_check) {
    add_to_list(ADD_CHECK, new_check);
}

/**
 * Append a new target to the config file, in the section
 * of targets.
 * @param target_path The path to be appended.
 * @param target_ext  The file extension to be related with the target_path.
 */
static inline void add_target(const char *target_path, const char *target_ext) {
    char target[strlen(target_path) + strlen(target_ext) + 2];
    strcpy(target, target_path);
    strcat(target, " ");
    strcat(target, target_ext);

    add_to_list(ADD_TARGET, target);
}

/**
 * Remove the target in a specific row line.
 * @param row_line The row line of the target to be removed.
 */
static inline void remove_target(char *row_line) {
    remove_from_list(REMOVE_TARGET, row_line);
}

/**
 * Remove the check in a specific row line.
 * @param row_line The row line of the check to be removed.
 */
static inline void remove_check(char *row_line) {
    remove_from_list(REMOVE_CHECK, row_line);
}

/**
 * List checks.
 */
static inline void list_checks() { list_command(LIST_CHECKS); }

/**
 * List targets.
 */
static inline void list_targets() { list_command(LIST_TARGETS); }

/**
 * List options.
 */
static inline void list_options() { list_command(LIST_OPTIONS); }

#endif