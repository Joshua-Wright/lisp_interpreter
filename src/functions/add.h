// (c) Copyright 2016 Josh Wright
#ifndef LISP_ADD_H
#define LISP_ADD_H

#include <vector>
#include "base_function.h"
#include "../function_context.h"
#include "../type.h"


LISP_FUNC_IMPL(add_ints);

LISP_FUNC_MATCHER(add_ints);


LISP_FUNC_IMPL(add_int_double);

LISP_FUNC_MATCHER(add_int_double);


#endif //LISP_ADD_H
