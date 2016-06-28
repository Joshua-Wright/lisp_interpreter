//
// Created by j0sh on 6/26/16.
//
#include <vector>
#include "add.h"

type_instance *add_ints::apply(const std::vector<type_instance *> &args) {
    long int sum = 0;
    for (size_t i = 0; i < args.size(); i++) {
        sum += (long int) args[i]->data;
    }
    return new type_instance(T_INT, (void *) sum);
}

bool add_ints::matches(const std::vector<type *> &arg_types) {
    for (auto type : arg_types) {
        if (type != T_INT) {
            return false;
        }
    }
    return true;
}



