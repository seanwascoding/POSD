#pragma once

#include "node.h"

class Link : public Node
{
public:
    Link(string name, Node *node) : Node(name), _lnode(node) {}

    int numberOfFiles() const override {}
    Node *find(string path) override {}
    std::list<string> findByName(string name) override {}
    void add(Node *node) override {}
    void remove(string path) override {}
    Node *getChildByName(const char *name) const override {}

    //! 
    Node *getTarget() {}

private:
    string _lname;
    Node *_lnode;
};