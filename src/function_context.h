// (c) Copyright 2016 Josh Wright
#ifndef LISP_FUNCTION_MATCHER_H
#define LISP_FUNCTION_MATCHER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "type_instance.h"

class function_context;

#define LISP_FUNC_IMPL(identifier) type_instance lisp_ ## identifier ## _impl(const std::vector<type_instance> &args, function_context *context)
#define LISP_FUNC_MATCHER(identifier) bool lisp_ ## identifier ## _matcher(const std::vector<type_instance> &args)

LISP_FUNC_IMPL(noop);

LISP_FUNC_MATCHER(noop);

typedef decltype(&lisp_noop_impl) type_lisp_func_impl;
typedef decltype(&lisp_noop_matcher) type_lisp_func_matcher;

class function_context {

    struct function_pair {
        type_lisp_func_impl func;
        type_lisp_func_matcher matcher;
        const std::string name;

        function_pair(const std::string &name, type_lisp_func_impl f, type_lisp_func_matcher m) : func(f), matcher(m), name(name) { }
    };

    // todo use a map keyed by function name for better efficiency
    std::vector<function_pair> functions;
    std::unordered_map<std::string, type_instance> variables;

    function_pair get_function(const std::string &name, const std::vector<type_instance> &arg_types);

public:

    function_context();

    type_instance apply_function(const type_instance &func_type, const std::vector<type_instance> &args);

    bool has_function(const std::string &name);

    bool has_variable(const std::string &name);

    void add_variable(const std::string &name, const type_instance& value);

    type_instance get_variable(const std::string &name);

    // todo destructor?
    type_instance apply_function(const type_instance &func_type, const type_instance &arg);
};

extern function_context global_function_context;

#endif //LISP_FUNCTION_MATCHER_H
