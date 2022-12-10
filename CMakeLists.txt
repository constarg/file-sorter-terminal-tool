cmake_minimum_required(VERSION 3.19)
project(file_sorter_terminal_Tool C)

set(CMAKE_C_STANDARD 17)

set(HEADERS_FILES include/actions.h include/config.h)
set(SOURCE_FILES src/main.c src/actions.c src/config.c)

set(TOOL_BUILDER_REL v1.5)
set(TOOL_BUILDER https://github.com/EmbeddedCat/terminal-tool-builder-lib/releases/download/${TOOL_BUILDER_REL}/libtoolbuilder.a)
set(TOOL_BUILDER_DEST ../lib/libtoolbuilder.a)

add_executable(sorter ${HEADERS_FILES} ${SOURCE_FILES})

install(FILES build/sorter PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE DESTINATION /usr/bin/)

include_directories(./include)
