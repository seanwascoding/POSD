#pragma once

#include "node.h"

class Link : public Node
{
public:
    Link(string path, Node *node) : Node(path), _lnode(node) {}

    int numberOfFiles() const override 
    {
        return _lnode->numberOfFiles();
    }
    Node *find(string path) override 
    {
        return _lnode->find(path);
    }
    std::list<string> findByName(string name) override 
    {
        return _lnode->findByName(name);
    }
    void add(Node *node) override 
    {
        _lnode->add(node);
    }
    void remove(string path) override 
    {
        _lnode->remove(path);
    }
    Node *getChildByName(const char *name) const override 
    {
        return _lnode->getChildByName(name);
    }
    void accept(Visitor *visitor) override 
    {
        visitor->visitLink(this);
    }

    //!
    Node *getTarget() 
    {
        return _lnode;
    }

protected:
    void updatePath(string name) override{};

private:
    Node *_lnode;
};