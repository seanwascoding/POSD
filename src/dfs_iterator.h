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

    // bool isFolder(Node *node) override
    // {
    //     // printf("test\n");
    //     Node *temp = dynamic_cast<File *>(node);
    //     if (temp)
    //     {
    //         // printf("false\n");
    //         return !temp->getClassIterator();
    //     }
    //     // printf("true\n");
    //     return true;
    // }

private:
    Node *_composite;
    std::vector<Node *>::iterator _it;
    std::vector<std::vector<Node *>::iterator> _temp;
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
