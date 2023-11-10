#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser
{
public:
    FileSystemParser(FileSystemBuilder *builder, FileSystemScanner *scanner) : _builder(builder), _scanner(scanner){};

    Folder *getRoot() const
    {
        return _builder->getRoot();
    };

    void parse(){

    };

    void setPath(string path)
    {
        _scanner->setPath(path);
    };

private:
    FileSystemBuilder *_builder;
    FileSystemScanner *_scanner;
};
