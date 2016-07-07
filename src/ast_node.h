// (c) Copyright 2016 Josh Wright
#pragma once

#include "forward_declarations.h"
#include "input/token.h"
#include "type_instance.h"

struct ast_node {
    token val_token;
    type_instance val;
    bool is_function_call;
    std::vector<ast_node> children;

    ast_node(const token &val, const bool called = false);

    ast_node(type_instance val);
};
