//
// Created by j0sh on 6/17/16.
//

#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "tokenizer.h"

class token_stream {
    token buffer;
    bool buffer_full;

    std::stringstream instream;

    bool is_whitespace(const char c) {
        return (c == ' ' || c == '\t' || c == '\n');
    }

    bool in_identifier(const char c) {
        if (c >= 'A' && c <= 'Z') {
            return true;
        } else if (c >= 'a' && c <= 'z') {
            return true;
        } else if (c >= '0' && c <= '9') {
            return true;
        } else {
            return false;
        }
    }

    bool starts_identifier(const char c) {
        if (c >= 'A' && c <= 'Z') {
            return true;
        } else if (c >= 'a' && c <= 'z') {
            return true;
        } else {
            return false;
        }
    }

    bool is_numeric(const char c) {
        /* todo add support for negative numbers */
        return (c >= '0' && c <= '9') || c == '.';
    }

public:
    token_stream(const std::string &in) : buffer_full(false), instream(in) { }

    token get() {
        if (buffer_full) {
            buffer_full = false;
            return buffer;
        }
        char c;
        do {
            c = instream.get();
        } while (is_whitespace(c));


        if (c == '(') {
            return token("(", token::OPEN_PARENTHESIS);
        } else if (c == ')') {
            return token(")", token::CLOSE_PARENTHESIS);
        } else if (starts_identifier(c)) {
            std::string buf;
            buf.push_back(c);
            while (in_identifier(instream.peek())) {
                buf.push_back(instream.get());
            }
            return token(buf, token::IDENTIFIER);
        } else if (is_numeric(c)) {
            std::string buf;
            buf.push_back(c);
            while (is_numeric(instream.peek())) {
                buf.push_back(instream.get());
            }
            // numbers with decimal points are decimals
            // todo: this will break if we implement scientific notation
            if (buf.find('.') != std::string::npos) {
                return token(buf, token::DECIMAL);
            } else {
                return token(buf, token::INT);
            };
        } else {
            throw std::runtime_error("unknown character: "
                                     + std::to_string(c)
                                     + ", " + std::string(&c, 1));
        }
    }

    void put_back(token t) {
        if (!buffer_full) {
            buffer_full = true;
            buffer = t;
        } else {
            std::cerr << "buffer " << buffer.literal << std::endl;
            std::cerr << "tried to put back " << t.literal << std::endl;
            throw std::runtime_error("put back on full buffer");
        }
    }

    bool eof() {
        return instream.eof() || instream.peek() == -1;
    }
};

ast_node parse_expression(token_stream &in) {
    if (in.get().type != token::OPEN_PARENTHESIS) {
        throw std::runtime_error("invalid token");
    }

    ast_node cur(in.get());
    while (true) {
        token t = in.get();
        switch (t.type) {
            case token::IDENTIFIER:
            case token::INT:
            case token::DECIMAL:
                cur.children.push_back(ast_node(t));
                break;
            case token::OPEN_PARENTHESIS:
                in.put_back(t);
                cur.children.push_back(parse_expression(in));
                break;
            case token::CLOSE_PARENTHESIS:
                return cur;
            default:
                throw std::runtime_error("bad token");
        }
    }
}

ast_node parse_expression(const std::string &input) {
    token_stream stream(input);
    return parse_expression(stream);
}


void print_ast(const ast_node &head, size_t depth) {
    for (size_t i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    std::cout << head.val_token.literal << " ";
    switch (head.val_token.type) {
        case token::IDENTIFIER:
            std::cout << "identifier";
            break;
        case token::INT:
            std::cout << "int";
            break;
        default:
            std::cout << "other";
            break;
    }
    std::cout << std::endl;
    for (const ast_node &n : head.children) {
        print_ast(n, depth + 1);
    }
}



