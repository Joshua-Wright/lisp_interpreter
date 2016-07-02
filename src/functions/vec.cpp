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


//type_instance vec::apply(const std::vector<type_instance> &args) {
//    return type_instance::vec_copy(args);
//}
