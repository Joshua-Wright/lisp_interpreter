// (c) Copyright 2016 Josh Wright

class base_function;

#ifndef LISP_BASE_FUNCTION_H
#define LISP_BASE_FUNCTION_H

#include <vector>
#include "../type.h"
#include "../type_instance.h"

class base_function {

public:
    base_function() { }

    virtual bool matches(const std::vector<type *> &arg_types) = 0;

    virtual type_instance apply(const std::vector<type_instance> &args) = 0;

    virtual std::string name() = 0;
};


#endif //LISP_BASE_FUNCTION_H
