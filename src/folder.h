#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>
#include <algorithm>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

using namespace std;

class Folder : public Node
{
    friend class FolderIterator;
    friend class DfsIterator;
    friend class BfsIterator;

public:
    Folder(string path)
    {
        _name = path.substr(path.find_last_of("/") + 1);
        _path = path;
        it = this->createIterator();
    };

    ~Folder() override
    {
        // printf("work\n");
        delete it;
    }

    string name() const override
    {
        return _name;
    }

    string path() const override
    {
        return _path;
    }

    void add(Node *node) override
    {
        _files.push_back(node);
    }

    // Explicit parent reference p.166
    void remove(string path) override
    {
        for (it->first(); !it->isDone(); it->next())
        {
            if (it->currentItem()->path() == path)
            {
                vector<Node *>::iterator temp = std::find(_files.begin(), _files.end(), it->currentItem());
                delete it->currentItem();
                _files.erase(temp);
                break;
            }
        }
    }

    Node *getChildByName(const char *name) const
    {
        for (it->first(); !it->isDone(); it->next())
        {
            if (it->currentItem()->name() == name)
            {
                return it->currentItem();
            }
        }
        return nullptr;
    };

    Node *find(string path)
    {
        for (it->first(); !it->isDone(); it->next())
        {
            if (it->currentItem()->path() == path)
            {
                return it->currentItem();
            }
        }
        return nullptr;
    };

    int numberOfFiles() const override
    {
        return _files.size();
    }

    // Different Iterator type can be place
    Iterator *createIterator() override
    {
        // return new FolderIterator(this);
        // return new DfsIterator(this);
        return new BfsIterator(this);
    }

private:
    string _path, _name;
    vector<Node *> _files;
    Iterator *it;
};

#endif // FOLDER
