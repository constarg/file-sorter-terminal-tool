#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "argumentHandler.h"
#include "configHandler.h"

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

void replaceOptionValues(int , char *, char *, char *);

void replace(int, char*, char*, int);

int isValidIntValue(char* , char**);

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

    // TODO Find a way to change the check.
    // TODO Ensure that the path is a valid path.
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
    replace(1, "checkInterval", checkInterval, 1);
    printf("OK\n");
}

void setParseInterval(char *parseInterval) {
    replace(2, "parseInterval", parseInterval, 1);
    printf("OK\n");
}

void setDebugLog(char *debugLog) {
    replace(3, "debugLog", debugLog, 1);
    printf("OK\n");
}

void setDefaultDirPath(char *defaultDirPath) {
    // TODO validate that is correct path.
    replace(4, "defaultDirPath", defaultDirPath, 0);
    printf("OK\n");
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


void replaceOptionValues(int blockIndex,
                         char* config,
                         char* blockName,
                         char* newValue) {

    char** configBlocks = calloc(5, sizeof(char*));
    char* blockSplitter = "\n";
    char* tmp = NULL;
    size_t valueOfInterestLen;
    size_t configSize = strlen(config);

    // save targets and checks.
    tmp = strstr(config, "[check]");
    char *dependencies = calloc(strlen(tmp) + 1, sizeof(char));
    strcpy(dependencies, tmp);

    // get all the options and split them in 4 block.
    configBlocks[0] = strtok(config, blockSplitter);
    for (int block = 1; block < 5; block++) {
        configBlocks[block] = strtok(NULL, blockSplitter);
    }

    // find the location that we are interested.
    tmp = calloc(strlen(configBlocks[blockIndex]) + 2, sizeof(char));
    strcpy(tmp, configBlocks[blockIndex]);
    valueOfInterestLen = strlen(&tmp[strlen(blockName) + 1]);

    char* valueOfInterest = calloc(strlen(newValue) + 1, sizeof(char));

    // allocate the appropriate space for new value.
    char* saveNewValue = calloc(strlen(tmp) + (strlen(newValue) - valueOfInterestLen) + 2, sizeof(char));
    strcpy(saveNewValue, blockName);
    strcat(saveNewValue, " ");

    memmove(valueOfInterest, newValue, strlen(newValue));
    strcat(saveNewValue, valueOfInterest);

    // Finish the new config.
    size_t newConfigLen = configSize;
    newConfigLen = newConfigLen - valueOfInterestLen;
    newConfigLen = newConfigLen + strlen(newValue);
    char *newConfig = calloc(newConfigLen, sizeof(char));

    configBlocks[blockIndex] = saveNewValue;
    for (int concat = 0; concat < 5; concat++) {
        strcat(newConfig, configBlocks[concat]);
        strcat(newConfig, "\n");
    }
    strcat(newConfig, "\n");
    strcat(newConfig, dependencies);

    // save the changes.
    writeConfig(newConfig, strlen(newConfig));

    free(newConfig);
    free(saveNewValue);
    free(tmp);
    free(dependencies);
    free(valueOfInterest);
    free(configBlocks);
}

void replace(int index, char* block, char* newValue, int isInteger) {
    char *check;

    if (isInteger) {
        if (isValidIntValue(newValue, &check) == -1) {
            free(check);
            return;
        }
    }

    char* config = NULL;

    if (readConfig(&config) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }

    replaceOptionValues(index, config, block, newValue);

}

int isValidIntValue(char* value, char** result) {

    char* integer = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(integer, value);

    int check = strtol(value, &value, 10);

    if (check == 0 && integer[0] != '0') {
        fprintf(stderr, "Invalid value\n");
        help();
        return -1;
    }

    *result = integer;
    return 0;
}