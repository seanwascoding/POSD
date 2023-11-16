#pragma once

#include "string_value.h"
#include "json_object.h"
#include "visitor.h"

class BeautifyVisitor : public JsonVisitor
{
public:
    void visitJsonObject(JsonObject *obj) override
    {
        _indent++;
        _result += "{\n";

        JsonIterator *it = obj->createIterator();
        int j = 0;
        for (it->first(); !it->isDone(); it->next())
        {
            // todo indent
            int i = 0;
            while (i < _indent)
            {
                _result += "    ";
                i++;
            }

            _result += "\"" + it->currentKey() + "\": ";
            it->currentValue()->accept(this);

            // todo if files not rest
            j++;
            if (it->getSize() != j)
            {
                _result += ",\n";
            }
            else
            {
                _result += "\n";
            }
        }

        int i = 0;
        while (i < _indent - 1)
        {
            _result += "    ";
            i++;
        }

        _result += "}";
        _indent--;
    };

    void visitStringValue(StringValue *val) override
    {
        _result += val->toString();
    };

    std::string getResult() const { return _result; };

private:
    std::string _result;
    int _indent = 0;
};