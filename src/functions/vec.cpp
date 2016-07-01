// (c) Copyright 2016 Josh Wright
#include "vec.h"
#include "../debug.h"

type_instance vec::apply(const std::vector<type_instance> &args) {
    return type_instance::vec_copy(args);
}