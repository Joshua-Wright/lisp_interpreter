//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_ADD_H
#define LISP_ADD_H

#include <vector>
#include "base_function.h"
#include "../function_matcher.h"
#include "../type.h"

class add_ints : public base_function {

public:

    virtual type_instance *apply(const std::vector<const type_instance*> &args) const;

    virtual bool matches(const std::vector<const type *> &arg_types) const;

    virtual std::string name() const { return "add"; }

};


#endif //LISP_ADD_H
