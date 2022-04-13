#include <tool_builder/tool_builder.h>

static void configure_option_commands(struct tool_builder *t_builder)
{
        tool_builder_add_both(
                t_builder,
                "--set-check-interval",
                1,
                NULL,
                "[value] Change the value of check interval."
        );
}

static void configure_list_commands(struct tool_builder *t_builder)
{

}

static void configure_commands(struct tool_builder *t_builder)
{
        configure_option_commands(t_builder);
        configure_list_commands(t_builder);
}


int main(int argc, char *argv[])
{
	struct tool_builder t_builder;
        memset(&t_builder, 0x0, sizeof(struct tool_builder));
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
