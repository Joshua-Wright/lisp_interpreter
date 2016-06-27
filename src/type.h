//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_TYPE_H
#define LISP_TYPE_H

#include <string>
#include <vector>

struct type {
    const std::string name;
    const type *parent_type;
    std::vector<const type *> all_grandparent_types;

    // null type
    type() : name("base"), parent_type(nullptr), all_grandparent_types(0) { }

    type(const type *_parent_type, const std::string &name) : parent_type(_parent_type),
                                                              all_grandparent_types(_parent_type->all_grandparent_types) {
        all_grandparent_types.push_back(parent_type);
    }


};

extern const type *T_BASE;
extern const type *T_NUMERIC;
extern const type *T_INT;
extern const type *T_FUNCTION;

struct type_instance {
    const type *this_type;
    const void *data;

    type_instance(const type *this_type, const void *data) : this_type(this_type), data(data) { }
};

#endif //LISP_TYPE_H
