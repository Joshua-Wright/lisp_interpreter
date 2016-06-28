// (c) Copyright 2015 Josh Wright
#include <algorithm>

#include <stdexcept>
#include "../debug.h"
#include "parser.h"

void parse_ast(ast_node &head, function_context &context) {
    // evaluate all children
    for (auto &n : head.children) {
        parse_ast(n, context);
    }
    // finally, evaluate this expression
    switch (head.val_token.type) {
        case token::INT:
            head.val = new type_instance(T_INT, (void *) std::stol(head.val_token.literal));
            break;
        case token::DECIMAL:
            head.val = new type_instance(T_DECIMAL, new double(std::stod(head.val_token.literal)));
            break;
        case token::IDENTIFIER: {
            // assume all identifiers refer to functions
            // todo this will break when we have variables
            std::vector<type *> arg_types(head.children.size());
            std::transform(head.children.begin(), head.children.end(), arg_types.begin(), [](ast_node n) {
                return n.val->this_type;
            });
            type_instance *func = new type_instance(T_FUNCTION, (void *) context.get_function(head.val_token.literal, arg_types));
            // don't evaluate functions here, do it in the evaluator
            head.val = func;
            break;
        }
        default:
            throw std::runtime_error("bad token in tree");
    }
}

