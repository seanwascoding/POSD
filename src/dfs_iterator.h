#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

// #include "iterator.h"
// #include "file.h"
// #include "node.h"

class DfsIterator : public Iterator
{
public:
    DfsIterator(Node *composite);

    void first() override;

    Node *currentItem() const override;

    void next() override;

    bool isDone() const override;

private:
    Node *_composite;
    std::vector<Node *>::iterator _it;
    std::vector<std::vector<Node *>::iterator> _temp;
    int _i = 0;
};

class BfsIterator : public Iterator
{
public:
    BfsIterator(Node *composite);

    void first() override;

    Node *currentItem() const override;

    void next() override;

    bool isDone() const override;

private:
    Node *_composite;
    std::vector<Node *>::iterator _it;
    std::vector<std::vector<Node *>::iterator> _temp, _temp2;
    int _i;
    bool _state;
};

#endif // DFS_ITERATOR_H
