cmake_minimum_required(VERSION 3.10)

# TODO create release and debug targets

# set the project name
project(Hello-World-Premium
	VERSION 0.1
	DESCRIPTION "Hello World Premium"
	LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# set build tree path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add the executable
add_executable(hwp ${SOURCES})