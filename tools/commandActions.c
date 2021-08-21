#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "include/commandActions.h"
#include "include/configHandler.h"
#include "include/argumentParser.h"

void replace(int, char *, char *, int);

void list(char *, char *);

void replaceOptionValues(int, char *, char *, char *);

void add(char **, char **, char *, char *, int);

int isValidIntValue(char *, char **, int);

int countItems(char *, char *);


void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--set-check-interval [value] Change the value of check interval.\n"
           "\t--set-parse-interval [value] Change the value of parse interval.\n"
           "\t--set-default-dir-path [path] Change the default directory path.\n"
           "\t--set-debug-log [value] 0:1 Change the log to debug mode (1).\n"
           "\t--add-check [path] Add new check.\n"
           "\t--add-target [ext] [path] Add new target.\n"
           "\t--remove-check [path] remove check.\n"
           "\t--remove-target [ext] [path] remove target.\n"
           "\t--list-checks list checks.\n"
           "\t--list-targets list targets.\n"
           "\t--list-options list options.\n");

    exit(0);
}
// TODO add and remove functions.

void setter(struct commandP commandP, char *newValue) {
    replace(commandP.index, commandP.identifier_one, newValue, commandP.isAddOrInteger);
}

void listContent(struct commandP commandP) {
    list(commandP.identifier_one, commandP.identifier_two);
}

void replaceOptionValues(int blockIndex,
                         char *config,
                         char *blockName,
                         char *newValue) {

    char **configBlocks = calloc(5, sizeof(char *));
    char *blockSplitter = "\n";
    char *tmp = NULL;
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

    char *valueOfInterest = calloc(strlen(newValue) + 1, sizeof(char));

    // allocate the appropriate space for new value.
    char *saveNewValue = calloc(strlen(tmp) + (strlen(newValue) - valueOfInterestLen) + 2, sizeof(char));
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


void replace(int index, char *block, char *newValue, int isInteger) {
    char *check;

    if (isInteger) {
        if (isValidIntValue(newValue, &check, 0) == -1) {
            free(check);
            return;
        }
    }

    char *config = NULL;

    if (readConfig(&config) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }

    replaceOptionValues(index, config, block, newValue);
    free(config);
}

void addOrRemove(struct commandP commandP, char **toDeleteOrAdd) {
    char *config = NULL;

    if (readConfig(&config) == -1) return;

    char *start = strstr(config, commandP.identifier_one);
    char *tmp = calloc(sizeof(char), strlen(start) + 2);
    strcpy(tmp, start);
    char *tmp2 = strstr(tmp, commandP.identifier_two);
    char *save = calloc(sizeof(char*), strlen(tmp2) + 1);
    strcpy(save, tmp2);
    free(tmp);

    char *splitter = "\n";
    char **items = calloc(sizeof(char *), countItems(commandP.identifier_one,commandP.identifier_two));
    char *currentItem = strtok(start, splitter);

    size_t tmpLen;
    int counter = 0;
    while (strcmp(currentItem, commandP.identifier_two) != 0) {
        tmpLen = strlen(currentItem) + 1;
        items[counter] = calloc(sizeof(char), tmpLen);
        strncpy(items[counter], currentItem, tmpLen);
        currentItem = strtok(NULL, splitter);
        counter++;
    }

    // TODO form the right string in case of target. exp. add .py + " " + path and then call the add function.
    if (commandP.isAddOrInteger) add(&config, items, save, toDeleteOrAdd[2], counter);
    // TODO make the remove function.

    free(config);
    free(save);
}

void add(char **config,
         char **items,
         char *missingPart,
         char *toAdd,
         int itemCount) {

    char **tmp = calloc(sizeof(char *), itemCount + 2);
    size_t totalSize = 0;

    // add the new item to the array.
    for (int item = 0; item < itemCount; item++) {
        tmp[item] = calloc(sizeof(char), strlen(items[item]) + 2);
        strcpy(tmp[item], items[item]);
        strcat(tmp[item], "\n");
        free(items[item]);
    }
    tmp[itemCount] = calloc(sizeof(char), strlen(toAdd) + 2);
    strcpy(tmp[itemCount], toAdd);
    strcat(tmp[itemCount], "\n");
    free(items);

    // find the total size of items.
    for (int item = 0; item < itemCount + 1; item++) totalSize += sizeof(tmp[item]);
    // add the rest.
    totalSize += strlen(*config) + strlen(missingPart) + strlen(toAdd) + 9;
    // allocate space.
    char *newConfig = calloc(sizeof(char), totalSize);
    // form the new config.
    strcpy(newConfig, *config);
    strcat(newConfig, "\n");
    for (int item = 1; item < itemCount + 1; item++) strcat(newConfig, tmp[item]);
    strcat(newConfig, missingPart);
    // free
    for (int item = 0; item < itemCount + 1; item++) free(tmp[item]);

    writeConfig(newConfig, totalSize);

    free(newConfig);
    free(tmp);
}


int countItems(char *startBlock, char *endBlock) {
    char *config = NULL;

    if (readConfig(&config) == -1) return -1;

    char *start = strstr(config, startBlock);
    char *currItem = strtok(start, "\n");
    int counter = 0;

    while (strcmp(currItem, endBlock) != 0) {
        ++counter;
        currItem = strtok(NULL, "\n");
    }

    free(config);
    return counter;
}


int isValidIntValue(char *value, char **result, int returnIntRes) {

    char *integer = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(integer, value);

    int check = strtol(value, &value, 10);

    if (check == 0 && integer[0] != '0') {
        return -1;
    }
    if (returnIntRes) return check;

    *result = integer;
    return 0;
}

void list(char *begin, char *end) {
    char *config = NULL;

    if (readConfig(&config) == -1) return;

    char *start = strstr(config, begin);
    char *currItem = strtok(start, "\n");

    if (start != NULL) {
        while (currItem != NULL && strcmp(currItem, end) != 0) {
            printf("[*] %s\n", currItem);
            currItem = strtok(NULL, "\n");
        }

    }
    free(config);
}