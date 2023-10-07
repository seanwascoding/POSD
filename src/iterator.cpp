#include "iterator.h"
#include "folder.h"

FolderIterator::FolderIterator(Folder *composite) : _composite(composite) {}

void FolderIterator::first()
{
    _it = _composite->_files.begin();
};

Node *FolderIterator::currentItem() const
{
    return *_it;
};

void FolderIterator::next()
{
    _it++;
};

bool FolderIterator::isDone() const
{
    return _it == _composite->_files.end();
};