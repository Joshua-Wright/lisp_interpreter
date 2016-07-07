// (c) Copyright 2016 Josh Wright
#include <vector>
#include "../input/evaluator.h"
#include "add.h"


type_instance add(const type_instance &a, const type_instance &b) {
    if (a.is_double() && b.is_double()) {
        return type_instance(a.get_double() + b.get_double());

    } else if (a.is_double() && b.is_int()) {
        return type_instance(a.get_double() + b.get_int());

    } else if (a.is_int() && b.is_double()) {
        return type_instance(a.get_int() + b.get_double());

    } else if (a.is_int() && b.is_int()) {
        return type_instance(a.get_int() + b.get_int());

    }
    throw std::runtime_error("bad args to add. types: " + std::string(a.type().name()) + ", " + std::string(b.type().name()));
}

LISP_FUNC_IMPL(add) {
    type_instance sum(0);
    for (auto &arg : args) {
        sum = add(sum, evaluate_ast(arg, context));
    }
    return sum;
}
