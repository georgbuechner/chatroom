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

# add source-files for server
set(SRC_FILES_SERVER
  "src/main.cc"
  "src/server/server_frame.cc"
  "src/users/user_manager.cc"
  "src/users/user.cc"
  "src/util/func.cc"
)

#add source-files for tests
set(SRC_FILES_TESTS 
  "src/server/server_frame.cc"
  "src/server/test_server.cc"
  "src/users/user_manager.cc"
  "src/users/user.cc"
  "src/users/test_user_manager.cc"
  "src/util/func.cc"
  "src/util/test_func.cc"
  )

# Specify, location for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/webserver)

# Create executables.
add_executable(chatroom_server.o ${SRC_FILES_SERVER})
add_executable(chatroom_tests.o ${SRC_FILES_TESTS})

target_include_directories(chatroom_server.o PUBLIC
  "src/server"
  "src/users/"
  "src/util"
)

target_include_directories(chatroom_tests.o PUBLIC
  "src/server"
  "src/users"
  "src/util"
  )

#Add conan files as linked libraries
target_link_libraries(chatroom_server.o PUBLIC ${CONAN_LIBS} stdc++ n)
target_link_libraries(chatroom_tests.o PUBLIC ${CONAN_LIBS} stdc++ n)

