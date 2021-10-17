/* argument_parser.c */
#include <string.h>

#include <parsing/argument_parser.h>
#include <command/command_actions.h>

/* functions types */
typedef void generic(void);
typedef void func_arg_1(const char *);
typedef void func_arg_2(const char *, const char *);

/* number of the commands. */
#define NUMBER_OF_COMMANDS 13

struct a_command {
    char    *c_name;
    generic *c_func;
    size_t   c_argc;
};

static struct a_command commands[NUMBER_OF_COMMANDS] = {
        {.c_name = SET_CHECK_INTERVAL,    .c_func = (generic *) &set_check_interval,     .c_argc = 1},
        {.c_name = SET_PARSE_INTERVAL,    .c_func = (generic *) &set_parse_interval,     .c_argc = 1},
        {.c_name = SET_DEBUG_LOG,         .c_func = (generic *) &set_debug_log,          .c_argc = 1},
        {.c_name = SET_DEFAULT_DIR_PATH,  .c_func = (generic *) &set_default_dir_path,   .c_argc = 1},
        {.c_name = SET_ENABLE_DEF_DIR,    .c_func = (generic *) &set_enable_def_dir,     .c_argc = 1},
        {.c_name = ADD_CHECK,             .c_func = (generic *) &add_check,              .c_argc = 1},
        {.c_name = ADD_TARGET,            .c_func = (generic *) &add_target,             .c_argc = 2},
        {.c_name = REMOVE_CHECK,          .c_func = (generic *) &remove_check,           .c_argc = 1},
        {.c_name = REMOVE_TARGET,         .c_func = (generic *) &remove_target,          .c_argc = 2},
        {.c_name = LIST_CHECKS,           .c_func = (generic *) &list_checks,            .c_argc = 0},
        {.c_name = LIST_TARGETS,          .c_func = (generic *) &list_targets,           .c_argc = 0},
        {.c_name = LIST_OPTIONS,          .c_func = (generic *) &list_options,           .c_argc = 0},
        {.c_name = HELP,                  .c_func = (generic *) &help,                   .c_argc = 0}
};

static inline int find_command(const char *c_name) {
    if (c_name == NULL) return -1;
    for (int command = 0; command < NUMBER_OF_COMMANDS; command++) {
        if (!strcmp(commands[command].c_name, c_name))
            return command;
    }

    return -1;
}

void parse_args(int argc, char **argv) {
    if (argc < 2) help();

    int command_to_exec = find_command(argv[1]);
    if (command_to_exec == -1) help();

    if ((argc - 2) < commands[command_to_exec].c_argc) help();

    if (commands[command_to_exec].c_argc == 0) commands[command_to_exec].c_func();
    else if (commands[command_to_exec].c_argc == 1) ((func_arg_1 *) commands[command_to_exec].c_func)(argv[2]);
    else if (commands[command_to_exec].c_argc == 2) ((func_arg_2 *) commands[command_to_exec].c_func)(argv[2], argv[3]);
}

