#pragma once

#include "node.h"

class Link : public Node
{
public:
    Link(string path, Node *node) : Node(path), _lnode(node) {}

    int numberOfFiles() const override {}
    Node *find(string path) override {}
    std::list<string> findByName(string name) override {}
    void add(Node *node) override {}
    void remove(string path) override {}
    Node *getChildByName(const char *name) const override {}
    void accept(Visitor *visitor) override {}

    // //!
    Node *getTarget() {}

protected:
    void updatePath(string name) override{};

private:
    Node *_lnode;
};