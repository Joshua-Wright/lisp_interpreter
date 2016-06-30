//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_BASE_FUNCTION_H
#define LISP_BASE_FUNCTION_H

#include <vector>
#include "../type.h"

class base_function : public type_instance {

public:
    base_function() : type_instance(T_FUNCTION, this) { }

    virtual bool matches(const std::vector<type *> &arg_types) = 0;

    virtual type_instance *apply(const std::vector<type_instance *> &args) = 0;

    virtual std::string name() = 0;
};


#endif //LISP_BASE_FUNCTION_H
