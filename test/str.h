// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Str, Int) {
    type_instance result = evaluate_ast(parse_expression("(str 5)"), global_function_context);
    ASSERT_EQ(result.get_str(), "5");
}

TEST(Str, Func) {
    type_instance result = evaluate_ast(parse_expression("(str add vec)"), global_function_context);
    ASSERT_EQ(result.get_str(), "addvec");
}

TEST(Str, IntConcat) {
    type_instance result = evaluate_ast(parse_expression("(str 5 8)"), global_function_context);
    ASSERT_EQ(result.get_str(), "58");
}

TEST(Str, Vec) {
    type_instance result = evaluate_ast(parse_expression("(str (vec 2 3))"), global_function_context);
    ASSERT_EQ(result.get_str(), "(2, 3)");
}
