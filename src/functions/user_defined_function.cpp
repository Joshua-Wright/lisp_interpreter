// (c) Copyright 2016 Josh Wright
#include "../function_context.h"
#include "user_defined_function.h"
#include "../input/evaluator.h"

user_defined_function::user_defined_function(const std::string &name,
                                             std::vector<std::string> args,
                                             ast_node head_node,
                                             function_context &context)
        : name(name), arg_names(args), head_node(head_node), parent_context(context) {
}

bool user_defined_function::matches(vec args) {
    return args.size() == arg_names.size();
}

type_instance user_defined_function::apply(vec args) {
    function_context context(parent_context);
    for (size_t i = 0; i < args.size(); i++) {
        context.add_variable(arg_names[i], args[i]);
    }
    return evaluate_ast(head_node, context);
}

std::string user_defined_function::get_name() { return name; }