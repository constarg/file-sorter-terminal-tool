#include <stdio.h>

#include "actions.h"
#include "config.h"

/**
 * This functions chagnes a value of one of
 * the options in the config file.
 * @param n_value The new value to write.
 * @param wtchange The option to change.
 */
static void change_value(const char *n_value,
                         const char *wtchange)
{
    

}

int set_check_interval(const char *n_value)
{

}

int set_parse_interval(const char *n_value)
{

}

int set_default_dir_path(const char *n_path)
{

}

int set_enable_default_dir(const char *n_state)
{

}

int set_debug_log(const char *n_state)
{
}

int add_check(const char *path)
{
}

int add_target(const char *ext, const char *path)
{
}

int add_exclude(const char *ext, const char *path)
{
}

int remove_check(const char *row)
{
}

int remove_target(const char *row)
{
}

int remove_exclude(const char *row)
{
}

int list_options()
{
}

int list_checks()
{
}
  
int list_targets()
{
}

int list_excludes()
{
}
