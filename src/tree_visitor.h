#pragma once

#include "visitor.h"
#include "order_by.h"

#include "../src/file.h"
#include "../src/folder.h"

//* Output the structure of file-system under CLI-tree tool
class TreeVisitor : public Visitor
{
public:
    TreeVisitor(OrderBy orderBy) : _operation(orderBy)
    {
        _results = ".\n";
    }

    void visitFile(File *file) override
    {
        _results += file->name();
    };

    void visitFolder(Folder *folder) override
    {
        int sizeCount = 0;
        _it = folder->createIterator(_operation);
        for (_it->first(); !_it->isDone(); _it->next())
        {
            sizeCount++;

            printf("%s\n", _it->currentItem()->name().c_str());

            //! add prefix
            if (_level != 0)
            {
                _results += "|";
                //! indent
                int i = 0;
                while (_level > i)
                {
                    _results += "   ";
                    i++;
                }
            }

            //! add filename
            if (temp.size() != 0 && temp.top()->getSize() == sizeCount)
            {
                _results += "└── ";
                sizeCount = 0;
                _level--;
                temp.pop();
            }
            else
            {
                _results += "├── ";
            }

            //! Tell the diff between file and folder
            if (_it->currentItem()->createIterator()->isDone() != true)
            {
                _results += _it->currentItem()->name();
                _results += "\n";
                _level++;
                temp.push(dynamic_cast<Folder *>(_it->currentItem()));
            }
            else
            {
                _it->currentItem()->accept(this);
                _results += "\n";
            }
        }

        // if (_level >= 0)
        // {
        //     _it = temp.top();
        //     temp.pop();
        // }
    };

    string getTree()
    {
        return _results;
    };

private:
    OrderBy _operation;
    std::string _results;
    Iterator *_it;
    stack<Folder *> temp;
    int _level = 0;
};