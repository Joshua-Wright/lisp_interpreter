// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Get, FromVec) {
    type_instance r1 = evaluate_ast(parse_expression("(get 0 (vec 1 2 3.2))"), global_function_context);
    type_instance r2 = evaluate_ast(parse_expression("(get 2 (vec 1 2 3.2))"), global_function_context);
    ASSERT_EQ(r1.get_int(), 1);
    ASSERT_EQ(r2.get_decimal(), 3.2);
}
