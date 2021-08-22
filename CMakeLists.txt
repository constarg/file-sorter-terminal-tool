cmake_minimum_required(VERSION 3.19)
project(File_Sorter_Terminal_Tool C)

set(CMAKE_C_STANDARD 99)

add_executable(sorter main.c tools/command_actions.c tools/include/command_actions.h tools/config_handler.c tools/include/config_handler.h tools/argument_parser.c tools/include/argument_parser.h)