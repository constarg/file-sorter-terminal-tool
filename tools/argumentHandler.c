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
    char* config = NULL;

    if (readConfig(&config) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }

    // TODO Find a way to change the check.
    // TODO Ensure that the path is a valid path.

    free(config);
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
    char* interval = malloc((strlen(checkInterval) + 1) * sizeof(char));
    strcpy(interval, checkInterval);

    int check = strtol(checkInterval, &checkInterval, 10);
    char* config = NULL;

    if (check == 0) {
        fprintf(stderr, "invalid check interval\n");
        return;
    }

    if (readConfig(&config) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }

    replaceOptionValues(1, config, "checkInterval", interval);

    free(interval);
    free(config);
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


void replaceOptionValues(int blockIndex,
                         char* config,
                         char* blockName,
                         char* newValue) {

    char** configBlocks = calloc(5, sizeof(char*));
    char* blockSplitter = "\n";
    char* tmp = NULL;
    size_t locationOfInterestLen;
    size_t blockNameLen;
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
    char* locationOfInterest = &configBlocks[blockIndex][strlen(blockName) + 1];
    locationOfInterestLen = strlen(locationOfInterest);;

    char* empty = calloc(locationOfInterestLen, sizeof(char));

    // fill empty cells of memory.
    for (int emp = 0; emp < locationOfInterestLen; emp++) empty[emp] = ' ';

    // clear the previous stored value.
    memmove(locationOfInterest, empty, locationOfInterestLen);
    // store the new value.
    memmove(locationOfInterest, newValue, strlen(newValue));

    blockNameLen = strlen(blockName);
    tmp = calloc(locationOfInterestLen + blockNameLen + 10, sizeof(char));
    // reallocate the old value a an new string so that is not depending on the other blocks.
    strncpy(tmp, blockName, blockNameLen);
    strcat(tmp, " ");
    strcat(tmp, locationOfInterest);
    strcat(tmp, "\n");

    // Finish the new config.
    char *newConfig = calloc(configSize + (strlen(newValue) - locationOfInterestLen) + strlen(dependencies), sizeof(char));

    strcpy(newConfig, configBlocks[0]);
    strcat(newConfig, "\n");
    strcat(newConfig, tmp);
    for (int concat = 2; concat < 5; concat++) {
        strcat(newConfig, configBlocks[concat]);
        strcat(newConfig, "\n");
    }
    strcat(newConfig, "\n");
    strcat(newConfig, dependencies);

    printf("%s\n", newConfig);

    free(tmp);
    free(newConfig);
    free(dependencies);
    free(empty);
    free(configBlocks);
}