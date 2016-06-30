// (c) Copyright 2016 Josh Wright

#include <iostream>
#include "../src/debug.h"
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"


int main(int argc, char const *argv[]) {

    {
        type_instance *result = evaluate_ast(parse_expression("(vec)"), global_function_context);
        test(result->vector_data.size() == 0, "empty function call");
        test(result->this_type == T_VECTOR, "empty function call");
    }
    {
        type_instance *result = evaluate_ast(parse_expression("(vec 1 2 3 3.2)"), global_function_context);
        test(result->vector_data.size() == 4, "create vector");
        test(result->vector_data[0]->int_data == 1, "create vector");
        test(result->vector_data[3]->decimal_data == 3.2, "create vector");
        test(result->this_type == T_VECTOR, "create vector");
    }
    {
        type_instance *r1 = evaluate_ast(parse_expression("(get 0 (vec 1 2 3.2))"), global_function_context);
        type_instance *r2 = evaluate_ast(parse_expression("(get 2 (vec 1 2 3.2))"), global_function_context);
        test(r1->this_type == T_INT, "get");
        test(r1->int_data == 1, "get");
        test(r2->this_type == T_DECIMAL, "get");
        test(r2->decimal_data == 3.2, "get");
    }

    std::cout << "tests complete" << std::endl;
    return 0;
}
