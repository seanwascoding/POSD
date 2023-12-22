#pragma once

#include "iterator_factory.h"
#include "folder.h"

class FolderIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::FolderIterator(node, operationCount);
    }

    static IteratorFactory *instance()
    {
        if (!_it)
            _it = new FolderIteratorFactory();
        return _it;
    }

private:
    static IteratorFactory *_it;
};

class OrderByNameIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::OrderByNameIterator(node, operationCount);
    }

    static IteratorFactory *instance()
    {
        if (!_it)
            _it = new OrderByNameIteratorFactory();
        return _it;
    }

protected:
    static IteratorFactory *_it;
};

class OrderByNameWithFolderFirstIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }

    static IteratorFactory *instance()
    {
        if (!_it)
            _it = new OrderByNameWithFolderFirstIteratorFactory();
        return _it;
    }

private:
    static IteratorFactory *_it;
};

class OrderByKindIteratorFactory : public IteratorFactory
{
public:
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::OrderByKindIterator(node, operationCount);
    }

    static IteratorFactory *instance()
    {
        if (!_it)
            _it = new OrderByKindIteratorFactory();
        return _it;
    }

private:
    static IteratorFactory *_it;
};

IteratorFactory* FolderIteratorFactory::_it = nullptr;
IteratorFactory* OrderByNameIteratorFactory::_it = nullptr;
IteratorFactory* OrderByNameWithFolderFirstIteratorFactory::_it = nullptr;
IteratorFactory* OrderByKindIteratorFactory::_it = nullptr;
