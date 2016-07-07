// (c) Copyright 2016 Josh Wright
#include "bool.h"

// todo visitor


LISP_FUNC_IMPL(bool) {
    type_instance t = evaluate_ast(args[0], context);
    if (t.is_int()) {
        return type_instance(t.get_int() != 0);
    } else if (t.is_double()) {
        return type_instance(t.get_double() != 0.0);
    }
    return type_instance(true);
}
