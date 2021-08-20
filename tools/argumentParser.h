#ifndef FILE_SORTER_TERMINAL_TOOL_ARGUMENTPARSER_H
#define FILE_SORTER_TERMINAL_TOOL_ARGUMENTPARSER_H 1

// commands properties.
struct commandP {
    char *name;
    char *type;
    int index;
    char *identifier_one;
    char *identifier_two;
    int isInteger;
};

void parseArgs(int argc, char** argv);


#endif
