// (c) Copyright 2016 Josh Wright
#pragma once

#include "tokenizer.h"
#include "../function_context.h"

type_instance evaluate_ast(const ast_node &head, function_context &context);

type_instance evaluate(const std::string &expression, function_context &context);

type_instance evaluate(const std::string &expression);
