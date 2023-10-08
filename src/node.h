#if !defined(NODE_H)
#define NODE_H

#include <string>
#include "iterator.h"

using namespace std;

class Node
{
public:
    virtual string name() const = 0;

    virtual string path() const = 0;

    virtual void add(Node *node){};

    virtual void remove(string path){};

    virtual Node *getChildByName(const char *name) const {};

    virtual Node *find(string path){};

    virtual int numberOfFiles() const {};

    virtual Iterator *createIterator() = 0;

    virtual bool getClassIterator(){};

    virtual ~Node(){};

    virtual void switchState(int state){};
};

#endif // NODE_H
