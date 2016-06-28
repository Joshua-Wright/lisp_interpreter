// (c) Copyright 2015 Josh Wright

#include <iostream>
#include "../src/debug.h"
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/parser.h"
#include "../src/input/evaluator.h"

int main(int argc, char const *argv[]) {

    { // test without evaluation
        base_function *func = global_function_context.get_function("add", {T_INT, T_INT});
        type_instance arg1(T_INT, (void *) 1);
        type_instance arg2(T_INT, (void *) 2);
        type_instance *result = func->apply(std::vector<type_instance *>{&arg1, &arg2});

        test(result->type_data == (void *) 3, "addition error");
    }
    { // test the evaluator too
        std::string expression = "(add 3 4)";
        ast_node head = parse_expression(expression);
        print_ast(head);
        parse_ast(head, global_function_context);
        type_instance *result = evaluate_ast(head, global_function_context);

        test(((long int) result->type_data) == 7, "evaluation and addition");
    }

    std::cout << "tests complete" << std::endl;

    return 0;
}
