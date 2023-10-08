#if !defined(FILE_H)
#define FILE_H

#include "node.h"
#include "null_iterator.h"

class File : public Node
{
public:
    File(string path)
    {
        iterator = this->createIterator();
        _path = path;
        _name = path.substr(path.find_last_of("/") + 1);
    };

    ~File() override
    {
        delete iterator;
    }

    string name() const override
    {
        return _name;
    }

    string path() const override
    {
        return _path;
    }

    Iterator *createIterator() override
    {
        return new NullIterator();
    }

    bool getClassIterator() override { return iterator->isDone(); };

private:
    string _path, _name;
    Iterator *iterator;
};

#endif // FILE_H
