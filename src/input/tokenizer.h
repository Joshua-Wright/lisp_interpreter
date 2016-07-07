// (c) Copyright 2016 Josh Wright
#ifndef LISP_TOKENIZER_H
#define LISP_TOKENIZER_H
#include <vector>
#include <string>
#include "../forward_declarations.h"
#include "../ast_node.h"
#include "../type_instance.h"


std::vector<ast_node> parse_expression(const std::string &input);

void print_ast(const ast_node &head, size_t depth = 0);


#endif //LISP_TOKENIZER_H
