// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Add, Simple) {
    type_instance result = evaluate_ast(parse_expression("(add 15 2)"), global_function_context);
    ASSERT_EQ(result.get_int(), 15 + 2);
}

TEST(Add, Nested) { // test the evaluator too
    std::string expression = "(add (add 12 30) (add 3 4))";
    ast_node head = parse_expression(expression);
    type_instance result = evaluate_ast(head, global_function_context);
    ASSERT_EQ(result.get_int(), 12 + 30 + 3 + 4);
}

TEST(Add, DoubleInt) {
    type_instance result = evaluate_ast(parse_expression("(add 15 3.75)"), global_function_context);
    ASSERT_EQ(result.get_decimal(), 15 + 3.75);
}

TEST(Add, Empty) {
    type_instance result = evaluate_ast(parse_expression("(add)"), global_function_context);
    ASSERT_EQ(result.get_int(), 0);
}
