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


/* number of the commands. */
#define NUMBER_OF_COMMANDS 12

// TODO - Make a few types.

// each row represent one command.
// each column represent one property of this specific command.
const struct command_p commands[NUMBER_OF_COMMANDS] = {

};


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

