//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_FUNCTION_MATCHER_H
#define LISP_FUNCTION_MATCHER_H

#include <vector>
#include "type.h"
#include "functions/base_function.h"


class _function_matcher {

    std::vector<base_function *> functions;

public:

    _function_matcher();

//    void add_function(const function_type func, const std::vector<type *> &args);

    base_function *get_function(const std::string &name, const std::vector<const type *> &arg_types);
};

extern _function_matcher function_matcher;

#endif //LISP_FUNCTION_MATCHER_H
