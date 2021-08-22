#include <string.h>

#include <parsing/argument_parser.h>
#include <command/command_actions.h>

#define ADD_CHECK "--add-check"
#define ADD_TARGET "--add-target"
#define SET_CHECK_INTERVAL "--set-check-interval"
#define SET_PARSE_INTERVAL "--set-parse-interval"
#define SET_DEBUG_LOG "--set-debug-log"
#define SET_DEFAULT_DIR_PATH "--set-default-dir-path"
#define REMOVE_CHECK "--remove-check"
#define REMOVE_TARGET "--remove-target"
#define LIST_CHECKS "--list-checks"
#define LIST_TARGETS "--list-targets"
#define LIST_OPTIONS "--list-options"

#define SETTER_TYPE "setter"
#define LIST_TYPE "list"
#define ADD_REMOVE_TYPE "add_remove"

#define NUMBER_OF_COMMANDS 11

// each row represent one command.
// each column represent one property of this specific command.
const struct command_p commands[NUMBER_OF_COMMANDS] = {
        {ADD_CHECK, ADD_REMOVE_TYPE, 0, "[check]", "[done_check]", 1, 1},
        {ADD_TARGET, ADD_REMOVE_TYPE, 0, "[targets]", "[done_targets]", 1, 2},
        {REMOVE_CHECK, ADD_REMOVE_TYPE, 0, "[check]", "[done_check]", 0, 1},
        {REMOVE_TARGET, ADD_REMOVE_TYPE, 0, "[targets]", "[done_targets]", 0, 1},
        {SET_CHECK_INTERVAL, SETTER_TYPE, 1, "checkInterval", NULL, 1, 1},
        {SET_PARSE_INTERVAL, SETTER_TYPE, 2, "parseInterval", NULL, 1, 1},
        {SET_DEBUG_LOG, SETTER_TYPE, 3, "debugLog", NULL, 1, 1},
        {SET_DEFAULT_DIR_PATH, SETTER_TYPE, 4, "defaultDirPath", NULL, 0, 1},
        {LIST_CHECKS, LIST_TYPE, 0, "[check]", "[done_check]", 0, 0},
        {LIST_TARGETS, LIST_TYPE, 0, "[targets]", "[done_targets]", 0, 0},
        {LIST_OPTIONS, LIST_TYPE, 0, "checkInterval", "[check]", 0, 0}
};

int find_command(char *, int *);

void parse_args(int argc, char **argv) {
    if (argc == 1) help();

    char *command_name = argv[1];
    int command_index = 0;

    // command not found.
    if (find_command(command_name, &command_index) == -1) help();
    // Command needs a new value, but no value has been set.
    if ((argc - 2) < commands[command_index].new_values_count) help();

    if (strcmp(commands[command_index].type, SETTER_TYPE) == 0) setter(commands[command_index], argv[2]);
    else if (strcmp(commands[command_index].type, LIST_TYPE) == 0) list_content(commands[command_index]);
    else if (strcmp(commands[command_index].type, ADD_REMOVE_TYPE) == 0) add_or_remove(commands[command_index], argv);
}

int find_command(char *name, int *resIndex) {
    // Find the command.
    for (int command = 0; command < NUMBER_OF_COMMANDS; command++) {
        if (strcmp(commands[command].name, name) == 0) {
            *resIndex = command;
            return 0;
        }
    }

    return -1;
}