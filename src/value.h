#pragma once

#include <string>
#include "json_iterator.h"
#include "visitor.h"

class Value
{
public:
    virtual std::string toString() { return NULL; }
    virtual JsonIterator *createIterator() { return new NullIterator(); }
    virtual void accept(JsonVisitor *visitor) = 0;
};