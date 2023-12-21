#include "node.h"

class Link : public Node
{
public:
    int numberOfFiles() const override {}
    Node *find(string path) override {}
    std::list<string> findByName(string name) override {}
    void add(Node *node) override {}
    void remove(string path) override {}
    Node *getChildByName(const char *name) const override {}

    Node * getTarget() {}

private:
};