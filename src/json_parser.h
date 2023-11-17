#pragma once

#include "./json_scanner.h"
#include "./json_builder.h"
#include "./json_object.h"
#include <string>
#include <regex>

class JsonParser
{
public:
    JsonParser(JsonScanner *scanner, JsonBuilder *builder) : _scanner(scanner), _builder(builder) {}

    void parse()
    {
        std::string key = "";
        while (!_scanner->isDone())
        {
            char token = _scanner->next();
            std::cout << token << std::endl;
            if (token == ' ')
            {
                continue;
            }
            else if (token == '{')
            {
                //! fill in the code => create the jsonobject
                _builder->buildObject(key);
            }
            else if (token == '"') //! create key-pair
            {
                std::string value;
                token = _scanner->next();
                while (token != '"')
                {
                    value += token;
                    token = _scanner->next();
                }
                token = _scanner->next();

                while (token == ' ')
                {
                    token = _scanner->next();
                }

                if (token == ':')
                {
                    key = value;
                }
                else if (token == ',')
                {
                    //! fill in the code
                    std::cout << key << ":" << value << std::endl;
                    _builder->buildValue(key, value);
                }
                else if (token == '}' || token == '\n')
                {
                    //! fill in the code
                    _builder->buildValue(key, value);
                    _builder->endObject();
                }
            }
            else if (token == '}')
            {
                //! fill in the code
                std::cout << key << std::endl;
                _builder->endObject();
            }
        }
    }

    JsonObject *getJsonObject()
    {
        return _builder->getJsonObject();
    }

    void setInput(std::string input)
    {
        _scanner->setInput(input);
    }

private:
    JsonScanner *_scanner;
    JsonBuilder *_builder;
};