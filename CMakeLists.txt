cmake_minimum_required(VERSION 3.19)
project(File_Sorter_Terminal_Tool C)

set(CMAKE_C_STANDARD 99)

add_executable(sorter main.c tools/commandActions.c tools/include/commandActions.h tools/configHandler.c tools/include/configHandler.h tools/argumentParser.c tools/include/argumentParser.h)