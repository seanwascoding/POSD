#pragma once

#include <string>
#include "iterator.h"
#include "visitor.h"
#include "null_iterator.h"
#include "order_by.h"
#include "iterator_factory.h"

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
        _path = _path.substr(0, slash + 1) + name;
        updatePath(name);
    }

    void correctPath(std::string path, size_t slashpot)
    {
        if (_path.substr(0, path.length()) != path)
        {
            size_t pot = _path.find('/', slashpot + 1);
            _path = path + _path.substr(pot);
        }
    }

protected:
    virtual void updatePath(string name) = 0;
};
