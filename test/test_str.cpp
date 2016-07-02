// (c) Copyright 2016 Josh Wright
#include <iostream>
#include "../src/input/evaluator.h"
#include "../src/debug.h"

int main(int argc, char const *argv[]) {
    {
        type_instance result = evaluate_ast(parse_expression("(str 5)"), global_function_context);
        test(result.get_str() == "5", "string");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(str add vec)"), global_function_context);
        test(result.get_str() == "addvec", "string");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(str 5 8)"), global_function_context);
        test(result.get_str() == "58", "string");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(str (vec 2 3))"), global_function_context);
        test(result.get_str() == "(2, 3)", "string");
    }
    return 0;
}
