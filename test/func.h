// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Func, ParentContext) {
    function_context context(global_function_context);
    context.add_variable("a", type_instance(2));

    ASSERT_TRUE(context.has_variable("a"));
    ASSERT_EQ(context.get_variable("a").get_int(), 2);

    auto result1 = evaluate("(add a)", context);
    ASSERT_EQ(result1.get_int(), 2);


    global_function_context.add_variable("asdf", type_instance(7));
    context.add_variable("asdf", type_instance(20));

    auto result2 = evaluate("(add asdf)", global_function_context);
    ASSERT_EQ(result2.get_int(), 7);

    auto result3 = evaluate("(add asdf)", context);
    ASSERT_EQ(result3.get_int(), 20);
}

TEST(Func, RealFunction) {
    auto result = evaluate("(defn f (g) (add g 2) ) "
                                   " (f 7) ");
    ASSERT_EQ(result.get_int(), 7 + 2);
}

TEST(Func, VeryBasicRecursion) {
    // todo better recursive example when more builtins are implemented
    // @formatter:off
    auto result = evaluate("(defn d (e) "
                             "(if (bool e) "
                               "1 "
                               "(d 1) "
            // todo the following doesn't work because user-defined-functions evaluate their arguments egarly
//                               "(d (add 1 e) ) "
                               ") "
                             ") "
                           "(d 0) ");
    // @formatter:on
    ASSERT_EQ(result.get_int(), 1);
}
