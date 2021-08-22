#ifndef FILE_SORTER_TERMINAL_TOOL_ARGUMENT_PARSER_H
#define FILE_SORTER_TERMINAL_TOOL_ARGUMENT_PARSER_H 1

// commands properties.
struct command_p {
    char *name;
    char *type;
    int index;
    char *id_one;
    char *id_two;
    int is_add_or_integer;
    int argc;
};

void parse_args(int argc, char **argv);


#endif
