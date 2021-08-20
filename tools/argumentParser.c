#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "argumentParser.h"
#include "argumentHandler.h"

#define ADD_CHECK "--add-check"
#define ADD_TARGET "--add-target"
#define SET_CHECK_INTERVAL "--set-check-interval"
#define SET_PARSE_INTERVAL "--set-parse-interval"
#define SET_DEBUG_LOG "--set-debug-log"
#define SET_DEFAULT_DIR_PATH "--set-default-dir-path"
#define REMOVE_CHECK "--remove-check"
#define REMOVE_TARGET "--remove-target"
#define LIST_CHECKS "--list-checks"
#define LIST_TARGETS "--list-targets"
#define LIST_OPTIONS "--list-options"

#define SETTER_TYPE "setter"
#define LIST_TYPE "list"
#define ADD_REMOVE_TYPE "add_remove"

const struct commandP commands[10] = {
        SET_CHECK_INTERVAL, SETTER_TYPE, 1 , "checkInterval", NULL, 1,
        SET_PARSE_INTERVAL, SETTER_TYPE , 2 , "parseInterval", NULL, 1,
        SET_DEBUG_LOG, SETTER_TYPE , 3 , "debugLog", NULL, 1,
        SET_DEFAULT_DIR_PATH, SETTER_TYPE, 4 , "defaultDirPath", NULL, 0,
        LIST_CHECKS, LIST_TYPE, 0 ,"[check]", "[done_check]", 0,
        LIST_TARGETS, LIST_TYPE, 0 , "[targets]", "[done_targets]", 0,
        LIST_OPTIONS, LIST_TYPE, 0 ,"checkInterval", "[check]", 0
};

int findCommand(char *, int *);

void parseArgs(int argc, char** argv) {
    if (argc == 1) help();

    char *commandName = argv[1];
    int commandIndex = 0;
    char *commandType;

    // command not found.
    if (findCommand(commandName, &commandIndex) == -1) help();
    // Command needs a new value, but no value has been set.
    if (!commands[commandIndex].identifier_two && argc < 3) help();

    if (strcmp(commands[commandIndex].type, SETTER_TYPE) == 0) setter(commands[commandIndex], argv[2]);
    else if (strcmp(commands[commandIndex].type, LIST_TYPE) == 0) listContent(commands[commandIndex]);
    else if (strcmp(commands[commandIndex].type, ADD_REMOVE_TYPE) == 0) return; // add or remove.

}

int findCommand(char *name, int *resIndex) {
    // Find the command.
    for (int command = 0; command < 7; command++) {
        if (strcmp(commands[command].name, name) == 0) {
            *resIndex = command;
            return 0;
        }
    }

    return -1;
}