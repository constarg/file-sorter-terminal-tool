#ifndef FILE_SORTER_TERMINAL_TOOL_CONFIG_HANDLER_H
#define FILE_SORTER_TERMINAL_TOOL_CONFIG_HANDLER_H 1

extern int write_config(char *changes, size_t changes_len);

extern int read_config(char **config_content);

#endif