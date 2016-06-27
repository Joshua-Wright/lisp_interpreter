cmake_minimum_required(VERSION 3.5)
project(lisp)

# for using clang
set(CMAKE_C_COMPILER   "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")


#project(assembler C ASM) # this enables building the assembly part of the code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES
        src/function_matcher.cpp
        src/function_matcher.h
        src/tokenizer.cpp
        src/tokenizer.h
        src/type.cpp
        src/type.h
        src/functions/add.cpp src/functions/add.cpp src/functions/add.h src/functions/base_function.h)

add_executable(lisp ${SOURCE_FILES})


add_executable(test_addition ${SOURCE_FILES} test/test_addition.cpp)

add_executable(test_tokenizer src/tokenizer.cpp src/tokenizer.h test/test_tokenizer.cpp)