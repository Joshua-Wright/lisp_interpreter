// (c) Copyright 2016 Josh Wright
#include "if.h"

LISP_FUNC_IMPL(if) {
    // todo validate args
    if (evaluate_ast(args[0], context).get_bool()) {
        return evaluate_ast(args[1], context);
    } else {
        return evaluate_ast(args[2], context);
    }
}
