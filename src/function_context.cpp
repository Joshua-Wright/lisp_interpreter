// (c) Copyright 2016 Josh Wright
#include <algorithm>
#include "forward_declarations.h"
#include "functions/type_casts/str.h"
#include "functions/type_casts/bool.h"
#include "functions/add.h"
#include "functions/vec.h"
#include "functions/get.h"
#include "functions/map.h"
#include "functions/if.h"
#include "functions/var.h"
#include "functions/defn.h"
#include "function_context.h"


type_lisp_func_impl function_context::get_function(const std::string &name, const std::vector<ast_node> &args) {
    auto f = global_functions.find(name);
    if (f != global_functions.end()) {
        return f->second;
    }
    return nullptr;
}

type_instance function_context::apply_function(const type_instance &func_type, const std::vector<ast_node> &args,
                                               function_context &context) {
    // todo throw exception for non-function type
    auto user_func_p = user_defined_functions.find(func_type.get_identifier().str);
    if (user_func_p != user_defined_functions.end()) {
        return user_func_p->second.apply(args);
    }
    auto func = get_function(func_type.get_identifier().str, args);
    if (func != nullptr) {
        return (*func)(args, context);
    }
    if (parent_context != nullptr) {
        return parent_context->apply_function(func_type, args, context);
    }
    // todo separate class for this exception
    throw std::runtime_error("Function not found: " + func_type.get_identifier().str);
}

type_instance function_context::apply_function(const type_instance &func_type, const std::vector<ast_node> &args) {
    return this->apply_function(func_type, args, *this);
}

bool function_context::has_variable(const std::string &name) {
    if (variables.find(name) != variables.end()) {
        return true;
    }
    if (parent_context != nullptr) {
        return parent_context->has_variable(name);
    }
    return false;
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

function_context::function_context(function_context &parent) : parent_context(&parent) {
}

void function_context::add_user_defined_function(user_defined_function function) {
    user_defined_functions[function.get_name()] = function;
}

bool function_context::has_user_defined_function(const std::string &name) {
    if (user_defined_functions.find(name) != user_defined_functions.end()) {
        return true;
    }
    return parent_context != nullptr && parent_context->has_user_defined_function(name);
}

function_context::function_context() { }

function_context::function_context(const std::unordered_map<std::string, type_lisp_func_impl> &functions)
        : global_functions(functions), parent_context(nullptr) { }


function_context global_function_context(
        {
                {"add",  lisp_add_impl},
                {"vec",  lisp_vec_impl},
                {"get",  lisp_get_impl},
                {"map",  lisp_map_impl},
                {"str",  lisp_str_impl},
                {"if",   lisp_if_impl},
                {"bool", lisp_bool_impl},
                {"var",  lisp_var_impl},
                {"defn", lisp_defn_impl},
        }
);