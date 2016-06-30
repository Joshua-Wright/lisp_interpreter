// (c) Copyright 2015 Josh Wright


class type_instance;

#ifndef LISP_TYPE_INSTANCE
#define LISP_TYPE_INSTANCE

#include <string>
#include <vector>
#include <list>
#include "functions/base_function.h"

class type_instance {
    type_instance(type *this_type) : this_type(this_type) { };
public:
    type *this_type;
    union {
        long int int_data;
        double decimal_data;
        std::vector<type_instance *> vector_data;
        std::list<type_instance *> list_data;
        base_function *function_data;
    };

    type_instance(base_function *data) : this_type(T_FUNCTION), function_data(data) { }

    type_instance(long int data) : this_type(T_INT), int_data(data) { }

    type_instance(int data) : this_type(T_INT), int_data(data) { }

    type_instance(double data) : this_type(T_DECIMAL), decimal_data(data) { }

    static type_instance *vec_of_size(size_t size) {
        type_instance *t = new type_instance(T_VECTOR);
        t->vector_data = std::vector<type_instance *>(size);
        return t;
    }
};


#endif //LISP_TYPE_INSTANCE