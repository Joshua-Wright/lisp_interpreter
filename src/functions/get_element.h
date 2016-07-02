// (c) Copyright 2016 Josh Wright
#pragma once

#include "base_function.h"


LISP_FUNC_IMPL(get) {
    return args.at(1).get<std::vector<type_instance>>().at((unsigned long) args.at(0).get<long>());
}

LISP_FUNC_MATCHER(get) {
    return args.at(0).is<long>() && args.at(1).is<std::vector<type_instance>>();
}



//class get_element : public base_function {
//public:
//    virtual bool matches(const std::vector<type *> &arg_types) override {
//        return arg_types.size() == 2 &&
//               arg_types[0] == T_INT &&
//               arg_types[1] == T_VECTOR;
//    }
//
//    virtual type_instance apply(const std::vector<type_instance> &args) override {
//        return args[1].get<std::vector<type_instance>>().at((unsigned long) args[0].get<long>());
//    }
//
//    virtual std::string name() override {
//        return "get";
//    }
//};