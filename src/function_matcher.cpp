//
// Created by j0sh on 6/26/16.
//

#include <algorithm>
#include "function_matcher.h"
#include "functions/add.h"

base_function *_function_matcher::get_function(const std::string &name, const std::vector<const type *> &arg_types) {
    for (base_function *func: functions) {
        if (func->name() == name && func->matches(arg_types)) {
            return func;
        }
    }
    return nullptr;
}

_function_matcher::_function_matcher() {
    functions.push_back(new add_ints());
}


_function_matcher function_matcher;

