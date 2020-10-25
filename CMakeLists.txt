cmake_minimum_required(VERSION 2.8)

project(chatroom)

# Conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) #Include dependencies added by conan
conan_basic_setup() #links include directories and libraries 

# specify C++ standards and compilation flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O3")
add_compile_options (-fdiagnostics-color=always)

# add source-files
file(GLOB SOURCES_PROGRAMM
  "src/*.cc"
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/webserver)

add_executable(chatroom ${SOURCES_PROGRAMM})
target_link_libraries(chatroom PUBLIC ${CONAN_LIBS})

target_include_directories(chatroom PUBLIC "src")
