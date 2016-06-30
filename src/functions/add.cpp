//
// Created by j0sh on 6/26/16.
//
#include <vector>
#include "add.h"

type_instance *add_ints::apply(const std::vector<type_instance *> &args) {
    long int sum = 0;
    for (size_t i = 0; i < args.size(); i++) {
        sum += args[i]->int_data;
    }
    return new type_instance(sum);
}

bool add_ints::matches(const std::vector<type *> &arg_types) {
    for (auto type : arg_types) {
        if (type != T_INT) {
            return false;
        }
    }
    return true;
}


type_instance *add_int_double::apply(const std::vector<type_instance *> &args) {
    double sum = 0;
    for (auto arg : args) {
        if (arg->this_type == T_INT) {
            sum += arg->int_data;
        } else if (arg->this_type == T_DECIMAL) {
            sum += arg->decimal_data;
        }
    }
    return new type_instance(sum);
}

bool add_int_double::matches(const std::vector<type *> &arg_types) {
    for (auto type : arg_types) {
        if (type != T_INT && type != T_DECIMAL) {
            return false;
        }
    }
    return true;
}



