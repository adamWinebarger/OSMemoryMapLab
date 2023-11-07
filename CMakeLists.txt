cmake_minimum_required(VERSION 3.0)

project(osmemorymap LANGUAGES C)

add_executable(osmemorymap main.c)

install(TARGETS osmemorymap RUNTIME DESTINATION bin)
