//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_FUNCTION_MATCHER_H
#define LISP_FUNCTION_MATCHER_H

#include <vector>
#include "type.h"
#include "functions/base_function.h"


class function_context {

    std::vector<base_function *> functions;

public:

    function_context();

//    void add_function(const function_type func, const std::vector<type *> &args);

    base_function *get_function(const std::string &name, const std::vector<type *> &arg_types);
};

extern function_context global_function_context;

#endif //LISP_FUNCTION_MATCHER_H
