// (c) Copyright 2016 Josh Wright
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "evaluator.h"
#include "../debug.h"

using std::vector;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

type_instance evaluate_ast(const ast_node &head, function_context &context) {
    // evaluate all children
    vector<type_instance> child_results;
    for (size_t i = 0; i < head.children.size(); i++) {
        child_results.push_back(evaluate_ast(head.children[i], context));
    }
    // finally, evaluate this expression
    if (head.val.is_int() || head.val.is_decimal() || head.val.is_str()) {
        return head.val;
    } else if (head.val.is_identifier()) {
        // functions must be applied
        // assume all identifiers refer to functions
        // todo this will break when we have variables (e.g. from user defined functions)
        if (head.is_function_call) {
            return context.apply_function(head.val, child_results);
        } else if (context.has_function_by_name(head.val.get_identifier().str)) {
            return head.val;
        }
    }
    throw std::runtime_error("bad token in tree: " + head.val_token.literal);
}

#pragma clang diagnostic pop

type_instance evaluate(const std::string &expression, function_context &context) {
    return evaluate_ast(parse_expression(expression), context);
}

type_instance evaluate(const std::string &expression) {
    return evaluate_ast(parse_expression(expression), global_function_context);
}
