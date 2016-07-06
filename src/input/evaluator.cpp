// (c) Copyright 2016 Josh Wright
#include <algorithm>
#include <vector>
#include <stdexcept>
//#include "../functions/user_defined_function.h"
//#include "../debug.h"
#include "evaluator.h"

type_instance evaluate_ast(const ast_node &head, function_context &context) {
    // handle variables first
    if (context.has_variable(head.val_token.literal)) {
        type_instance var = context.get_variable(head.val_token.literal);
        // but even more importantly, handle variables storing functions
        if (head.is_function_call) {
            return context.apply_function(var, head.children);
        } else {
            return var;
        }
    }
    if (!head.is_function_call) {
        return head.val;
    }
    return context.apply_function(head.val, head.children);
}

type_instance evaluate(const std::string &expression, function_context &context) {
    type_instance result;
    for (auto &head_node : parse_expression(expression)) {
        result = evaluate_ast(head_node, context);
    }
    return result;
}

type_instance evaluate(const std::string &expression) {
    return evaluate(expression, global_function_context);
}
