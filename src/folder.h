#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>
#include <algorithm>
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
        _state = 0;
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
        else{
            throw "wrong path";
        }
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
            // printf("test%s\n", it->currentItem()->path().c_str());
            if (it->currentItem()->path() == path)
            {
                // printf("work\n");
                return it->currentItem();
            }
        }
        // printf("nullptr\n");
        // printf("%s\n", it->currentItem()->name().c_str());
        return nullptr;
    };

    int numberOfFiles() const override
    {
        return _files.size();
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
