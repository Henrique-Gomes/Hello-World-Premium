cmake_minimum_required(VERSION 3.12)

project(Hello-World-Premium
	VERSION 0.1
	DESCRIPTION "Hello World Premium"
	LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# load wxwidgets

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

# cli

file(GLOB_RECURSE CLI_SOURCES CONFIGURE_DEPENDS "src/cli/*.cpp")
file(GLOB_RECURSE CLI_HEADERS CONFIGURE_DEPENDS "src/cli/*.h")

add_executable(hwp ${CLI_SOURCES} ${CLI_HEADERS})

# gui

file(GLOB_RECURSE GUI_SOURCES CONFIGURE_DEPENDS "src/gui/*.cpp")
file(GLOB_RECURSE GUI_HEADERS CONFIGURE_DEPENDS "src/gui/*.h")

add_executable(hwp_gui ${GUI_SOURCES} ${GUI_HEADERS})

## link wxwidgets
target_link_libraries(hwp_gui ${wxWidgets_LIBRARIES})