// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Map, Vec) {
    type_instance result = evaluate("(str (map str (vec 15 3 7)))");
    ASSERT_EQ(result.get_str(), "(15, 3, 7)");
}
