cmake_minimum_required(VERSION 3.0.0)
project(AccountManagement)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -Wall -O0 -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -Wall -O3")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall -O3")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
include_directories("${PROJECT_SOURCE_DIR}/include")
link_directories("${PROJECT_SOURCE_DIR}/lib")
aux_source_directory(src DIR_SRCS)

add_executable(main ${DIR_SRCS})
target_link_libraries(main pthread)
target_link_libraries(main m)
