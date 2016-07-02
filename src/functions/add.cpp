// (c) Copyright 2016 Josh Wright
#include <vector>
#include "add.h"
#include "../type_instance.h"
#include "../debug.h"

LISP_FUNC_IMPL(add_ints) {
    long int sum = 0;
    for (auto &arg : args) {
        sum += arg.get<long>();
    }
    return type_instance(sum);
}

LISP_FUNC_MATCHER(add_ints) {
    for (auto &t : args) {
        if (!t.is<long>()) {
            return false;
        }
    }
    return true;
}

LISP_FUNC_IMPL(add_int_double) {
    double sum = 0;
    for (auto &arg : args) {
        if (arg.is<double>()) {
            sum += arg.get<double>();
        } else if (arg.is<long>()) {
            sum += arg.get<long>();
        }
    }
    return type_instance(sum);
}

LISP_FUNC_MATCHER(add_int_double) {
    for (auto &t : args) {
        if (!(t.is<long>() || t.is<double>())) {
            return false;
        }
    }
    return true;
}
