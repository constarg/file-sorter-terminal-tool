#include <actions.h>
#include <string.h>
#include <stdio.h>

static const char *help_msg =  "";

static int help()
{
    return printf("%s\n", help_msg);
}


int main(int argc, char *argv[])
{
    if (argv[1] == NULL) {
        return help();
    } else if (!strcmp(argv[1], "--set-check-interval")) {
        if (argv[2] == NULL) return help();
        set_check_interval(argv[1]);
    } else if (!strcmp(argv[1], "--set-parse-interval")) {
        if (argv[2] == NULL) return help();
        set_parse_interval(argv[1]);
    } else if (!strcmp(argv[1], "--set-default-dir-path")) {
        if (argv[2] == NULL) return help();
        set_default_dir_path(argv[2]);
    } else if (!strcmp(argv[1], "--set-enable-default-dir")) {
        if (argv[2] == NULL) return help();
        set_enable_default_dir(argv[2]);
    } else if (!strcmp(argv[1], "--set-debug-log")) {
        if (argv[2] == NULL) return help();
        set_debug_log(argv[2]);
    } else if (!strcmp(argv[1], "--add-check")) {
        if (argv[2] == NULL) return help();
        add_check(argv[2]);
    } else if (!strcmp(argv[1], "--add-target")) {
        if (argv[2] == NULL) return help();
        if (argv[3] == NULL) return help();
        add_target(argv[2], argv[3]);
    } else if (!strcmp(argv[1], "--add-exclude")) {
        if (argv[2] == NULL) return help();
        if (argv[3] == NULL) return help();
        add_exclude(argv[2], argv[3]);
    } else if (!strcmp(argv[1], "--remove-check")) {
        if (argv[2] == NULL) return help();
        remove_check(argv[2]);
    } else if (!strcmp(argv[1], "--remove-target")) {
        if (argv[2] == NULL) return help();
        remove_target(argv[2]);
    } else if (!strcmp(argv[1], "--remove-exclude")) {
        if (argv[2] == NULL) return help();
        remove_exclude(argv[2]);
    } else if (!strcmp(argv[1], "--list-options")) {
        list_options();
    } else if (!strcmp(argv[1], "--list-checks")) {
        list_checks();
    } else if (!strcmp(argv[1], "--list-targets")) {
        list_targets();
    } else if (!strcmp(argv[1], "--list-excludes")) {
        list_excludes();
    } else {
        return help();
    }

	return 0;
}
