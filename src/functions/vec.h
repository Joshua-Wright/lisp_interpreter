// (c) Copyright 2016 Josh Wright
#pragma once

#include "base_function.h"
#include "../type.h"
#include "../function_context.h"

LISP_FUNC_IMPL(vec);

LISP_FUNC_MATCHER(vec);


//class vec : public base_function {
//public:
//
//    virtual bool matches(const std::vector<type *> &arg_types) override {
//        // we can make a vector of anything!
//        return true;
//    }
//
//    virtual type_instance apply(const std::vector<type_instance> &args) override;
//
//    virtual std::string name() override {
//        return "vec";
//    }
//};
