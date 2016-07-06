// (c) Copyright 2016 Josh Wright
#include <algorithm>
//#include "functions/add.h"

//#include "functions/vec.h"
//#include "functions/str.h"
//#include "functions/get_element.h"
//#include "functions/map.h"

#include "function_context.h"


type_lisp_func function_context::get_function(const std::string &name, const std::vector<type_instance> &args) {
    auto f = global_functions.find(name);
    if (f != global_functions.end()) {
        return f->second;
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
    auto func = get_function(func_type.get_identifier().str, args);
    return (func)(args, this);
}

type_instance function_context::apply_function(const type_instance &func_type, const type_instance &arg) {
    return apply_function(func_type, vec(1, arg));
}

bool function_context::has_function(const std::string &name) {
    if (global_functions.find(name) != global_functions.end()) {
        return true;
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


void function_context::_add_function(const std::string &name, type_lisp_func func) {
    global_functions[name] = func;
}

function_context::function_context(function_context *parent_context) : parent_context(parent_context) { }

function_context &global_function_context() {
    static function_context *instance = new function_context(nullptr);
    return *instance;
}


void add_function(const std::string &name, type_lisp_func function) {
    global_function_context()._add_function(name, function);
}

