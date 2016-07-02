// (c) Copyright 2016 Josh Wright
#include <iostream>
#include "../src/input/evaluator.h"
#include "../src/debug.h"

int main(int argc, char const *argv[]) {
    {
        type_instance result = evaluate_ast(parse_expression("(str (map str 15 3))"), global_function_context);
        test(result.get_str() == "(15, 3)", "map to splat args");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(str (map str (vec 15 3 7)))"), global_function_context);
        test(result.get_str() == "(15, 3, 7)", "map to vector");
    }
    return 0;
}
