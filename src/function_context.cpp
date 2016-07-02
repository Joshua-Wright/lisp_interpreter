// (c) Copyright 2016 Josh Wright
#include <algorithm>
#include "function_context.h"
#include "functions/add.h"
#include "functions/vec.h"
#include "functions/str.h"
#include "functions/get_element.h"
#include "functions/map.h"

LISP_FUNC_IMPL(noop) {
    return args[0];
}

LISP_FUNC_MATCHER(noop) {
    return args.size() > 0;
}


function_context::function_pair function_context::get_function(const std::string &name, const std::vector<type_instance> &arg_types) {
    for (function_pair &p : functions) {
        if (p.name == name && (*p.matcher)(arg_types)) {
            return p;
        }
    }
    throw std::runtime_error("function not found: " + name);
}

#define ADD_FUNCTION(name, identifier) functions.push_back(function_pair(name, lisp_ ## identifier ## _impl, lisp_ ## identifier ## _matcher));
function_context::function_context() {
    ADD_FUNCTION("add", add_ints);
    ADD_FUNCTION("add", add_int_double);
    ADD_FUNCTION("vec", vec);
    ADD_FUNCTION("get", get);
    ADD_FUNCTION("str", str);
    ADD_FUNCTION("map", map_vec);
    ADD_FUNCTION("map", map_splat);
}

type_instance function_context::apply_function(const type_instance &func_type, const std::vector<type_instance> &args) {
    function_pair func = get_function(func_type.get<identifier>().str, args);
    return (*func.func)(args, this);
}

type_instance function_context::apply_function(const type_instance &func_type, const type_instance &arg) {
    return apply_function(func_type, vec(1, arg));
}

bool function_context::has_function_by_name(const std::string &name) {
    for (function_pair &p: functions) {
        if (p.name == name) {
            return true;
        }
    }
    return false;
}


function_context global_function_context;
