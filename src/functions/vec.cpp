// (c) Copyright 2016 Josh Wright
#include "vec.h"
#include "../debug.h"
#include "../function_context.h"


LISP_FUNC_IMPL(vec) {
    return type_instance(args);
}

LISP_FUNC_MATCHER(vec) {
    return true;
}
