// (c) Copyright 2016 Josh Wright
#pragma once

#include "../type_instance.h"


LISP_FUNC_IMPL(get) {
    return args.at(1).get<std::vector<type_instance>>().at((unsigned long) args.at(0).get<long>());
}

LISP_FUNC_MATCHER(get) {
    return args.at(0).is<long>() && args.at(1).is<std::vector<type_instance>>();
}
