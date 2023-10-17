#pragma once

#include <string>
#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor
{
public:
    FindByNameVisitor(string name) : _name(name){};

    void visitFile(File *file) override
    {
        if (_name == file->name())
        {
            _files.push_back(file->name());
        }
    };

    void visitFolder(Folder *folder) override
    {
        auto it = folder->dfsIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            it->currentItem()->accept(this);
        }
        delete it;
    };

    std::list<string> getPaths() const
    {
        return _files;
    };

private:
    string _name;
    std::list<string> _files;
};