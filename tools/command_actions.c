#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <command/command_actions.h>
#include <config/config_handler.h>
#include <parsing/argument_parser.h>

#define OPTION_NUMBER           6
#define SPLITTER                "\n"
#define CHANGE_LINE             "\n"

#define TARGET_IDENTIFIER       "[targets]"
#define CHECK_IDENTIFIER        "[check]"
#define CHECK_DONE_IDENTIFIER   "[done_check]"

#define OPTIONS_START           "check_interval"

void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--set-check-interval      [value] Change the value of check interval.\n"
           "\t--set-parse-interval      [value] Change the value of parse interval.\n"
           "\t--set-default-dir-path    [path] Change the default directory path.\n"
           "\t--set-enable-default-dir  [value] 0:1 Enable the to transfer files in default dir.\n"
           "\t--set-debug-log           [value] 0:1 Change the log to debug mode (1).\n"
           "\t--add-check               [path] Add new check.\n"
           "\t--add-target              [ext] [path] Add new target.\n"
           "\t--remove-check            [row number] remove check.\n"
           "\t--remove-target           [row number] remove target.\n"
           "\t--list-checks list checks.\n"
           "\t--list-targets list targets.\n"
           "\t--list-options list options.\n");

    exit(0);
}

void setter(struct command_p c_command_p, char *new_value) {

}

void list_content(struct command_p c_command_p) {

}

void list(char *begin, char *end) {

}
