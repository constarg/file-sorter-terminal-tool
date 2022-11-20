#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "actions.h"
#include "config.h"

/**
 * This functions chagnes a value of one of
 * the options in the config file.
 * @param n_value The new value to write.
 * @param wtchange The option to change.
 */
static int change_opt_value(const char *n_value,
                            const char *wtchange)
{
    struct config conf;
    init_config(&conf);
    parse_config(&conf);

    if (!strcmp(wtchange, CHECK_INT)) {
        conf.c_options.o_check_interval = atoi(n_value);
        if (conf.c_options.o_check_interval == 0) return -1;
    } else if (!strcmp(wtchange, PARSE_INT)) {
        conf.c_options.o_parse_interval = atoi(n_value);
        if (conf.c_options.o_parse_interval == 0) return -1;
    } else if (!strcmp(wtchange, DEBUG_LOG)) {
        conf.c_options.o_debug_log = atoi(n_value) & 0x1;
    } else if (!strcmp(wtchange, DEFAULT_DIR)) {
        free(conf.c_options.o_default_path);
        conf.c_options.o_default_path = (char *) strdup(n_value);
        // TODO - check if the path exist?
    } else if (!strcmp(wtchange, EN_DEFAULT)) {
        conf.c_options.o_enable_default = atoi(n_value) & 0x1;
    } else {
        return -1;
    }

    if (update_config(&conf) == -1) return -1;
    destroy_config(&conf);
    return 0;
}

int set_check_interval(const char *n_value)
{
    change_opt_value(n_value, CHECK_INT);
}

int set_parse_interval(const char *n_value)
{
    change_opt_value(n_value, PARSE_INT);
}

int set_debug_log(const char *n_state)
{
    change_opt_value(n_state, DEBUG_LOG);
}

int set_default_dir_path(const char *n_path)
{
    change_opt_value(n_path, DEFAULT_DIR);
}

int set_enable_default_dir(const char *n_state)
{
    change_opt_value(n_state, EN_DEFAULT);
}

int set_mv_without_ext(const char *n_state)
{
    change_opt_value(n_state, WITHOUT_EXT);
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
    struct config conf;
    init_config(&conf);
    parse_config(&conf);
 
    printf("%s %d\n",   CHECK_INT,   conf.c_options.o_check_interval);
    printf("%s %d\n",   PARSE_INT,   conf.c_options.o_parse_interval);
    printf("%s %d\n",   DEBUG_LOG,   conf.c_options.o_debug_log);
    printf("%s %s\n",   DEFAULT_DIR, conf.c_options.o_default_path);
    printf("%s %d\n",   EN_DEFAULT,  conf.c_options.o_enable_default);
    printf("%s %d\n\n", WITHOUT_EXT, conf.c_options.o_move_no_ext);

    destroy_config(&conf);
    return 0;
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
