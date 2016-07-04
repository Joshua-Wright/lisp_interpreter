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


function_context::function_pair function_context::get_function(const std::string &name, const std::vector<type_instance> &args) {
    for (function_pair &p : functions) {
        if (p.name == name && (*p.matcher)(args)) {
            return p;
        }
    }
    if (parent_context != nullptr) {
        return parent_context->get_function(name, args);
    }
    throw std::runtime_error("function not found: " + name);
}

type_instance function_context::apply_function(const type_instance &func_type, const std::vector<type_instance> &args) {
    for (auto &f : user_defined_functions) {
        if (f.get_name() == func_type.get_identifier().str && f.matches(args)) {
            return f.apply(args);
        }
    }
    function_pair func = get_function(func_type.get_identifier().str, args);
    return (*func.func)(args, this);
}

type_instance function_context::apply_function(const type_instance &func_type, const type_instance &arg) {
    return apply_function(func_type, vec(1, arg));
}

bool function_context::has_function(const std::string &name) {
    for (function_pair &p: functions) {
        if (p.name == name) {
            return true;
        }
    }
    if (has_user_defined_function(name)) {
        return true;
    }
    return (parent_context != nullptr && parent_context->has_variable(name));
}

bool function_context::has_variable(const std::string &name) {
    if (parent_context != nullptr && parent_context->has_variable(name)) {
        return true;
    }
    return variables.find(name) != variables.end();
}

void function_context::add_variable(const std::string &name, const type_instance &value) {
    variables[name] = value;
}

type_instance function_context::get_variable(const std::string &name) {
    if (variables.find(name) != variables.end()) {
        return variables[name];
    }
    if (parent_context != nullptr && parent_context->has_variable(name)) {
        return parent_context->get_variable(name);
    }
    throw std::runtime_error("no variable found: " + name);
}

function_context::function_context(const std::initializer_list<function_pair> &functions) : parent_context(nullptr), functions(functions) {
}

function_context::function_context(function_context &parent) : parent_context(&parent) {
}

void function_context::add_function(user_defined_function &function) {
    user_defined_functions.push_back(function);
}

bool function_context::has_user_defined_function(const std::string &name) {
    for (auto &f : user_defined_functions) {
        if (f.get_name() == name) {
            return true;
        }
    }
    return false;
}


#define FUNCTION(name, identifier) {name, lisp_ ## identifier ## _impl, lisp_ ## identifier ## _matcher}
function_context global_function_context({
                                                 FUNCTION("add", add_ints),
                                                 FUNCTION("add", add_int_double),
                                                 FUNCTION("vec", vec),
                                                 FUNCTION("get", get),
                                                 FUNCTION("str", str),
                                                 FUNCTION("map", map_vec),
                                                 FUNCTION("map", map_splat),
                                         });
