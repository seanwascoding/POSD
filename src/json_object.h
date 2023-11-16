#pragma once

#include "value.h"
#include <list>
#include <map>
#include <string>

#include "value.h"

class JsonObject : public Value
{
public:
    void set(std::string key, Value *value)
    {
        _compound.insert(std::pair<std::string, Value *>(key, value));
    }

    Value *getValue(std::string key)
    {
        if(_compound.find(key) != _compound.end())
            return _compound.find(key)->second;
        else
            throw "not exist";
    }

    std::string toString() override
    {
        unsigned int count = 0;

        std::string result = "{\n";

        for (const auto &entry : _compound)
        {
            result += "\"" + entry.first + "\":";

            result += entry.second->toString();

            count++;
            // std::cout << _compound.size() << ":" << count << std::endl;

            if (static_cast<unsigned int>(_compound.size()) == count)
            {
                result += "\n";
            }
            else
            {
                result += ",\n";
            }
        }

        result += "}";

        return result;
    }

    JsonIterator *createIterator() { return new JsonObjectIterator(this); }

    class JsonObjectIterator : public JsonIterator
    {
    public:
        JsonObjectIterator(JsonObject *compound) : _host(compound), _size(compound->_compound.size()) {}

        void first() override
        {
            _it = _host->_compound.begin();
        }

        std::string currentKey() const override { return _it->first; }

        Value *currentValue() const override { return _it->second; }

        void next() override { _it++; }

        bool isDone() const override { return _it == _host->_compound.end(); }

        int getSize() override { return _size; }

    private:
        JsonObject *_host;
        std::map<std::string, Value *>::iterator _it;
        int _size;
    };

    void accept(JsonVisitor *visitor) override
    {
        visitor->visitJsonObject(this);
    }

private:
    std::map<std::string, Value *> _compound;
};