#ifndef FILE_SORTER_TERMINAL_TOOL_COMMANDACTIONS_H
#define FILE_SORTER_TERMINAL_TOOL_COMMANDACTIONS_H 1

#include "argumentParser.h"

extern void help();

extern void setter(struct commandP commandP, char *newValue);

extern void listContent(struct commandP commandP);

extern void addOrRemove(struct commandP commandP, char **toDelete);

#endif