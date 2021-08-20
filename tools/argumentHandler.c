#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "include/argumentHandler.h"
#include "include/configHandler.h"
#include "include/argumentParser.h"

void replace(int, char*, char*, int);

extern void list(char*, char*);

void replaceOptionValues(int , char *, char *, char *);

int isValidIntValue(char* , char**);

void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--add-check [path] Add new check\n"
           "\t--add-target [ext] [path] Add new target\n"
           "\t--remove-check [path] remove check\n"
           "\t--remove-target [ext] [path] remove target\n"
           "\t--list-checks list checks\n"
           "\t--list-targets list targets\n");

    exit(0);
}
// TODO add and remove functions.

void setter(struct commandP commandP, char *newValue) {
    replace(commandP.index, commandP.identifier_one, newValue, commandP.isInteger);
}

void listContent(struct commandP commandP) {
    list(commandP.identifier_one, commandP.identifier_two);
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
    free(config);
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

void list(char* begin, char* end) {
    char* config = NULL;

    if (readConfig(&config) == -1) return;

    char *start = strstr(config, begin);
    char *currItem = strtok(start, "\n");

    if (start != NULL) {
        while (strcmp(currItem, end) != 0) {
            printf("[*] %s\n", currItem);
            currItem = strtok(NULL, "\n");
        }

    }
    free(config);
}