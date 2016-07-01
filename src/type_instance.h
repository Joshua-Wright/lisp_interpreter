// (c) Copyright 2016 Josh Wright

class type_instance;

#ifndef LISP_TYPE_INSTANCE
#define LISP_TYPE_INSTANCE

#include <string>
#include <vector>
#include <list>
#include "functions/base_function.h"
#include "debug.h"

class type_instance {
    type_instance(type *this_type) : this_type(this_type), int_data(0) { };
public:
    type *this_type;
    union {
        long int int_data;
        double decimal_data;
        std::vector<type_instance> vector_data;
        std::list<type_instance> list_data;
        base_function *function_data;
    };

    type_instance(base_function *data) : this_type(T_FUNCTION), function_data(data) { }

    type_instance(const long int &data) : this_type(T_INT), int_data(data) { }

    type_instance(const int &data) : this_type(T_INT), int_data(data) { }

    type_instance(const double &data) : this_type(T_DECIMAL), decimal_data(data) { }

    static type_instance vec_of_size(const size_t &size) {
        type_instance t(T_VECTOR);
        // can't use the copy assignment operator because that would implicitly
        // call the destructor on the uninitialized vector
        memset(&t.vector_data, 0, sizeof(std::vector<type_instance>));
        new(&t.vector_data) std::vector<type_instance>(size);
        return t;
    }

    static type_instance vec_copy(const std::vector<type_instance> &other) {
        type_instance t(T_VECTOR);
        memset(&t.vector_data, 0, sizeof(std::vector<type_instance>));
        new(&t.vector_data) std::vector<type_instance>(other);
        return t;
    }

    type_instance(type_instance &&rhs) : this_type(rhs.this_type) {
        if (this_type == T_VECTOR) {
            new(&vector_data) std::vector<type_instance>(rhs.vector_data);
        } else if (this_type == T_LIST) {
            new(&list_data) std::list<type_instance>(rhs.list_data);
        } else if (this_type == T_INT) {
            int_data = rhs.int_data;
        } else if (this_type == T_DECIMAL) {
            decimal_data = rhs.decimal_data;
        } else if (this_type == T_FUNCTION) {
            function_data = rhs.function_data;
        }
    }

    type_instance(const type_instance &rhs) : this_type(rhs.this_type) {
        if (this_type == T_VECTOR) {
            vector_data = rhs.vector_data;
        } else if (this_type == T_LIST) {
            list_data = rhs.list_data;
        } else if (this_type == T_INT) {
            int_data = rhs.int_data;
        } else if (this_type == T_DECIMAL) {
            decimal_data = rhs.decimal_data;
        } else if (this_type == T_FUNCTION) {
            function_data = rhs.function_data;
        }
    }

    type_instance &operator=(const type_instance &rhs) {
        this->~type_instance();
        this_type = rhs.this_type;
        if (this_type == T_LIST) {
            list_data = rhs.list_data;
        } else if (this_type == T_VECTOR) {
            vector_data = rhs.vector_data;
        } else if (this_type == T_INT) {
            int_data = rhs.int_data;
        } else if (this_type == T_DECIMAL) {
            decimal_data = rhs.decimal_data;
        } else if (this_type == T_FUNCTION) {
            function_data = rhs.function_data;
        }
        return *this;
    }

    type_instance() : this_type(nullptr), int_data(0) { }

    virtual ~type_instance() {
        if (this_type == T_VECTOR) {
            vector_data.~vector();
        } else if (this_type == T_LIST) {
            list_data.~list();
        }
    }
};


#endif //LISP_TYPE_INSTANCE