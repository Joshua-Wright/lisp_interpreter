cmake_minimum_required(VERSION 3.5)
project(lisp)

# for using clang
#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")


#project(assembler C ASM) # this enables building the assembly part of the code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgtest")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES
        src/debug.cpp
        src/debug.h
        src/type_instance.h
        src/function_context.cpp
        src/function_context.h
        src/input/evaluator.cpp
        src/input/evaluator.h
        src/input/tokenizer.cpp
        src/input/tokenizer.h
        src/functions/add.cpp
        src/functions/add.h
        src/functions/vec.cpp
        src/functions/vec.h
        src/functions/get_element.h
        src/functions/str.cpp
        src/functions/str.h
        src/functions/map.cpp
        src/functions/map.h)

set(TEST_FILES
        test/all_tests.cpp
        test/add.h
        test/map.h
        test/str.h
        test/vec.h
        test/get.h)
add_executable(all_test ${SOURCE_FILES} ${TEST_FILES})
