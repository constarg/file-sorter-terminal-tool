/* config_handler.h */
#ifndef FILE_SORTER_TERMINAL_TOOL_CONFIG_HANDLER_H
#define FILE_SORTER_TERMINAL_TOOL_CONFIG_HANDLER_H

/**
 * Rewrite the config file.
 * @param changes The data to write.
 * @param changes_len The length of the data.
 * @return -1 on error or 0 on success.
 */
extern int write_config(char *changes, size_t changes_len);

/**
 * Read all the content of the config file.
 * @param config_content The variable that will get the content.
 * @return -1 on error or 0 on success.
 */
extern int read_config(char **config_content);

#endif