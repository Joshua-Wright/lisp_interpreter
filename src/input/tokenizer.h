// (c) Copyright 2016 Josh Wright
#ifndef LISP_TOKENIZER_H
#define LISP_TOKENIZER_H

#include <vector>
#include <string>
#include "../type_instance.h"

struct token {
    enum token_type {
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        STRING,
        IDENTIFIER,
        INT,
        DECIMAL,
        NA
    };
    token_type type;
    std::string literal;

    token(const std::string &value, token_type type) : type(type), literal(value) { }

    token() : type(NA), literal("") { }
};

struct ast_node {
    token val_token;
    type_instance val;
    bool is_function_call;
    std::vector<ast_node> children;

    ast_node(const token &val, const bool called = false) : val_token(val), is_function_call(called) { }
};


std::vector<ast_node> parse_expression(const std::string &input);

void print_ast(const ast_node &head, size_t depth = 0);


#endif //LISP_TOKENIZER_H
