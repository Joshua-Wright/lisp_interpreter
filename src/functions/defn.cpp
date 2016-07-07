// (c) Copyright 2016 Josh Wright
#include <vector>
#include "../forward_declarations.h"
#include "defn.h"

LISP_FUNC_IMPL(defn) {

    if (args[0].val_token.type != token::IDENTIFIER) {
        // todo more specific exception type
        throw std::runtime_error("function name must be an identifier");
    }
    std::string name = args[0].val_token.literal;

    // +1 because 'root node' is also a function parameter
    std::vector<std::string> arg_names(1+args[1].children.size());
    // todo typecheck this too
    arg_names[0] = args[1].val_token.literal;
    for (size_t i=1; i<arg_names.size(); i++) {
        arg_names[i] = args[1].children[i-1].val_token.literal;
    }

    const ast_node& root_node = args[2];

    auto func = user_defined_function(name, arg_names, root_node, context);
    context.add_user_defined_function(func);
    // retrun identifier of the name of this function
    return type_instance({name});
}
