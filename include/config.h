#ifndef CONFIG_H
#define CONFIG_H

#include <memory.h>

/**
 * ------------------
 *  Config Options
 * ------------------
 */
struct conf_opt 
{
    char *c_check_intrv;      // Check interval.
    char *c_parse_intrv;      // Parse interval.
    char *c_debu_log;         // Debug log.
    char *c_default_dir_p;    // default directory path.
    char *c_enable_p;         // enable default directory.
};

/**
 * ----------------
 *  Config Lists
 * ----------------
 */
struct conf_lists
{
    char *(*c_check_list);      // Check list.
    char *(*c_target_list);     // Target list.
    char *(*c_exclude_list);    // Exclude list.
};

struct conf 
{
    struct conf_opt c_options; // The options of the config.
    struct conf_lists c_lists; // The lists of the config.
};


static void init_conf(struct conf *src)
{
    memset(src, 0x0, sizeof(struct conf));
}

/**
 * Write the config file contents.
 * @param src The buffer that contains the changed content.
 * @return 0 on success or -1 on error.
 */
extern int write_config(const struct conf *src);

/**
 * Reads the config file contents and
 * store them in a buffer.
 * @param dst The destination buffer.
 * @return 0 on success or -1 on error.
 */
extern int read_config(struct conf *dst);


#endif
