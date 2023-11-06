#pragma once

#include "term.h"

class Operand : public Term
{
public:
    Operand(int value) : _value(value) {}

    int evaluate() const override { return _value; }

    std::string str() const override
    {
        return to_string(_value);
    }

    std::string post_str() const override
    {
        return to_string(_value);
    }

    void accept(Visitor *v)
    {
        v->visit(this);
    }

private:
    int _value;
};
