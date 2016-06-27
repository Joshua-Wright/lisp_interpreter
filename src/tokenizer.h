//
// Created by j0sh on 6/17/16.
//

#ifndef LISP_TOKENIZER_H
#define LISP_TOKENIZER_H

#include <vector>
#include <string>

struct token {
    enum token_type {
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        IDENTIFIER,
        NUMBER,
        NA
    };
    token_type type;
    std::string value;

    token(const std::string &value, token_type type) : value(value), type(type) { }
    token() : value(""), type(NA) {}
};

struct ast_node {
    token val;
    std::vector<ast_node> children;

    ast_node(const token &val) : val(val) { }
};


ast_node parse_expression(const std::string &input);

void print_ast(const ast_node &head, size_t depth = 0);


#endif //LISP_TOKENIZER_H
