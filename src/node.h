#pragma once

#include <string>
#include "iterator.h"
#include "visitor.h"
#include "null_iterator.h"
#include "order_by.h"
#include "iterator_factory.h"
#include <cstdio>
#include <iostream>

using namespace std;

class Node
{
private:
    string _path;
    Node *_parent;

protected:
    Node(string path) : _path(path) {}

public:
    virtual ~Node() {}

    Node *parent()
    {
        return _parent;
    }

    void parent(Node *parent)
    {
        _parent = parent;
    }

    virtual void removeChild(Node *target)
    {
        throw string("This node does not support removing sub node");
    }

    string name() const
    {
        size_t slash = _path.rfind("/");
        return _path.substr(slash + 1);
    }

    string path() const
    {
        return _path;
    }

    virtual void add(Node *node)
    {
        throw string("This node does not support adding sub node");
    }

    virtual Node *getChildByName(const char *name) const
    {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;

    virtual Iterator *createIterator(OrderBy orderBy)
    {
        return new NullIterator();
    }

    //! overloading versions
    virtual Iterator *createIterator()
    {
        return new NullIterator();
    }

    virtual Iterator *createIterator(IteratorFactory *)
    {
        return new NullIterator();
    }

    virtual Node *find(string path) = 0;

    virtual std::list<string> findByName(string name) = 0;

    virtual void remove(string path)
    {
        throw string("This node does not support deleting sub node");
    }

    virtual void accept(Visitor *visitor) = 0;

    //! add new function
    void rename(std::string name)
    {
        size_t slash = _path.rfind("/");
        string temp = _path.substr(0, slash + 1) + name;
        // std::rename(_path.c_str(), temp.c_str());
        _path = temp;
        updatePath(name);
    }

    void correctPath(std::string path, size_t slashpot)
    {
        if (_path.substr(0, path.length()) != path)
        {
            size_t pot = _path.find('/', slashpot + 1);
            string temp = path + _path.substr(pot);
            // std::rename(_path.c_str(), temp.c_str());
            _path = temp;
        }
    }

protected:
    virtual void updatePath(string name) = 0;
};
