//
// Created by j0sh on 6/26/16.
//

#include <algorithm>
#include "function_context.h"
#include "functions/add.h"
#include "functions/vec.h"
#include "functions/get_element.h"

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
    functions.push_back(new add_int_double());
    functions.push_back(new vec());
    functions.push_back(new get_element());
}

type_instance *function_context::apply_function(const std::string &name, const std::vector<type_instance *> &args) {
    std::vector<type *> arg_types(args.size());
    for (size_t i = 0; i < arg_types.size(); i++) {
        arg_types[i] = args[i]->this_type;
    }
    base_function *base_function1 = get_function(name, arg_types);
    return base_function1->apply(args);
}


function_context global_function_context;
