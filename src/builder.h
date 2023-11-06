#pragma once

#include <list>
#include <stack>

class Builder
{
public:
    Builder() {}

    void buildExpression(char op)
    {

    }

    void endExpression()
    {
    }

    void buildOperand(int operand)
    {
        _compounds.push(new Operand(operand));
    }

    Term *getTerm()
    {
        return term;
    }

private:
    Term *term;
    std::stack<Term *> _compounds;
};
