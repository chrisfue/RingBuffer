cmake_minimum_required(VERSION 3.10.2)
project(ringbuffer C)
set(CMAKE_BUILD_TYPE "Debug")


include_directories(include)

add_library(${PROJECT_NAME}_library SHARED
    src/ringbuffer.c
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(sender
src/sender.c
src/ringbuffer.c

)

add_executable(receiver
src/receiver.c
src/ringbuffer.c
)


#add_library( functions
    #include/receiver.h
  #  include/ringbuffer.h
   # src/ringbuffer.c
#)

add_library(functions_library SHARED
    src/ringbuffer.c
)









target_link_libraries(sender PRIVATE functions_library)
