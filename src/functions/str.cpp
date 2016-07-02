// (c) Copyright 2016 Josh Wright
#include <string>
#include "str.h"

using std::string;
using std::to_string;

class to_str : public boost::static_visitor<string> {
public:

    template<typename T>
    string operator()(const T &v) const {
        return to_string(v);
    }

    string operator()(const std::vector<type_instance> &v) const {
        string out("(");
        for (size_t i = 0; i < v.size(); i++) {
            out += boost::apply_visitor(to_str(), v[i]);
            if (i != v.size() - 1) {
                out += ", ";
            }
        }
        out += ")";
        return out;
    }

    string operator()(const std::list<type_instance> &v) const {
        string out("(");
        // todo fix this
        for (auto &arg : v) {
            out += boost::apply_visitor(to_str(), arg);
            out += ", ";
        }
        return out;
    }

    string operator()(const string &v) const {
        return v;
    }

    string operator()(const identifier &v) const {
        return v.str;
    }

};


LISP_FUNC_IMPL(str) {
    string out;
    for (auto &arg : args) {
        out += boost::apply_visitor(to_str(), arg);
    }
    return type_instance(out);
}

LISP_FUNC_MATCHER(str) { return true; }
