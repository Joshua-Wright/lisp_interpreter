//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_ADD_H
#define LISP_ADD_H

#include <vector>
#include "base_function.h"
#include "../function_context.h"
#include "../type.h"

class add_ints : public base_function {

public:

    virtual type_instance *apply(const std::vector<type_instance *> &args);

    virtual bool matches(const std::vector<type *> &arg_types);

    virtual std::string name() { return "add"; }

};


#endif //LISP_ADD_H
