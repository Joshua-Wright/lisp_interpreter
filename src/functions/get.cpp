// (c) Copyright 2016 Josh Wright
#include "get.h"


LISP_FUNC_IMPL(get) {
    // todo non-vector types
    long int idx = evaluate_ast(args.at(0), context).get_int();
    return evaluate_ast(args.at(1), context).get_vec().at((unsigned long) idx);
}