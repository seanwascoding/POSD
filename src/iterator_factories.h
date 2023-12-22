#pragma once

#include "iterator_factory.h"
#include "folder.h"

class FolderIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        _it = new Folder::FolderIterator(node, operationCount);
        return _it;
    }

    Iterator *instance()
    {
        return _it;
    }

private:
    Iterator *_it;
};

class OrderByNameIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        _it = new Folder::OrderByNameIterator(node, operationCount);
        return _it;
    }

    Iterator *instance()
    {
        return _it;
    }

private:
    Iterator *_it;
};

class OrderByNameWithFolderFirstIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        _it = new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
        return _it;
    }

    Iterator *instance()
    {
        return _it;
    }

private:
    Iterator *_it;
};

class OrderByKindIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        _it = new Folder::OrderByKindIterator(node, operationCount);
        return _it;
    }

    Iterator *instance()
    {
        return _it;
    }

private:
    Iterator *_it;
};
