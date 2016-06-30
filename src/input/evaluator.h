// (c) Copyright 2015 Josh Wright
#pragma once

#include "../type.h"
#include "tokenizer.h"
#include "../function_context.h"

type_instance *evaluate_ast(const ast_node &head, function_context &context);