// (c) Copyright 2016 Josh Wright
#include "map.h"

LISP_FUNC_IMPL(map_splat) {
    type_instance func = args.front();
    vec out(args.size() - 1);
    for (size_t i = 1; i < args.size(); i++) {
        out[i - 1] = context->apply_function(func, args[i]);
    }
    return type_instance(out);
}

LISP_FUNC_MATCHER(map_splat) {
    return args.size() >= 2 &&
           args[0].is_identifier();
}


LISP_FUNC_IMPL(map_vec) {
    type_instance func = args.front();
    vec out(args[1].get_vec().size());
    for (size_t i = 0; i < args[1].get_vec().size(); i++) {
        out[i] = context->apply_function(func, args[1].get_vec()[i]);
    }
    return type_instance(out);
}

LISP_FUNC_MATCHER(map_vec) {
    return args.size() >= 2 &&
           args[0].is_identifier() &&
           args[1].is_vec();
}
