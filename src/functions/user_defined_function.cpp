// (c) Copyright 2016 Josh Wright
#include "../function_context.h"
#include "user_defined_function.h"
#include "../input/evaluator.h"

user_defined_function::user_defined_function(const std::string &name,
                                             std::vector<std::string> args,
                                             ast_node head_node,
                                             function_context &context)
        : name(name), arg_names(args), head_node(head_node), parent_context(&context) {
}


type_instance user_defined_function::apply(vec args) {
    if (parent_context == nullptr) {
        // todo exception type
        throw std::runtime_error("tried to call uninitialized user defined function");
    }
    function_context context(*parent_context);
    for (size_t i = 0; i < args.size(); i++) {
        context.add_variable(arg_names[i], args[i]);
    }
    return evaluate_ast(head_node, context);
}

std::string user_defined_function::get_name() { return name; }

size_t user_defined_function::arg_count() { return arg_names.size(); }

type_instance user_defined_function::apply(std::vector<ast_node> args) {
    vec args_values(args.size());
    for (size_t i=0; i<args_values.size(); i++) {
        args_values[i] = evaluate_ast(args[i], *parent_context);
    }
    return apply(args_values);
}

user_defined_function::user_defined_function() : parent_context(nullptr), head_node("") {
}





