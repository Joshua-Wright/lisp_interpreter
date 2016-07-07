// (c) Copyright 2016 Josh Wright
#pragma once

#include <string>

struct token {
    enum token_type {
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        STRING,
        IDENTIFIER,
        INT,
        DECIMAL,
        NA
    };
    token_type type;
    std::string literal;

    token(const std::string &value, token_type type);

    token();
};