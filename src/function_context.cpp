// (c) Copyright 2016 Josh Wright
#include <algorithm>

#include "functions/type_casts/str.h"
#include "functions/type_casts/bool.h"
#include "functions/add.h"
#include "functions/vec.h"
#include "functions/get.h"
#include "functions/map.h"
#include "functions/if.h"
#include "functions/var.h"

#include "function_context.h"


type_lisp_func_impl function_context::get_function(const std::string &name, const std::vector<ast_node> &args) {
//    for (function_pair &p : functions) {
//        if (p.name == name && (*p.matcher)(args)) {
//            return p;
//        }
//    }
//    if (parent_context != nullptr) {
//        return parent_context->get_function(name, args);
//    }
    auto f = global_functions.find(name);
    if (f == global_functions.end()) {
        // todo separate class for this exception
        throw std::runtime_error("Function not found: " + name);
    }
    return f->second;
//    throw std::runtime_error("function not found: " + name);
}

type_instance function_context::apply_function(const type_instance &func_type, const std::vector<ast_node> &args) {
//    for (auto &f : user_defined_functions) {
//        if (f.get_name() == func_type.get_identifier().str && f.matches(args)) {
//            return f.apply(args);
//        }
//    }
    auto func = get_function(func_type.get_identifier().str, args);
    return (*func)(args, *this);
}


//bool function_context::has_function(const std::string &name) {
//    for (function_pair &p: functions) {
//        if (p.name == name) {
//            return true;
//        }
//    }
//    if (has_user_defined_function(name)) {
//        return true;
//    }
//    return (parent_context != nullptr && parent_context->has_variable(name));
//}

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

function_context::function_context() {}

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
        }
);