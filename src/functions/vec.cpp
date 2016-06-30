// (c) Copyright 2016 Josh Wright
#include "vec.h"

type_instance *vec::apply(const std::vector<type_instance *> &args) {
    type_instance *vec = type_instance::vec_of_size(args.size());
    for (size_t i = 0; i < args.size(); i++) {
        vec->vector_data[i] = args[i];
    }
    return vec;
}