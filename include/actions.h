#ifndef ACTIONS_H
#define ACTIONS_H

#include <tool_builder/tool_builder.h>

// option manipulation commands.
extern void set_check_interval(const struct tool_builder_args *args);

extern void set_parse_interval(const struct tool_builder_args *args);

extern void set_default_dir_path(const struct tool_builder_args *args);

extern void set_enable_default_dir(const struct tool_builder_args *args);

extern void set_debug_log(const struct tool_builder_args *args);

// list manipulation commands.
extern void add_check(const struct tool_builder_args *args);

extern void add_target(const struct tool_builder_args *args);

extern void add_exclude(const struct tool_builder_args *args);

extern void remove_check(const struct tool_builder_args *args);

extern void remove_target(const struct tool_builder_args *args);

extern void remove_exclude(const struct tool_builder_args *args);

// Show commmands.
extern void list_options(const struct tool_builder_args *args);

extern void list_checks(const struct tool_builder_args *args);

extern void list_targets(const struct tool_builder_args *args);

extern void list_excludes(const struct tool_builder_args *args);

#endif
