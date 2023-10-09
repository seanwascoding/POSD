#include "iterator.h"
#include "folder.h"
#include "file.h"

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

/* dfs_iterator */

bool isFolder(Node *node)
{
    // printf("test\n");
    Node *temp = dynamic_cast<File *>(node);
    if (temp)
    {
        // printf("false\n");
        return !temp->getClassIterator();
    }
    // printf("true\n");
    return true;
}

DfsIterator::DfsIterator(Node *composite) : _composite(composite)
{
    _temp.clear();
};

void DfsIterator::first()
{
    // composite must be the folder in the first giving on this pattern
    if (dynamic_cast<Folder *>(_composite)->_files.empty())
    {
        printf("empty\n");
        return;
    }
    else
    {
        _it = dynamic_cast<Folder *>(_composite)->_files.begin();
        while ((*_it) == nullptr)
        {
            _it++;
        }
    }
};

Node *DfsIterator::currentItem() const
{
    return *_it;
};

// todo recursive method
void DfsIterator::next()
{
    if (!isDone())
    {
        if (isFolder(*_it))
        {
            if (dynamic_cast<Folder *>(*_it)->_files.empty())
            {
                _it++;
                return;
            }
            else
            {
                printf("folder\n");
                _temp.push_back(_it);
                _it = dynamic_cast<Folder *>(*_it)->_files.begin();
                while ((*_it) == nullptr)
                {
                    _it++;
                }
            }
        }
        else
        {
            _it++;
            printf("move to next file\n");
            while (_temp.size() > 0 && _it == dynamic_cast<Folder *>(*_temp.back())->_files.end())
            {
                printf("subfolder end\n");
                // if SubFolder is end, then will back to RootFolder
                _it = _temp.back();
                _temp.pop_back();
                _it++;
            }
            while ((*_it) == nullptr)
            {
                _it++;
                while (_temp.size() > 0 && _it == dynamic_cast<Folder *>(*_temp.back())->_files.end())
                {
                    printf("subfolder end\n");
                    // if SubFolder is end, then will back to RootFolder
                    _it = _temp.back();
                    _temp.pop_back();
                    _it++;
                }
            }
        }
    }
    else
    {
        /* jump */
    }
};

bool DfsIterator::isDone() const
{
    if (_temp.size() == 0)
    {
        printf("%d\n", _temp.size());
        size_t index = std::distance(_composite->_files.begin(), _it) + 1;
        printf("isDone filter %d %d\n", index, _composite->_files.size());
        return index == _composite->_files.size();
    }
    else
    {
        return _it == _composite->_files.end();
    }
};

/* bfs_iterator */

BfsIterator::BfsIterator(Node *composite) : _composite(composite)
{
    _temp.clear();
    _temp2.clear();
    _i = 0;
    _state = false;
}

void BfsIterator::first()
{
    _it = dynamic_cast<Folder *>(_composite)->_files.begin();
}

Node *BfsIterator::currentItem() const
{
    return *_it;
}

void BfsIterator::next()
{
    if (isFolder(*_it))
    {
        printf("folder\n");
        _temp2.push_back(_it);
    }
    printf("++\n");
    _it++;

    if (_it == dynamic_cast<Folder *>(_composite)->_files.end())
    {
        printf("done1\n");
        _temp.clear();
        _temp = _temp2;
        _temp2.clear();
        _i = 0;

        _it = dynamic_cast<Folder *>(*_temp[_i])->_files.begin();
        _i++;
    }
    else if (_temp.size() > 0 && _it == dynamic_cast<Folder *>(*_temp[_i - 1])->_files.end())
    {
        printf("subdone\n");
        if (_i == _temp.size())
        {
            printf("done2\n");
            _temp.clear();
            _temp = _temp2;
            _temp2.clear();
            _i = 0;

            if (_temp.size() == 0)
            {
                printf("close\n");
                _state = true;
                return;
            }
            else
            {
                _it = dynamic_cast<Folder *>(*_temp[_i])->_files.begin();
                _i++;
            }
        }
        else
        {
            printf("switch\n");
            _it = dynamic_cast<Folder *>(*_temp[_i])->_files.begin();
            _i++;
        }
    }
}

// TODO the end-point is on the last step
bool BfsIterator::isDone() const
{
    return _state;
}
