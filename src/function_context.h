// (c) Copyright 2016 Josh Wright
#ifndef LISP_FUNCTION_MATCHER_H
#define LISP_FUNCTION_MATCHER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "forward_declarations.h"
#include "functions/user_defined_function.h"
#include "type_instance.h"

// todo auto-register functions
// todo remove matcher
#define LISP_FUNC_IMPL(identifier) type_instance lisp_ ## identifier ## _impl(const std::vector<ast_node> &args, function_context &context)

LISP_FUNC_IMPL(noop);

typedef decltype(&lisp_noop_impl) type_lisp_func_impl;

class function_context {

    function_context *parent_context;

    std::unordered_map<std::string, user_defined_function> user_defined_functions;
    std::unordered_map<std::string, type_instance> variables;
    std::unordered_map<std::string, type_lisp_func_impl> global_functions;

    type_lisp_func_impl get_function(const std::string &name, const std::vector<ast_node> &args);

    bool has_user_defined_function(const std::string &name);

    function_context();

    type_instance apply_function(const type_instance &func_type, const std::vector<ast_node> &args, function_context &context);

public:

    function_context(const std::unordered_map<std::string, type_lisp_func_impl> &functions);

    function_context(function_context &parent_context);


    type_instance apply_function(const type_instance &func_type, const std::vector<ast_node> &args);

    bool has_variable(const std::string &name);

    void add_variable(const std::string &name, const type_instance &value);

    type_instance get_variable(const std::string &name);

    void add_user_defined_function(user_defined_function function);

};


// todo make this a global getter
extern function_context global_function_context;

#endif //LISP_FUNCTION_MATCHER_H
