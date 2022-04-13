cmake_minimum_required(VERSION 3.19)
project(file_sorter_terminal_Tool C)

set(CMAKE_C_STANDARD 17)

set(HEADERS_FILES )
set(SOURCE_FILES main.c)

set(TOOL_BUILDER_REL v1.5)
set(TOOL_BUILDER https://github.com/rounnus/terminal-tool-builder-lib/releases/download/${TOOL_BUILDER_REL}/libtoolbuilder.a)
set(TOOL_BUILDER_DEST ../lib/libtoolbuilder.a)

set(TOOL_BUILDER_H https://raw.githubusercontent.com/rounnus/terminal-tool-builder-lib/main/include/tool_builder.h)
set(TOOL_BUILDER_H_DEST ../include/tool_builder/tool_builder.h)

set(PATH ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT EXISTS ${TOOL_BUILDER_DEST})
	message(STATUS "Start downloading libtoolbuilder.a")
	message(STATUS "Downloading from ${TOOL_BUILDER}")
	file(DOWNLOAD ${TOOL_BUILDER} ${TOOL_BUILDER_DEST})
	message(STATUS "Download complete")
endif()

if (NOT EXISTS ${TOOL_BUILDER_H_DEST})
	message(STATUS "Start downloading tool_builder.h")
	message(STATUS "Downloading from ${TOOL_BUILDER_H}")
	file(DOWNLOAD ${TOOL_BUILDER_H} ${TOOL_BUILDER_H_DEST})
	message(STATUS "Download complete")
endif()

add_executable(sorter ${HEADERS_FILES} ${SOURCE_FILES})

target_link_libraries(sorter ${PATH}/lib/libtoolbuilder.a)

install(FILES build/sorter PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE DESTINATION /usr/bin/)

include_directories(./include)
