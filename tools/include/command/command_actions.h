/* command_actions.h */
#ifndef FILE_SORTER_TERMINAL_TOOL_COMMAND_ACTIONS_H
#define FILE_SORTER_TERMINAL_TOOL_COMMAND_ACTIONS_H

#include <parsing/argument_parser.h>

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
 * Append a new target to the config file, in the section
 * of targets.
 * @param new_target The new target to be appended.
 */
extern void add_target(const char *new_target);

/**
 * Append a new check to the config file, in the section
 * of targets.
 * @param new_check The new check to be appended.
 */
extern void add_check(const char *new_check);

/**
 * Remove the target in a specific row line.
 * @param row_line The row line of the target to be removed.
 */
extern void remove_target(int row_line);

/**
 * Remove the check in a specific row line.
 * @param row_line The row line of the check to be removed.
 */
extern void remove_check(int row_line);

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