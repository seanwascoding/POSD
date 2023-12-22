#pragma once

#include "visitor.h"
#include "order_by.h"
#include "iterator_factory.h"

class TreeVisitor : public Visitor
{
public:
    TreeVisitor(IteratorFactory *itF) : _itF(itF), _currentLevel(0), _notEndLevel(0), _state(false) { cout << "test1" << endl; }

    TreeVisitor(OrderBy orderBy) : _orderBy(orderBy), _currentLevel(0), _notEndLevel(0), _state(true) { cout << "test2" << endl; }

    void visitFile(File *file)
    {
        _result += file->name() + "\n";
    }
    void visitFolder(Folder *folder)
    {
        if (_result == "")
        {
            _result += ".\n";
        }
        else
        {
            _result += folder->name() + "\n";
        }

        Iterator *it;
        if (_state)
        {
            // cout << "test3" << endl;
            it = folder->createIterator(_orderBy);
        }
        else
        {
            // cout << "test4" << endl;
            it = _itF->create(folder, folder->getOperationCount());
            // cout << "test5" << endl;
        }

        it->first();
        while (!it->isDone())
        {
            Node *current = it->currentItem();
            it->next();

            ++_currentLevel;
            int notEndLevel = _notEndLevel;
            for (int i = 1; i < _currentLevel; ++i)
            {
                if (i <= _notEndLevel)
                {
                    _result += "│   ";
                }
                else
                {
                    _result += "    ";
                }
            }

            if (it->isDone())
            {
                _result += "└── ";
            }
            else
            {
                _result += "├── ";
                ++_notEndLevel;
            }
            current->accept(this);

            --_currentLevel;
            _notEndLevel = notEndLevel;
        }
    }

    string getTree()
    {
        return _result;
    }

    //!
    void visitLink(Link *link) override
    {
    }

private:
    OrderBy _orderBy;
    IteratorFactory *_itF;
    bool _state;
    std::string _result;
    int _currentLevel;
    int _notEndLevel;
};