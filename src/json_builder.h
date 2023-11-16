#pragma once

#include "string_value.h"
#include <stack>

class JsonBuilder
{
public:
    void buildValue(std::string key, std::string value)
    {
        test.top().second->set(key, new StringValue(value));

        //!
    };

    void buildObject(std::string key)
    {
        temp = std::make_pair(key, new JsonObject());
        test.push(temp);
    };

    void endObject()
    {
        if (!test.empty())
        {
            temp = test.top();
            test.pop();
            if (test.empty())
            {
                tt->set(temp.first, temp.second);
            }
            else
            {
                test.top().second->set(temp.first, temp.second);
            }
        }
    };

    JsonObject *getJsonObject() { return tt; };

private:
    std::pair<std::string, JsonObject *> temp;
    std::stack<std::pair<std::string, JsonObject *>> test;
    JsonObject *tt = new JsonObject();
};
