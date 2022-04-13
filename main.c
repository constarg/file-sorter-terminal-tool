#include <tool_builder/tool_builder.h>
#include <actions.h>

static void configure_option_commands(struct tool_builder *t_builder)
{
        tool_builder_add_both(t_builder,"--set-check-interval",1,
                              &set_check_interval," [value]\t  Change the value of check interval.");

        tool_builder_add_both(t_builder,"--set-parse-interval",1,
                              &set_parse_interval," [value]\t  Change the value of parse interval.");

        tool_builder_add_both(t_builder,"--set-default-dir-path",1,
                              &set_default_dir_path," [path]\t  Change the default directory path.");

        tool_builder_add_both(t_builder,"--set-enable-default-dir",1,
                              &set_enable_default_dir," [value]  0:1 Enable the to transfer files in default dir.");

        tool_builder_add_both(t_builder,"--set-debug-log",1,
                              &set_debug_log," [value]\t\t  0:1 Change the log to debug mode (1).");

}

static void configure_list_commands(struct tool_builder *t_builder)
{
        tool_builder_add_both(t_builder,"--add-check",1,
                              &add_check," [path]\t\t  Add new check.");

        tool_builder_add_both(t_builder,"--add-target",2,
                              &add_target," [ext] [path]\t  Add new target.");

        tool_builder_add_both(t_builder,"--add-exclude",2,
                              &add_exclude," [ext] [path]\t  Add new exclude.");

        tool_builder_add_both(t_builder,"--remove-check",1,
                              &remove_check," [row number]\t  remove check.");

        tool_builder_add_both(t_builder,"--remove-target",1,
                              &remove_target," [row number]\t  remove target.");

        tool_builder_add_both(t_builder,"--remove-exclude",1,
                              &remove_exclude," [row number]\t  remove exclude.");
}

static void configure_show_commands(struct tool_builder *t_builder)
{
        tool_builder_add_both(t_builder,"--list-options",0,
                              &list_options,"\t\t\t  list options.");

        tool_builder_add_both(t_builder,"--list-checks",0,
                              &list_checks,"\t\t\t  list checks.");

        tool_builder_add_both(t_builder,"--list-targets",0,
                              &list_targets,"\t\t\t  list targets.");

        tool_builder_add_both(t_builder,"--list-excludes",0,
                              &list_excludes,"\t\t\t  list excludes.");
}

static void configure_commands(struct tool_builder *t_builder)
{
        configure_option_commands(t_builder);
        configure_list_commands(t_builder);
        configure_show_commands(t_builder);
}


int main(int argc, char *argv[])
{
	struct tool_builder t_builder;
	tool_builder_init(&t_builder);
        tool_builder_init_help(&t_builder, "sorter");

        tool_builder_set_closing_desc(
                &t_builder,
                "Each of the above commands will print an OK message on success.\n"
                "Check https://github.com/rounnus/file-sorter-core for more information's about the project!\n"
        );
        configure_commands(&t_builder);

        int error = tool_builder_execute(argc, argv, &t_builder);
        if (error != 0)
        {
                tool_builder_call_command("--help", &t_builder);
        }

	tool_builder_destroy(&t_builder);
	return 0;
}
