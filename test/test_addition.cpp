// (c) Copyright 2016 Josh Wright

#include <iostream>
#include "../src/debug.h"
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

int main(int argc, char const *argv[]) {

    { // test without evaluation
        base_function *func = global_function_context.get_function("add", {T_INT, T_INT});
        type_instance *arg1 = new type_instance(1);
        type_instance *arg2 = new type_instance(2);
        type_instance *result = func->apply(std::vector<type_instance *>{arg1, arg2});

        test(result->int_data == 3, "addition error");
    }
    { // test the evaluator too
        std::string expression = "(add (add 12 30) (add 3 4))";
        ast_node head = parse_expression(expression);
        type_instance *result = evaluate_ast(head, global_function_context);
        test(result->int_data == 12 + 30 + 3 + 4, "evaluation and addition");
        test(result->this_type == T_INT, "addition");
    }
    {
        type_instance *result = evaluate_ast(parse_expression("(add 15 3.75)"), global_function_context);
        test(result->decimal_data == 15 + 3.75, "floating point addition");
        test(result->this_type == T_DECIMAL, "floating point addition");
    }
    {
        type_instance *result = evaluate_ast(parse_expression("(add)"), global_function_context);
        test(result->int_data == 0, "empty function call");
        test(result->this_type == T_INT, "empty function call");
    }

    std::cout << "tests complete" << std::endl;
    return 0;
}
