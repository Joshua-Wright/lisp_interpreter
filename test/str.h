// (c) Copyright 2016 Josh Wright
#pragma once

#include <gtest/gtest.h>
#include "../src/function_context.h"
#include "../src/input/tokenizer.h"
#include "../src/input/evaluator.h"

TEST(Str, Int) {
    type_instance result = evaluate("(str 5)");
    ASSERT_EQ(result.get_str(), "5");
}

TEST(Str, Func) {
    type_instance result = evaluate("(str add vec)");
    ASSERT_EQ(result.get_str(), "addvec");
}

TEST(Str, IntConcat) {
    type_instance result = evaluate("(str 5 8)");
    ASSERT_EQ(result.get_str(), "58");
}

TEST(Str, Vec) {
    type_instance result = evaluate("(str (vec 2 3))");
    ASSERT_EQ(result.get_str(), "(2, 3)");
}

TEST(Str, Literal) {
    type_instance result = evaluate("(str \"test\")");
    ASSERT_EQ(result.get_str(), "test");
}

TEST(Str, ConcatLiterals) {
    type_instance result = evaluate("(str \"test\" \"asdf\")");
    ASSERT_EQ(result.get_str(), "testasdf");
}

TEST(Str, LiteralEscapes) {
    type_instance result = evaluate("(str \"te\\nst\\\" asdf \\\", \\\t \n\")");
    ASSERT_EQ(result.get_str(), "tenst\" asdf \", \t \n");
}
