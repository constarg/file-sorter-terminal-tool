#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "include/commandActions.h"
#include "include/configHandler.h"
#include "include/argumentParser.h"

#define OPTION_NUMBER 5

void list(char *begin, char *end);
void replaceOption(char *option, int optionIndex, char *newValue, int isInteger);
void setOption(char *option, char **options, char *newValue, int index, char *missing, size_t prevConfSize);

int isValidIntValue(char *value, char **result, int returnIntRes);


void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--set-check-interval [value] Change the value of check interval.\n"
           "\t--set-parse-interval [value] Change the value of parse interval.\n"
           "\t--set-default-dir-path [path] Change the default directory path.\n"
           "\t--set-debug-log [value] 0:1 Change the log to debug mode (1).\n"
           "\t--add-check [path] Add new check.\n"
           "\t--add-target [ext] [path] Add new target.\n"
           "\t--remove-check [row number] remove check.\n"
           "\t--remove-target [row number] remove target.\n"
           "\t--list-checks list checks.\n"
           "\t--list-targets list targets.\n"
           "\t--list-options list options.\n");

    exit(0);
}
// TODO add and remove functions.
// TODO replace function.

void setter(struct commandP commandP, char *newValue) {
    replaceOption(commandP.identifier_one, commandP.index, newValue, commandP.isAddOrInteger);
}

void listContent(struct commandP commandP) {
    list(commandP.identifier_one, commandP.identifier_two);
}

void replaceOption(char *option, int optionIndex, char *newValue, int isInteger) {
    char *config = NULL;
    // read the config file.
    if (readConfig(&config) == -1) return;

    size_t confSize = strlen(config);
    // allocate space to save all the previous options.
    char **options = calloc(OPTION_NUMBER, sizeof(char *));
    char *missing = calloc(confSize + 1, sizeof(char));

    strncpy(missing, config, confSize);
    // save the checks and targets.
    char *missingFields = strstr(missing, "[check]");
    // save the options.
    char *splitter = "\n";
    options[0] = strtok(config, splitter);

    for (int index = 1; index < OPTION_NUMBER; index++)
        options[index] = strtok(NULL, splitter);

    // check if is an integer.
    if (isInteger) {
        char *integerValue;
        if (isValidIntValue(newValue, &integerValue, 0))
            setOption(option, options, newValue, optionIndex, missingFields, confSize);

        free(integerValue);
    }
    else setOption(option, options, newValue, optionIndex, missingFields, confSize);

    free(missing);
    free(options);
    free(config);
}

void setOption(char *option,
               char **options,
               char *newValue,
               int index,
               char *missing,
               size_t prevConfSize) {

    // Allocate space for the interested string.
    size_t newOptionSize = strlen(option) + strlen(newValue) + 2;
    char *changedOption = calloc(newOptionSize, sizeof(char));
    // form the new option.
    strcpy(changedOption, option);
    strcat(changedOption, " ");
    strcat(changedOption, newValue);

    // calculate the size of the new config.
    size_t oldOptionSize = strlen(options[index]);
    size_t defOfSize = (newOptionSize > oldOptionSize)? (newOptionSize - oldOptionSize): (oldOptionSize - newOptionSize);
    size_t newConfSize = (newOptionSize > oldOptionSize)? (prevConfSize + defOfSize) : (prevConfSize - defOfSize);

    // temporary save the changed option.
    options[index] = changedOption;
    // form the new config.
    char *newConfig = calloc(newConfSize, sizeof(char));

    strcpy(newConfig, options[0]);
    for (int save = 1; save < OPTION_NUMBER; save++) {
        strcat(newConfig, "\n");
        strcat(newConfig, options[save]);
    }
    strcat(newConfig, "\n\n");
    strcat(newConfig, missing);

    // save the changes.
    writeConfig(newConfig, newConfSize);
    free(newConfig);
    free(changedOption);
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
    return 1;
}

void list(char *begin, char *end) {
    char *config = NULL;

    if (readConfig(&config) == -1) return;

    char *start = strstr(config, begin);
    char *currItem = strtok(start, "\n");
    int counter = 1;

    if (start != NULL) {
        while (currItem != NULL && strcmp(currItem, end) != 0) {
            if (strcmp(begin, currItem) == 0) {
                currItem = strtok(NULL, "\n");
                continue;
            }
            printf("[*] [%d] %s\n", counter, currItem);
            currItem = strtok(NULL, "\n");
            counter++;
        }

    }
    free(config);
}