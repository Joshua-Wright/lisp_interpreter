// (c) Copyright 2016 Josh Wright

class type_instance;

#ifndef LISP_TYPE_INSTANCE
#define LISP_TYPE_INSTANCE

#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <boost/variant.hpp>
#include "debug.h"

// simple wrapper to distinguish function identifiers from literal strings
struct identifier {
    std::string str;
};

typedef std::vector<type_instance> vec;

typedef boost::variant<
        bool,
        long,
        double,
        std::string,
        vec,
        std::list<type_instance>,
        identifier
> _type_instance;

class type_instance : public _type_instance {
public:

    // default to an int or whatever
    type_instance() : _type_instance(0l) { };

    template<typename T>
    type_instance(const T &t) : _type_instance(t) { }

    type_instance(const int &t) : _type_instance((long) t) { }

    template<typename T>
    const T &get() const { return boost::strict_get<T>(*this); };

    template<typename T>
    bool is() const {
        try {
            boost::strict_get<T>(*this);
            return true;
        } catch (boost::bad_get) {
            return false;
        }
    };

    const std::string &get_str() const {
        return get<std::string>();
    }

    const long &get_int() const {
        return get<long>();
    }

    const double &get_double() const {
        return get<double>();
    }

    const identifier &get_identifier() const {
        return get<identifier>();
    }

    vec get_vec() const {
        return get<vec>();
    }

    bool is_str() const {
        return is<std::string>();
    }

    bool is_int() const {
        return is<long>();
    }

    bool is_double() const {
        return is<double>();
    }

    bool is_identifier() const {
        return is<identifier>();
    }

    bool is_vec() const {
        return is<vec>();
    }

    bool is_bool() const {
        return is<bool>();
    }

    bool get_bool() const {
        return get<bool>();
    }
};

#endif //LISP_TYPE_INSTANCE