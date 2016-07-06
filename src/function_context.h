// (c) Copyright 2016 Josh Wright

class function_context;

#ifndef LISP_FUNCTION_MATCHER_H
#define LISP_FUNCTION_MATCHER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "functions/user_defined_function.h"
#include "type_instance.h"

#define __LISP_FUNCTION_NAME(name) __lisp_##name
#define __LISP_FUNC_PROTOTYPE(name) \
    type_instance __LISP_FUNCTION_NAME(name)(const std::vector<type_instance> &args, function_context *context)

#define LISP_FUNCTION(name) \
    __LISP_FUNC_PROTOTYPE(name); \
    add_function(#name, &__LISP_FUNCTION_NAME(name)); \
    __LISP_FUNC_PROTOTYPE(name)

__LISP_FUNC_PROTOTYPE(noop);

typedef decltype(&__LISP_FUNCTION_NAME(noop)) type_lisp_func;

class function_context {

    function_context *parent_context;

    std::vector<user_defined_function> user_defined_functions;
    std::unordered_map<std::string, type_lisp_func> global_functions;
    std::unordered_map<std::string, type_instance> variables;

    bool has_user_defined_function(const std::string &name);

    type_lisp_func get_function(const std::string &name, const std::vector<type_instance> &args);

public:

    function_context(function_context *parent_context);

    void _add_function(const std::string &name, type_lisp_func func);


    type_instance apply_function(const type_instance &func_type, const std::vector<type_instance> &args);

    bool has_function(const std::string &name);

    bool has_variable(const std::string &name);

    void add_variable(const std::string &name, const type_instance &value);

    type_instance get_variable(const std::string &name);

    void add_function(user_defined_function &function);

    // todo destructor?
    type_instance apply_function(const type_instance &func_type, const type_instance &arg);
};


function_context &global_function_context();

void add_function(const std::string &name, type_lisp_func function);

#endif //LISP_FUNCTION_MATCHER_H
