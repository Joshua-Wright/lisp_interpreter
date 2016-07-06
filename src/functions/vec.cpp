// (c) Copyright 2016 Josh Wright
#include "vec.h"
#include "../input/evaluator.h"
#include "../function_context.h"


LISP_FUNC_IMPL(vec) {
    vec out(args.size());
    for (size_t i = 0; i < out.size(); i++) {
        out[i] = evaluate_ast(args[i], context);
    }
    return type_instance(out);
}
