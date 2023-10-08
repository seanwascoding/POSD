#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "node.h"
#include "iterator.h"

using namespace std;

class Folder : public Node
{
    friend class FolderIterator;
    friend class DfsIterator;
    friend class BfsIterator;

public:
    Folder(string path)
    {
        _state = 1;
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
        if (_path == node->path().substr(0, node->path().find_last_of("/")))
        {
            _files.push_back(node);
        }
        else
        {
            throw runtime_error("wrong path");
        }
    }

    // Explicit parent reference p.166
    void remove(string path) override
    {
        try
        {
            if (_path == path.substr(0, path.find_last_of("/")))
            {
                for (it->first(); !it->isDone(); it->next())
                {
                    if (it->currentItem()->path() == path)
                    {
                        vector<Node *>::iterator temp = std::find(_files.begin(), _files.end(), it->currentItem());
                        _files.erase(temp);
                        delete it->currentItem();
                        break;
                    }
                }
            }
            else
            {
                for (it->first(); !it->isDone(); it->next())
                {
                    if (it->currentItem()->path().substr(0, it->currentItem()->path().find_last_of("/")) == path.substr(0, it->currentItem()->path().find_last_of("/")) && it->currentItem()->getClassIterator() == false)
                    {
                        it->currentItem()->remove(path);
                        break;
                    }
                }
            }
        }
        catch (...)
        {
            printf("error\n");
        }
    }

    Node *getChildByName(const char *name) const override
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

    Node *find(string path) override
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

    // todo bug
    int numberOfFiles() const override
    {
        int i = 0;
        printf("test\n");
        // for (it->first(); !it->isDone(); it->next())
        // {
        //     if (it->currentItem() != nullptr && it->currentItem()->getClassIterator() == true)
        //     {
        //         i++;
        //     }
        // }
        it->first();
        it->next();
        it->next();
        printf("%d\n", it->isDone());
        return i;
    }

    // Different Iterator type can be place
    Iterator *createIterator() override
    {
        if (_state == 0)
        {
            return new FolderIterator(this);
        }
        else if (_state == 1)
        {
            return new DfsIterator(this);
        }
        else if (_state == 2)
        {
            return new BfsIterator(this);
        }
    }

    void switchState(int state) override
    {
        delete it;
        _state = state;
        it = this->createIterator();
    }

private:
    string _path, _name;
    vector<Node *> _files;
    Iterator *it;
    int _state;
};

#endif // FOLDER
