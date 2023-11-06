#pragma once

#include "scanner.h"
#include "builder.h"
#include "term.h"
#include <string>

class Parser
{
public:
    Parser(Scanner *scanner, Builder *builder) : _scanner(scanner), _builder(builder) {}

    void parse()
    {
        // token = _scanner->nextToken();
        // token = _scanner->nextToken();
        // token = _scanner->nextToken();
        // token = _scanner->nextToken();
        // token = _scanner->nextToken();

        // std::cout << _scanner->isDone() << std::endl;

        while (!_scanner->isDone())
        {
            std::string token = _scanner->nextToken(); // (
            // _builder->buildOperand(_scanner->nextDouble()); // 10
            // std::string temp1 = _scanner->nextToken(); // +
            // _scanner->nextToken(); // (
            // _scanner->nextToken(); // (
            // _builder->buildOperand(_scanner->nextDouble()); // 11
            // std::string temp2 = _scanner->nextToken(); // +
            // _builder->buildOperand(_scanner->nextDouble()); // 12
            // _builder->buildExpression(temp1[0]);
            // _builder->endExpression(); // end

            // temp2 = _scanner->nextToken(); // *
            // _scanner->nextToken(); // (
            // _builder->buildOperand(_scanner->nextDouble()); // 5
            // std::string temp3 = _scanner->nextToken(); // *
            // _builder->buildOperand(_scanner->nextDouble()); // 4
            // _builder->endExpression(); // end
            // _builder->endExpression(); // end
            // _builder->endExpression(); // end
        }
    }

    Term *getTerm()
    {
        return _builder->getTerm();
    }

    void setInput(std::string input)
    {
        _scanner->setInput(input);
    }

private:
    Scanner *_scanner;
    Builder *_builder;
};
