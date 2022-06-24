cmake_minimum_required(VERSION 3.10.2)
project(ringbuffer C)
set(CMAKE_BUILD_TYPE "Debug")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(include)

add_executable(sender
src/sender.c
)

add_executable(receiver
src/receiver.c
)

