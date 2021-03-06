// (c) Copyright 2016 Josh Wright
#ifndef LISP_USER_DEFINED_FUNCTION_H
#define LISP_USER_DEFINED_FUNCTION_H

#include <vector>
#include <string>
#include "../forward_declarations.h"
#include "../ast_node.h"
#include "../type_instance.h"
#include "../function_context.h"

class user_defined_function {
    std::string name;
    std::vector<std::string> arg_names;
    ast_node head_node;
    function_context *parent_context;
public:
    user_defined_function();

    user_defined_function(const std::string &name, std::vector<std::string> args, ast_node head_node, function_context &context);

    type_instance apply(vec args);

    type_instance apply(std::vector<ast_node> args);

    size_t arg_count();

    std::string get_name();

};


#endif //LISP_USER_DEFINED_FUNCTION_H
