cmake_minimum_required(VERSION 3.12)

project(Hello-World-Premium
	VERSION 0.1
	DESCRIPTION "Hello World Premium"
	LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Load wxWidgets

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

# Common library

file(GLOB_RECURSE COMMON_CPP CONFIGURE_DEPENDS "src/common/*.cpp")
list(APPEND COMMON_SOURCES ${COMMON_CPP})

file(GLOB_RECURSE COMMON_H CONFIGURE_DEPENDS "src/common/*.h")
list(APPEND COMMON_SOURCES ${COMMON_H})

add_library(hwp_common ${COMMON_SOURCES})

target_include_directories(hwp_common PUBLIC "include")

# CLI

file(GLOB_RECURSE CLI_CPP CONFIGURE_DEPENDS "src/cli/*.cpp")
list(APPEND CLI_SOURCES ${CLI_CPP})

file(GLOB_RECURSE CLI_H CONFIGURE_DEPENDS "src/cli/*.h")
list(APPEND CLI_SOURCES ${CLI_H})

add_executable(hwp ${CLI_SOURCES})

target_link_libraries(hwp PUBLIC hwp_common)

# GUI

file(GLOB_RECURSE GUI_CPP CONFIGURE_DEPENDS "src/gui/*.cpp")
list(APPEND GUI_SOURCES ${GUI_CPP})

file(GLOB_RECURSE GUI_H CONFIGURE_DEPENDS "src/gui/*.h")
list(APPEND GUI_SOURCES ${GUI_H})

if(WIN32)
	file(GLOB_RECURSE GUI_RC CONFIGURE_DEPENDS "src/gui/*.rc")
	list(APPEND GUI_SOURCES ${GUI_RC})
endif()

add_executable(hwp_gui WIN32 ${GUI_SOURCES})

target_link_libraries(hwp_gui PUBLIC hwp_common)

## Link wxWidgets
target_link_libraries(hwp_gui PUBLIC ${wxWidgets_LIBRARIES})