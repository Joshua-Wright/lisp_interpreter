// (c) Copyright 2016 Josh Wright
#include "ast_node.h"

ast_node::ast_node(const token &val, const bool called) : val_token(val), is_function_call(called) { }

ast_node::ast_node(type_instance val) : val(val) { }