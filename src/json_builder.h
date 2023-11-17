#pragma once

#include "string_value.h"
#include <stack>

class JsonBuilder
{
public:
    void buildValue(std::string key, std::string value)
    {
        if (_compound.empty())
        {
            _root->set(key, new StringValue(value));
        }
        else
        {
            _compound.top().second->set(key, new StringValue(value));
        }
    };

    void buildObject(std::string key)
    {
        if (_state == 0)
        {
            _root = new JsonObject();
        }
        else
        {
            std::pair<std::string, JsonObject *> _temp = std::make_pair(key, new JsonObject());
            _compound.push(_temp);
        }
        _state++;
    };

    void endObject()
    {
        if (!_compound.empty())
        {
            std::pair<std::string, JsonObject *> _temp = _compound.top();
            _compound.pop();
            if (_compound.empty())
            {
                std::cout << "in the end" << std::endl;
                _root->set(_temp.first, _temp.second);
            }
            else
            {
                _compound.top().second->set(_temp.first, _temp.second);
            }
        }
    };

    JsonObject *getJsonObject() { return _root; };

private:
    std::stack<std::pair<std::string, JsonObject *>> _compound;
    JsonObject *_root;
    size_t _state;
};
