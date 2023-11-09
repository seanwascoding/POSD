#pragma once

#include "visitor.h"
#include "order_by.h"

#include "../src/file.h"
#include "../src/folder.h"

//* Output the structure of file-system under CLI-tree tool
class TreeVisitor : public Visitor
{
public:
    TreeVisitor(OrderBy orderBy) : _operationCount(static_cast<int>(orderBy))
    {
        _results += ".";
    }

    void visitFile(File *file) override
    {
        _results += "├──";
        _results += file->name();
    };
    void visitFolder(Folder *folder) override{
        
    };

    string getTree()
    {
        return _results;
    };

private:
    int _operationCount = 0;
    std::string _results;
};