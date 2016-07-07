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
        src/ast_node.cpp
        src/ast_node.h
        src/debug.h
        src/forward_declarations.h
        src/function_context.cpp
        src/function_context.h
        src/functions/add.cpp
        src/functions/add.h
        src/functions/defn.cpp
        src/functions/defn.h
        src/functions/get.cpp
        src/functions/get.cpp
        src/functions/get.h
        src/functions/get.h
        src/functions/if.cpp
        src/functions/if.h
        src/functions/map.cpp
        src/functions/map.h
        src/functions/type_casts/bool.cpp
        src/functions/type_casts/bool.h
        src/functions/type_casts/str.cpp
        src/functions/type_casts/str.h
        src/functions/user_defined_function.cpp
        src/functions/user_defined_function.h
        src/functions/var.cpp
        src/functions/var.h
        src/functions/vec.cpp
        src/functions/vec.h
        src/input/evaluator.cpp
        src/input/evaluator.h
        src/input/token.cpp
        src/input/token.h
        src/input/tokenizer.cpp
        src/input/tokenizer.h
        src/type_instance.cpp
        src/type_instance.h
        )

set(TEST_FILES
        test/all_tests.cpp
        test/add.h
        test/map.h
        test/str.h
        test/vec.h
        test/get.h
        test/var.h
        test/func.h
        test/bool.h
        test/if.h
        )

add_executable(all_test ${SOURCE_FILES} ${TEST_FILES})

