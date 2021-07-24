#include <stdio.h>
#include <string.h>
#include "argumentHandler.h"

#define HELP_ARG "--help"
#define ADD_CHECK "--add-check"
#define ADD_TARGET "--add-target"
#define REMOVE_CHECK "--remove-check"
#define REMOVE_TARGET "--remove-target"
#define LIST_CHECKS "--list-checks"
#define LIST_TARGETS "--list-targets"

void help();

void addCheck(char *);

void addTarget(char *, char *);

void removeCheck(char *);

void removeTarget(char *, char *);

void listChecks();

void listTargets();

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

        else if (validateArg(argv[1], NULL, NULL, LIST_CHECKS, 0, 13))
            listChecks();

        else if (validateArg(argv[1], NULL, NULL, LIST_TARGETS, 0, 14))
            listTargets();
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

}

void addTarget(char *ext, char *path) {

}

void removeCheck(char *path) {

}

void removeTarget(char *ext, char *path) {

}

void listChecks() {

}

void listTargets() {

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





