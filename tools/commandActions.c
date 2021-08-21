#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "include/commandActions.h"
#include "include/configHandler.h"
#include "include/argumentParser.h"

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

void setter(struct commandP commandP, char *newValue) {

}

void listContent(struct commandP commandP) {

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