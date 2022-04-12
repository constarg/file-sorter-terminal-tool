#include <tool_builder/tool_builder.h>



int main(int argc, char *argv) {
	struct tool_builder builder; 
	tool_builder_init(&builder);

	tool_builder_destroy(&builder);
	return 0;
}
