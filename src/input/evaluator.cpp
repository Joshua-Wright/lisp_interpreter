// (c) Copyright 2016 Josh Wright
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "evaluator.h"
#include "../debug.h"

using std::vector;
using std::transform;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

type_instance evaluate_ast(const ast_node &head, function_context &context) {
    // evaluate all children
    vector<type_instance> child_results;
    for (size_t i = 0; i < head.children.size(); i++) {
        child_results.push_back(evaluate_ast(head.children[i], context));
    }
    // finally, evaluate this expression
    switch (head.val_token.type) {
        case token::INT:
        case token::DECIMAL:
            // literals are pre-evaluated
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

