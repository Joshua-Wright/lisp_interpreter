// (c) Copyright 2016 Josh Wright

#include <iostream>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"
#include "../src/functions/add.h"
#include "../src/debug.h"

int main(int argc, char const *argv[]) {

    { // test without evaluation
        type_instance arg1(1);
        type_instance arg2(2);
        std::vector<type_instance> args{arg1, arg2};
        type_instance result = global_function_context.apply_function("add", args);
        test(result.get<long>() == 3, "addition error");
    }
    { // test the evaluator too
        std::string expression = "(add (add 12 30) (add 3 4))";
        ast_node head = parse_expression(expression);
        type_instance result = evaluate_ast(head, global_function_context);
        test(result.get<long>() == 12 + 30 + 3 + 4, "evaluation and addition");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(add 15 3.75)"), global_function_context);
        test(result.get<double>() == 15 + 3.75, "floating point addition");
    }
    {
        type_instance result = evaluate_ast(parse_expression("(add)"), global_function_context);
        test(result.get<long>() == 0, "empty function call");
    }

    std::cout << "tests complete" << std::endl;
    return 0;
}
