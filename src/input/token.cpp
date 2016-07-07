// (c) Copyright 2016 Josh Wright
#include "token.h"

token::token(const std::string &value, token_type type) : type(type), literal(value) { }

token::token() : type(NA), literal("") { }