#ifndef ACTIONS_H
#define ACTIONS_H

#include <tool_builder/tool_builder.h>

// option manipulation commands.
/**
 * Change the value of the check interval option
 * in config file.
 * @param args The information that the builder pass to the callback.
 */
extern void set_check_interval(const struct tool_builder_args *args);

/**
 * Change the value of the parse interval option
 * in config file.
 * @param args The information that the builder pass to the callback.
 */
extern void set_parse_interval(const struct tool_builder_args *args);

/**
 * Change the default dir path, where the
 * files sent when no rule has been set.
 * @param args The information that the builder pass to the callback.
 */
extern void set_default_dir_path(const struct tool_builder_args *args);

/**
 * Enable or disable the default dir
 * feature. This works by changing
 * the value of the corresponded value
 * in config file.
 * @param args The information that the builder pass to the callback.
 */
extern void set_enable_default_dir(const struct tool_builder_args *args);

/**
 * Enable or disable the debug log
 * feature. This works by changing
 * the value of the corresponded value
 * in config file.
 * @param args The information that the builder pass to the callback.
 */
extern void set_debug_log(const struct tool_builder_args *args);

// list manipulation commands.
/**
 * Add a new path on the check list that the core
 * will scan for files.
 * @param args The information that the builder pass to the callback.
 */
extern void add_check(const struct tool_builder_args *args);

/**
 * Add a new rule on the target list that the core
 * checks in order to organize the files.
 * @param args The information that the builder pass to the callback.
 */
extern void add_target(const struct tool_builder_args *args);

/**
 * Add a new rule on the exlude list that the core
 * checks in order to exclude files.
 * @param args The information that the builder pass to the callback.
 */
extern void add_exclude(const struct tool_builder_args *args);

/**
 * Remove a path from the check list that the core
 * will scan for files.
 * @param args The information that the builder pass to the callback.
 */
extern void remove_check(const struct tool_builder_args *args);

/**
 * Remove a rule from the target list that the core
 * checks in order to organize the files.
 * @param args The information that the builder pass to the callback.
 */
extern void remove_target(const struct tool_builder_args *args);

/**
 * Remove a rule from the exlude list that the core
 * checks in order to exclude files.
 * @param args The information that the builder pass to the callback.
 */
extern void remove_exclude(const struct tool_builder_args *args);

// Show commands.
/**
 * Show the available options.
 * @param args The information that the builder pass to the callback.
 */
extern void list_options(const struct tool_builder_args *args);

/**
 * Show the list of path's in check list.
 * @param args The information that the builder pass to the callback.
 */
extern void list_checks(const struct tool_builder_args *args);

/**
 * Show the list of rules in target list.
 * @param args The information that the builder pass to the callback.
 */
extern void list_targets(const struct tool_builder_args *args);

/**
 * Show the list of rules in exclude list.
 * @param args The information that the builder pass to the callback.
 */
extern void list_excludes(const struct tool_builder_args *args);

#endif
