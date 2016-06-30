//
// Created by j0sh on 6/26/16.
//

#ifndef LISP_TYPE_H
#define LISP_TYPE_H

#include <string>
#include <vector>
#include <list>

struct type {
    std::string name;
    type *parent_type;
    std::vector<type *> all_grandparent_types;

    // null type
    type() : name("base"), parent_type(nullptr), all_grandparent_types(0) { }

    type(type *_parent_type, std::string name) : parent_type(_parent_type),
                                                 all_grandparent_types(_parent_type->all_grandparent_types) {
        all_grandparent_types.push_back(parent_type);
    }
};

extern type *T_BASE;
extern type *T_NUMERIC;
extern type *T_INT;
extern type *T_DECIMAL;
extern type *T_SEQUENCE;
extern type *T_VECTOR;
extern type *T_LIST;
extern type *T_FUNCTION;

#endif //LISP_TYPE_H
