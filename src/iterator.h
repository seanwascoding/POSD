#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once

#include <list>
#include <vector>

class Node;
class Folder;
class File;

class Iterator
{
public:
    virtual ~Iterator(){};
    virtual void first(){};
    virtual Node *currentItem() const {};
    virtual void next(){};
    virtual bool isDone() const {};
};

class FolderIterator : public Iterator
{
public:
    FolderIterator(Folder *composite);
    void first() override;
    Node *currentItem() const override;
    void next() override;
    bool isDone() const override;

private:
    Folder *_composite;
    std::vector<Node *>::iterator _it;
};

#include "dfs_iterator.h"

#endif // ITERATOR_H
