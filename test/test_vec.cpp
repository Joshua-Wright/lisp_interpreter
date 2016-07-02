// (c) Copyright 2016 Josh Wright

#include <iostream>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"
#include "../src/debug.h"


int main(int argc, char const *argv[]) {

    {
        type_instance result = evaluate_ast(parse_expression("(vec)"), global_function_context);
        test(result.get_vec().size() == 0, "empty function call");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(vec 1 2 3 3.2)"), global_function_context);
        test(result.get_vec().size() == 4, "create vector");
        test(result.get_vec()[0].get_int() == 1, "create vector");
        test(result.get_vec()[3].get_decimal() == 3.2, "create vector");
    }
    {
        type_instance r1 = evaluate_ast(parse_expression("(get 0 (vec 1 2 3.2))"), global_function_context);
        type_instance r2 = evaluate_ast(parse_expression("(get 2 (vec 1 2 3.2))"), global_function_context);
        test(r1.get_int() == 1, "get");
        test(r2.get_decimal() == 3.2, "get");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(vec add vec)"), global_function_context);
        test(result.get_vec()[0].is<identifier>(), "vector of functions");
        test(result.get_vec()[0].get<identifier>().str == "add", "vector of functions");
        test(result.get_vec()[1].is<identifier>(), "vector of functions");
        test(result.get_vec()[1].get<identifier>().str == "vec", "vector of functions");
    }

    std::cout << "tests complete" << std::endl;
    return 0;
}
