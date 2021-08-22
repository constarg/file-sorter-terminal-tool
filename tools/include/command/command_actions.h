#ifndef FILE_SORTER_TERMINAL_TOOL_COMMAND_ACTIONS_H
#define FILE_SORTER_TERMINAL_TOOL_COMMAND_ACTIONS_H 1

#include <parsing/argument_parser.h>

extern void help();

extern void setter(struct command_p c_command_p, char *new_value);

extern void list_content(struct command_p c_command_p);

extern void add_or_remove(struct command_p c_command_p, char **to_delete_or_add);

#endif