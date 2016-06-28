//
// Created by j0sh on 6/26/16.
//

#include <algorithm>
#include "function_context.h"
#include "functions/add.h"

base_function *function_context::get_function(const std::string &name, const std::vector<type *> &arg_types) {
    for (base_function *func: functions) {
        if (func->name() == name && func->matches(arg_types)) {
            return func;
        }
    }
    return nullptr;
}

function_context::function_context() {
    functions.push_back(new add_ints());
}

function_context global_function_context;

