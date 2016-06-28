// (c) Copyright 2015 Josh Wright

#include "debug.h"

void __test(bool expr, const char* expr_str, const std::string &message, const char *file, int line) {
    if (!expr) {
        std::cerr << basename(file) << ":" << line << "  Test failed: " <<
        message << " : " << expr_str << std::endl;
    }
}