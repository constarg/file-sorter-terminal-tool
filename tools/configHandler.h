#ifndef FILE_SORTER_TERMINAL_TOOL_CONFIGHANDLER_H
#define FILE_SORTER_TERMINAL_TOOL_CONFIGHANDLER_H

extern int writeConfig(char* changes, size_t changesLen);
extern int readConfig(char** configContent);

#endif