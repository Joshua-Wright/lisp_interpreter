// (c) Copyright 2015 Josh Wright

#include <iostream>
#include <string>
#include "../src/type.h"
#include "../src/tokenizer.h"

int main(int argc, char const *argv[]) {
    using std::string;
    using std::cout;
    using std::endl;

    {
        string src = "( asdf23ADG (add 3.123 4 ))";
        auto tree = parse_expression(src);
        print_ast(tree);
    }

    return 0;
}
