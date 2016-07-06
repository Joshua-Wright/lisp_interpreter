// (c) Copyright 2016 Josh Wright
#ifndef LISP_ADD_H
#define LISP_ADD_H

#include <vector>
#include "../function_context.h"
//#include "../type_instance.h"




__LISP_FUNC_PROTOTYPE(add);
std::string add = "add";

add_function(add, &__lisp_add);

__LISP_FUNC_PROTOTYPE(add) {
    return type_instance(0);
}

//
//LISP_FUNC_MATCHER(add_ints);
//
//
//LISP_FUNC_IMPL(add_int_double);
//
//LISP_FUNC_MATCHER(add_int_double);


#endif //LISP_ADD_H
