#pragma once

#include "term.h"
#include <iostream>

class Expression : public Term
{
public:
    Expression(Term *left, Term *right, const char op = '+') : _left(left), _right(right), _op(op)
    {
        if (_op != '+' && _op != '*')
        {
            std::cout << _op << std::endl;
            throw "error";
        }
    }

    Term *left() const { return _left; }
    Term *right() const { return _right; }
    char getOperator() const { return _op; }

    int evaluate() const override
    {
        if (_op == '+')
        {
            return _left->evaluate() + _right->evaluate();
        }
        else if (_op == '*')
        {
            return _left->evaluate() * _right->evaluate();
        }
        else
        {
            throw "error";
        }
    }

    std::string str() const override
    {
        string result = "(";

        result += _left->str();
        result += _op;
        result += _right->str();

        result += ")";

        return result;
    }

    std::string post_str() const override
    {
        return _left->post_str() + " " + _right->post_str() + " " + _op;
    }

    void accept(Visitor *v)
    {
        v->visit(this);
    }

private:
    Term *_left, *_right;
    const char _op;
};
