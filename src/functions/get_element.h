// (c) Copyright 2015 Josh Wright
#pragma once

#include "base_function.h"

class get_element : public base_function {
public:
    virtual bool matches(const std::vector<type *> &arg_types) override {
        return arg_types.size() == 2 &&
               arg_types[0] == T_INT &&
               arg_types[1] == T_VECTOR;
    }

    virtual type_instance *apply(const std::vector<type_instance *> &args) override {
        return args[1]->vector_data.at((unsigned long) args[0]->int_data);
    }

    virtual std::string name() override {
        return "get";
    }
};