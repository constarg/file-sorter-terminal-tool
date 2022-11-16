#include <actions.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        // help message.
    } else if (!strcmp(argv[1], "--set-check-interval"))
    {
    } else if (!strcmp(argv[1], "--set-parse-interval"))
    {
    } else if (!strcmp(argv[1], "--set-default-dir-path"))
    {
    } else if (!strcmp(argv[1], "--set-enable-default-dir"))
    {
    } else if (!strcmp(argv[1], "--set-debug-log"))
    {
    } else if (!strcmp(argv[1], "--add-check"))
    {
    } else if (!strcmp(argv[1], "--add-target"))
    {
    } else if (!strcmp(argv[1], "--add-exclude"))
    {
    } else if (!strcmp(argv[1], "--remove-check"))
    {
    } else if (!strcmp(argv[1], "--remove-target"))
    {
    } else if (!strcmp(argv[1], "--remove-exclude"))
    {
    } else if (!strcmp(argv[1], "--list-options"))
    {
    } else if (!strcmp(argv[1], "--list-checks"))
    {
    } else if (!strcmp(argv[1], "--list-targets"))
    {
    } else if (!strcmp(argv[1], "--list-excludes"))
    {
    } else {
    }

	return 0;
}
