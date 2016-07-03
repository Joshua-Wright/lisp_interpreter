// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Vec, Empty) {
    type_instance result = evaluate("(vec)");
    ASSERT_EQ(result.get_vec().size(), 0);
}

TEST(Vec, Numbers) {
    type_instance result = evaluate("(vec 1 2 3 3.2)");
    ASSERT_EQ(result.get_vec().size(), 4);
    ASSERT_EQ(result.get_vec()[0].get_int(), 1);
    ASSERT_EQ(result.get_vec()[3].get_decimal(), 3.2);
}

TEST(Vec, Func) {
    type_instance result = evaluate("(vec add vec)");
    ASSERT_EQ(result.get_vec()[0].get<identifier>().str, "add");
    ASSERT_EQ(result.get_vec()[1].get<identifier>().str, "vec");
}
