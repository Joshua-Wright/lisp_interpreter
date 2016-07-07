// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(If, True) {
    auto result = evaluate("(if (bool 1) 5 2.123)");
    ASSERT_EQ(result.get_int(), 5);
}

TEST(If, False) {
    auto result = evaluate("(if (bool 0) 8.0 123.0)");
    ASSERT_EQ(result.get_double(), 123.0);
}
