#pragma once

#include <string>
#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor
{
public:
    FindByNameVisitor(string name) : _name(name), _state(false){};

    void visitFile(File *file) override
    {
        printf("1:%s\n", _name.c_str());
        printf("2:%s\n", file->name().c_str());
        printf("3:%s\n", file->path().c_str());

        if (_name == file->name())
        {
            _files.push_back(file->path());
            if (_state)
            {
                std::list<string>::iterator it = find(_files.begin(), _files.end(), file->path());
                if (it == _files.end())
                {
                    _files.push_back(file->path());
                }
            }
        }
    };

    void visitFolder(Folder *folder) override
    {
        _state = true;
        auto it = folder->dfsIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            printf("the output folders:%s\n", it->currentItem()->path().c_str());
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
    bool _state;
};