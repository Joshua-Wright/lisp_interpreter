// (c) Copyright 2016 Josh Wright
#include <algorithm>
#include "function_context.h"
#include "functions/add.h"
#include "functions/vec.h"
#include "functions/get_element.h"

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

function_context::function_context() {
    functions.push_back(function_pair("add", lisp_add_ints_impl, lisp_add_ints_matcher));
    functions.push_back(function_pair("add", lisp_add_int_double_impl, lisp_add_int_double_matcher));
    functions.push_back(function_pair("vec", lisp_vec_impl, lisp_vec_matcher));
    functions.push_back(function_pair("get", lisp_get_impl, lisp_get_matcher));
}

type_instance function_context::apply_function(const type_instance &func_type, const std::vector<type_instance> &args) {
    function_pair func = get_function(func_type.get<identifier>().str, args);
    return (*func.func)(args, this);
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
