#pragma once

#include "iterator_factory.h"
#include "folder.h"

class FolderIteratorFactory : public IteratorFactory
{
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::FolderIterator(node, operationCount);
    }
};

class OrderByNameIteratorFactory : public IteratorFactory
{
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::OrderByNameIterator(node, operationCount);
    }
};

class OrderByNameWithFolderFirstIteratorFactory : public IteratorFactory
{
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }
};

class OrderByKindIteratorFactory : public IteratorFactory
{
    Iterator *create(Folder *node, int operationCount) override
    {
        return new Folder::OrderByKindIterator(node, operationCount);
    }
};
