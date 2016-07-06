// (c) Copyright 2016 Josh Wright

class function_context;

#ifndef LISP_FUNCTION_MATCHER_H
#define LISP_FUNCTION_MATCHER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "functions/user_defined_function.h"
#include "type_instance.h"

#define LISP_FUNC_IMPL(identifier) type_instance lisp_ ## identifier ## _impl(const std::vector<ast_node> &args, function_context &context)
#define LISP_FUNC_MATCHER(identifier) bool lisp_ ## identifier ## _matcher(std::vector<type_instance> &args)

LISP_FUNC_IMPL(noop);

LISP_FUNC_MATCHER(noop);

typedef decltype(&lisp_noop_impl) type_lisp_func_impl;
typedef decltype(&lisp_noop_matcher) type_lisp_func_matcher;

class function_context {

    function_context *parent_context;

    struct function_pair {
        type_lisp_func_impl func;
        type_lisp_func_matcher matcher;
        const std::string name;

        function_pair(const std::string &name, type_lisp_func_impl f, type_lisp_func_matcher m) : func(f), matcher(m), name(name) { }
    };

    // todo use a map keyed by function name for better efficiency
//    std::vector<function_pair> functions;
    std::vector<user_defined_function> user_defined_functions;
    std::unordered_map<std::string, type_instance> variables;
    std::unordered_map<std::string, type_lisp_func_impl> global_functions;

    type_lisp_func_impl get_function(const std::string &name, const std::vector<ast_node> &args);

    bool has_user_defined_function(const std::string &name);

    function_context();

public:

    function_context(const std::unordered_map<std::string, type_lisp_func_impl> &functions);

    function_context(function_context &parent_context);


    type_instance apply_function(const type_instance &func_type, const std::vector<ast_node> &args);

//    bool has_function(const std::string &name);

    bool has_variable(const std::string &name);

    void add_variable(const std::string &name, const type_instance &value);

    type_instance get_variable(const std::string &name);

    void add_function(user_defined_function &function);

    // todo destructor?

};


extern function_context global_function_context;

#endif //LISP_FUNCTION_MATCHER_H
