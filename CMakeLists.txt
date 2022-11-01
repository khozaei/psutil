cmake_minimum_required(VERSION 3.5)

project(psutil)

include_directories(include)

add_executable(psutil_main src/main.c src/psutil.c)

add_library(psutil src/psutil.c)

