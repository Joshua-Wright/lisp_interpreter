// (c) Copyright 2016 Josh Wright
#include "map.h"
#include "../input/evaluator.h"


LISP_FUNC_IMPL(map) {
    type_instance func = evaluate_ast(args.front(), context);
    vec in = evaluate_ast(args.at(1), context).get_vec();
    vec out(in.size());
    for (size_t i = 0; i < in.size(); i++) {
        out[i] = context.apply_function(func, {ast_node(in[i])});
    }
    return type_instance(out);
}
