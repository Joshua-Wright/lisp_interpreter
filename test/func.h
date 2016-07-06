// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Func, ParentContext) {
    function_context context(global_function_context());
    context.add_variable("a", type_instance(2));
    auto result = evaluate("(add a)", context);
    ASSERT_EQ(result.get_int(), 2);
}

TEST(Func, RealFunction) {
    auto result = evaluate("(defn f (g) (add g 2) ) "
                                   " (f 7) ");
    ASSERT_EQ(result.get_int(), 7 + 2);
}