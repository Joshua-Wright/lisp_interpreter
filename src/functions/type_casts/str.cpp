// (c) Copyright 2016 Josh Wright
#include <string>
#include "../../input/evaluator.h"
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
        auto a = evaluate_ast(arg, context);
        out += boost::apply_visitor(to_str(), a);
    }
    return type_instance(out);
}
