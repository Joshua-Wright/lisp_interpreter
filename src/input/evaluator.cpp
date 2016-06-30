// (c) Copyright 2015 Josh Wright

#include <algorithm>
#include <vector>
#include <stdexcept>
#include "evaluator.h"
#include "../debug.h"

using std::vector;
using std::transform;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

type_instance *evaluate_ast(const ast_node &head, function_context &context) {
    // evaluate all children
    vector<type_instance *> child_results(head.children.size());
    transform(head.children.begin(), head.children.end(), child_results.begin(), [&context](ast_node n) {
        return evaluate_ast(n, context);
    });
    // finally, evaluate this expression
    switch (head.val_token.type) {
        case token::INT:
        case token::DECIMAL:
            // literals are simple
            return head.val;
        case token::IDENTIFIER: {
            // functions must be applied
            // assume all identifiers refer to functions
            // todo this will break when we have variables (e.g. from user defined functions)
            return context.apply_function(head.val_token.literal, child_results);
        }
        default:
            throw std::runtime_error("bad token in tree: " + head.val_token.literal);
    }
}

#pragma clang diagnostic pop

