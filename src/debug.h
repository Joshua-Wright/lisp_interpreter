// (c) Copyright 2016 Josh Wright
#pragma once

#include <iostream> // for std::cerr and std::endl
#include <typeinfo> // for typeid(T).name()
#include <cstring> // for strlen() and basename()
#include <cxxabi.h> // for abi::__cxa_demangle()

/*use this basename() if your <string.h> doesn't provide one*/
//const char* basename(const char* string) {
//    /*simple basename function which doesn't require dynamically allocating a
//     * second C String*/
//    const char *first = string;
//    const char *last = string + strlen(string);
//    const char *current = last;
//    while (current > first) {
//        if (*(current -1) == '/') {
//            break;
//        }
//        current--;
//    }
//    return current;
//}

template<typename T>
void __debug_log(T v, const char *l, const char *f, int line, bool p) {
    /*debug logger that uses template type resolution to print whatever we give it*/
    std::cerr << basename(f) << ":" << line << " ";
    if (p) {
        /*gcc-specific way to demangle the type names, probably not portable*/
        std::cerr << abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL) <<
        " ";
    }
    std::cerr << l << "=" << v << std::endl;
}

#define debug_log(x) __debug_log(x, #x, __FILE__, __LINE__, true)
#define debug_log_type(x) __debug_log(x, #x, __FILE__, __LINE__, true)
#define debug_log_notype(x) __debug_log(x, #x, __FILE__, __LINE__, false)
