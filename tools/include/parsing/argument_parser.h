/* argument_parser.h */
#ifndef FILE_SORTER_TERMINAL_TOOL_ARGUMENT_PARSER_H
#define FILE_SORTER_TERMINAL_TOOL_ARGUMENT_PARSER_H

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


void parse_args(int argc, char **argv);


#endif
