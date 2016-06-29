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
            // todo this will break when we have variables?
            // can't really do anything about this because we can't guarantee the return type of
            // a function, and therefore can't guarantee what types the children will really be
            head.val = nullptr;
            break;
        }
        default:
            throw std::runtime_error("bad token in tree");
    }
}

