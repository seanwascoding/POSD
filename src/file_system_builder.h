#pragma once

#include <string>

#include "folder.h"

using std::string;

class FileSystemBuilder
{
public:
    Folder *getRoot() const
    {
        return _root;
    };

    void buildFile(string path)
    {
        File *file = new File(path);
        if (_compound.empty())
        {
            _root->add(file);
        }
        else
        {
            _compound.top()->add(file);
        }
    };

    void buildFolder(string path)
    {
        if (_state == 0)
        {
            _root = new Folder(path);
        }
        else
        {
            _compound.push(new Folder(path));
        }
        _state++;
    };

    void endFolder()
    {
        if (!_compound.empty())
        {
            Folder *folder = _compound.top();
            _compound.pop();
            if (_compound.empty())
            {
                _root->add(folder);
            }
            else
            {
                _compound.top()->add(folder);
            }
        }
    };

private:
    Folder *_root;
    stack<Folder *> _compound;
    int _state = 0;
};
