#include <string.h>

#include <parsing/argument_parser.h>
#include <command/command_actions.h>

/* commands */
#define ADD_CHECK               "--add-check"
#define ADD_TARGET              "--add-target"
#define SET_CHECK_INTERVAL      "--set-check-interval"
#define SET_PARSE_INTERVAL      "--set-parse-interval"
#define SET_DEBUG_LOG           "--set-debug-log"
#define SET_DEFAULT_DIR_PATH    "--set-default-dir-path"
#define SET_ENABLE_DEF_DIR      "--set-enable-default-dir"
#define REMOVE_CHECK            "--remove-check"
#define REMOVE_TARGET           "--remove-target"
#define LIST_CHECKS             "--list-checks"
#define LIST_TARGETS            "--list-targets"
#define LIST_OPTIONS            "--list-options"

/* identifier */
#define CHECK_ID                "[check]"
#define CHECK_ID_D              "[done_check]"
#define TARGET_ID               "[targets]"
#define TARGET_ID_D             "[done_targets]"

/* options */
#define C_INTERVAL_OP           "check_interval"
#define P_INTERVAL_OP           "parse_interval"
#define D_LOG_OP                "debug_log"
#define D_PATH_OP               "default_dir_path"
#define D_ENABL_OP              "enable_default_path"

/* number of args  */
#define ARGS_0                  0
#define ARGS_1                  1
#define ARGS_2                  2

/* helper bytes */
#define IS_ADD                  1
#define IS_INTEGER              1
#define IS_NOT_ADD              0
#define IS_NOT_INTEGER          0

/* type of the command */
#define SETTER_TYPE             "setter"
#define LIST_TYPE               "list"
#define ADD_REMOVE_TYPE         "add_remove"

/* number of the commands. */
#define NUMBER_OF_COMMANDS 12

// each row represent one command.
// each column represent one property of this specific command.
const struct command_p commands[NUMBER_OF_COMMANDS] = {
        {ADD_CHECK,            ADD_REMOVE_TYPE, 0, CHECK_ID,      CHECK_ID_D,   IS_ADD,         ARGS_1},
        {ADD_TARGET,           ADD_REMOVE_TYPE, 0, TARGET_ID,     TARGET_ID_D,  IS_ADD,         ARGS_2},
        {REMOVE_CHECK,         ADD_REMOVE_TYPE, 0, CHECK_ID,      CHECK_ID_D,   IS_NOT_ADD,     ARGS_1},
        {REMOVE_TARGET,        ADD_REMOVE_TYPE, 0, TARGET_ID,     TARGET_ID_D,  IS_NOT_ADD,     ARGS_1},
        {SET_CHECK_INTERVAL,   SETTER_TYPE,     1, C_INTERVAL_OP, NULL,         IS_INTEGER,     ARGS_1},
        {SET_PARSE_INTERVAL,   SETTER_TYPE,     2, P_INTERVAL_OP, NULL,         IS_INTEGER,     ARGS_1},
        {SET_DEBUG_LOG,        SETTER_TYPE,     3, D_LOG_OP,      NULL,  	    IS_INTEGER,     ARGS_1},
        {SET_DEFAULT_DIR_PATH, SETTER_TYPE,     4, D_PATH_OP,     NULL, 	    IS_NOT_INTEGER, ARGS_1},
        {SET_ENABLE_DEF_DIR,   SETTER_TYPE,     5, D_ENABL_OP,    NULL,         IS_INTEGER,     ARGS_1},
        {LIST_CHECKS,          LIST_TYPE,       0, CHECK_ID,      CHECK_ID_D,   IS_NOT_INTEGER, ARGS_0},
        {LIST_TARGETS,         LIST_TYPE,       0, TARGET_ID,     TARGET_ID_D,  IS_NOT_INTEGER, ARGS_0},
        {LIST_OPTIONS,         LIST_TYPE,       0, C_INTERVAL_OP, CHECK_ID,     IS_NOT_INTEGER, ARGS_0}
};


static inline int find_command(char *name, int *resIndex) {
    // Find the command.
    for (int command = 0; command < NUMBER_OF_COMMANDS; command++) {
        if (strcmp(commands[command].name, name) == 0) {
            *resIndex = command;
            return 0;
        }
    }

    return -1;
}

void parse_args(int argc, char **argv) {
    if (argc == 1) help();

    char *command_name = argv[1];
    int command_index = 0;

    // command not found.
    if (find_command(command_name, &command_index) == -1) help();
    // Command needs a new value, but no value has been set.
    if ((argc - 2) < commands[command_index].argc) help();

    if (strcmp(commands[command_index].type, SETTER_TYPE) == 0) setter(commands[command_index], argv[2]);
    else if (strcmp(commands[command_index].type, LIST_TYPE) == 0) list_content(commands[command_index]);
    else if (strcmp(commands[command_index].type, ADD_REMOVE_TYPE) == 0) add_or_remove(commands[command_index], argv);
}

