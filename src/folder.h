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
        _state = 0;
        _files.clear();
        _name = path.substr(path.find_last_of("/") + 1);
        _path = path;
        it = this->createIterator();
        it_normal = this->createIterator();
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
            printf("node be add\n");
            _files.push_back(node);
            printf("%s\n", node->path().c_str());
        }
        else
        {
            throw runtime_error("wrong path");
        }
    }

    // Explicit parent reference p.166
    void remove(string path) override
    {
        for (it->first(); !it->isDone(); it->next())
        {
            if (path == it->currentItem()->path())
            {
                printf("remove find the file %s\n", it->currentItem()->name().c_str());
                Node *test = it->currentItem();

                // effect the iterator => last execute
                Node *temp_dir = find(it->currentItem()->path().substr(0, it->currentItem()->path().find_last_of("/")));

                if (temp_dir == nullptr)
                {
                    _files.erase(std::remove_if(_files.begin(), _files.end(), [test](Node *node)
                                                { return node->path() == test->path(); }),
                                 _files.end());
                }
                else
                {
                    vector<Node *>::iterator position_node = std::find(temp_dir->_files.begin(), temp_dir->_files.end(), test);
                    temp_dir->_files.erase(std::remove(temp_dir->_files.begin(), temp_dir->_files.end(), test), temp_dir->_files.end());
                }
                // delete test;
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
        for (it->first(); !it->isDone(); it->next())
        {
            // printf("filter name %s\n", it->currentItem()->name().c_str());
            if (it->currentItem() != nullptr && it->currentItem()->getClassIterator() == true)
            {
                printf("work %s\n", it->currentItem()->name().c_str());
                i++;
            }
            else
            {
                printf("fail\n");
            }
        }
        // if (it->currentItem() != nullptr && it->currentItem()->getClassIterator() == true)
        // {
        //     printf("work %s\n", it->currentItem()->name().c_str());
        //     i++;
        // }
        // else
        // {
        //     printf("fail\n");
        // }
        return i;
    }

    // Different Iterator type can be place
    Iterator *createIterator() override
    {
        if (_state == 0)
        {
            _state = 1;
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
    Iterator *it;
    Iterator *it_normal;
    int _i = 0, _state;
};

#endif // FOLDER
