// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Variables, Simple) {
    global_function_context().add_variable("seven", type_instance(7));
    type_instance result = evaluate("(add seven 4)");
    ASSERT_EQ(result.get_int(), 7 + 4);
}

TEST(Variables, UsingVar) {
    type_instance result = evaluate("(var a 7) (add a 4)");
    ASSERT_EQ(result.get_int(), 7 + 4);
}

TEST(Variables, StoreFunction) {
    type_instance result = evaluate("(var b add) (b 3 4)");
    ASSERT_EQ(result.get_int(), 3 + 4);
}

TEST(Variables, Overwrite) {
    type_instance result = evaluate("(var c 7) (var c 2) (add c 4)");
    ASSERT_EQ(result.get_int(), 2 + 4);
}
