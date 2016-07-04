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

    // special case skip evaluating the variable name since it isn't defined yet
    if (head.val.is_identifier() && head.val.get_identifier().str == "var") {
        context.add_variable(
                head.children.at(0).val.get_identifier().str,
                evaluate_ast(head.children.at(1), context)
        );
        return context.get_variable(head.children.at(0).val.get_identifier().str);
    }

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
        std::string id = head.val.get_identifier().str;
        // todo this will break when we have variables (e.g. from user defined functions)
        if (head.is_function_call) {
            // apply function stored in variable
            if (context.has_variable(id)) {
                return context.apply_function(context.get_variable(id), child_results);
            } else {
                return context.apply_function(head.val, child_results);
            }
        } else if (context.has_variable(id)) {
            return context.get_variable(id);
        } else if (context.has_function(id)) {
            return head.val;
        }
    }
    throw std::runtime_error("evaulate_ast: bad token in tree: " + head.val_token.literal);
}

#pragma clang diagnostic pop

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
