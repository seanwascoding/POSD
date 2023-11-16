#pragma once

#include <string>
#include <map>

class Value;

class JsonIterator
{
public:
    virtual void first() = 0;

    virtual std::string currentKey() const = 0;

    virtual Value *currentValue() const = 0;

    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual int getSize() {}
};

class NullIterator : public JsonIterator
{
public:
    void first() override{};

    std::string currentKey() const override { throw "not exist"; };

    Value *currentValue() const override { throw "not exist"; };

    void next() override{};

    bool isDone() const override { return true; };
};
