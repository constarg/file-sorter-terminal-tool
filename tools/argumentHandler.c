#include <stdio.h>
#include <string.h>
#include "argumentHandler.h"

#define HELP_ARG "--help"
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

void help();

void addCheck(char *);

void addTarget(char *, char *);

void setCheckInterval(char *);

void setParseInterval(char *);

void setDebugLog(char *);

void setDefaultDirPath(char *);

void removeCheck(char *);

void removeTarget(char *, char *);

void listChecks();

void listTargets();

void listOptions();

int validateArg(char*, char* , char*,char*,int, int);

void parse(int argc, char **argv) {
    int found = 1;

    if (argc == 1) {
        help();
        found = 0;
    }

    if (found) {

        if (validateArg(argv[1], NULL, NULL, HELP_ARG, 0, 6))
            help();

        else if (validateArg(argv[1], argv[2], NULL, ADD_CHECK, 1, 11))
            addCheck(argv[2]);

        else if (validateArg(argv[1], argv[2], argv[3], ADD_TARGET, 2, 12))
            addTarget(argv[2], argv[3]);

        else if (validateArg(argv[1], argv[2], NULL, REMOVE_CHECK, 1, 14))
            removeCheck(argv[2]);

        else if (validateArg(argv[1], argv[2], argv[3], REMOVE_TARGET, 2, 15))
            removeTarget(argv[2], argv[3]);

        else if (validateArg(argv[1], argv[2], NULL, SET_CHECK_INTERVAL, 1, 20))
            setCheckInterval(argv[2]);

        else if (validateArg(argv[1], argv[2], NULL, SET_PARSE_INTERVAL, 1, 20))
            setParseInterval(argv[2]);

        else if (validateArg(argv[1], argv[2], NULL, SET_DEBUG_LOG, 1, 15))
            setDebugLog(argv[2]);

        else if (validateArg(argv[1], argv[2], NULL, SET_DEFAULT_DIR_PATH, 1, 22))
            setDefaultDirPath(argv[2]);

        else if (validateArg(argv[1], NULL, NULL, LIST_CHECKS, 0, 13))
            listChecks();

        else if (validateArg(argv[1], NULL, NULL, LIST_OPTIONS, 0, 14))
            listTargets();

        else if (validateArg(argv[1], NULL, NULL, LIST_TARGETS, 0, 14))
            listOptions();
    }

}

void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--add-check [path] Add new check\n"
           "\t--add-target [ext] [path] Add new target\n"
           "\t--remove-check [path] remove check\n"
           "\t--remove-target [ext] [path] remove target\n"
           "\t--list-checks list checks\n"
           "\t--list-targets list targets\n");

}

void addCheck(char *path) {
    // TODO add check.
}

void addTarget(char *ext, char *path) {
    // TODO add target.
}

void removeCheck(char *path) {
    // TODO remove check.
}

void removeTarget(char *ext, char *path) {
    // TODO remove target.
}

void setCheckInterval(char *checkInterval) {
    // TODO set check interval.
}

void setParseInterval(char *parseInterval) {
    // TODO set parse interval.
}

void setDebugLog(char *debugLog) {
    // TODO set debug log.
}

void setDefaultDirPath(char *defaultDirPath) {
    // TODO set default dir path.
}

void listChecks() {
    // TODO list checks.
}

void listTargets() {
    // TODO list targets.
}

void listOptions() {
    // TODO list options.
}


int validateArg(char* arg_1,
                 char* arg_2,
                 char* arg_3,
                 char* validate,
                 int args,
                 int len) {

    if (strlen(validate) == len) {
        if (strcmp(arg_1, validate) == 0) {
            if (args == 1) {
                if (arg_2 == NULL) {
                    help();
                    return 0;
                }
            }
            else if (args == 2) {
                if (arg_2 == NULL || arg_3 == NULL) {
                    help();
                    return 0;
                }
            }
            return 1;
        }

    }

    return 0;
}





