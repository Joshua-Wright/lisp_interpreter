// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"


TEST(Bool, FromInt) {
    auto result = evaluate("(bool 1)");
    ASSERT_EQ(result.get_bool(), true);
    result = evaluate("(bool 0)");
    ASSERT_EQ(result.get_bool(), false);
}

TEST(Bool, FromDouble) {
    auto result = evaluate("(bool 1.0)");
    ASSERT_EQ(result.get_bool(), true);
    result = evaluate("(bool 0.0)");
    ASSERT_EQ(result.get_bool(), false);
}