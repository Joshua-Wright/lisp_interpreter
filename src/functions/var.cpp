// (c) Copyright 2016 Josh Wright
#include "var.h"


LISP_FUNC_IMPL(var) {
    std::string identifier = args.front().val_token.literal;
    type_instance val = evaluate_ast(args[1], context);
    context.add_variable(identifier, val);
    return val;
}
