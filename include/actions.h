#ifndef ACTIONS_H
#define ACTIONS_H

// option manipulation commands.
/**
 * Change the value of the check interval option
 * in config file.
 */
extern void set_check_interval(const char *n_value);

/**
 * Change the value of the parse interval option
 * in config file.
 */
extern void set_parse_interval(const char *n_value);

/**
 * Change the default dir path, where the
 * files sent when no rule has been set.
 */
extern void set_default_dir_path(const char *n_path);

/**
 * Enable or disable the default dir
 * feature. This works by changing
 * the value of the corresponded value
 * in config file.
 */
extern void set_enable_default_dir(const char *n_state);

/**
 * Enable or disable the debug log
 * feature. This works by changing
 * the value of the corresponded value
 * in config file.
 */
extern void set_debug_log(const char *n_state);

// list manipulation commands.
/**
 * Add a new path on the check list that the core
 * will scan for files.
 */
extern void add_check(const char *path);

/**
 * Add a new rule on the target list that the core
 * checks in order to organize the files.
 * @param args The information that the builder pass to the callback.
 */
extern void add_target(const char *ext, const char *path);

/**
 * Add a new rule on the exlude list that the core
 * checks in order to exclude files.
 */
extern void add_exclude(const char *ext, const char *path);

/**
 * Remove a path from the check list that the core
 * will scan for files.
 */
extern void remove_check(const char *row);

/**
 * Remove a rule from the target list that the core
 * checks in order to organize the files.
 */
extern void remove_target(const char *row);

/**
 * Remove a rule from the exlude list that the core
 * checks in order to exclude files.
 */
extern void remove_exclude(const char *row);

// Show commands.
/**
 * Show the available options.
 */
extern void list_options();

/**
 * Show the list of path's in check list.
 * @param args The information that the builder pass to the callback.
 */
extern void list_checks();

/**
 * Show the list of rules in target list.
 */
extern void list_targets();

/**
 * Show the list of rules in exclude list.
 */
extern void list_excludes();

#endif
