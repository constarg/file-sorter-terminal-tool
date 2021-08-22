#ifndef FILE_SORTER_TERMINAL_TOOL_ARGUMENT_PARSER_H
#define FILE_SORTER_TERMINAL_TOOL_ARGUMENT_PARSER_H 1

// commands properties.
struct command_p {
    char *name;
    char *type;
    int index;
    char *identifier_one;
    char *identifier_two;
    int is_add_or_integer;
    int new_values_count;
};

void parse_args(int argc, char **argv);


#endif
