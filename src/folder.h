#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstdio>
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
        _files.clear();
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
        if (node == nullptr)
        {
            printf("nullptr be add\n");
            _i++;
            _files.push_back(nullptr);
        }
        else if (_path == node->path().substr(0, node->path().find_last_of("/")))
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
            if (it->currentItem()->getClassIterator() == true && path == it->currentItem()->path())
            {
                if (std::remove(path.c_str()) == 0)
                {
                    std::cout << "work to delete" << std::endl;
                }
                else
                {
                    std::cerr << "error" << std::endl;
                }

                // vector<Node *>::iterator temp = std::find(it->currentItem()->_files.begin(), it->currentItem()->_files.end(), it->currentItem());
                // _files.erase(temp);
                // it->currentItem()->_files.erase(temp);
                // delete it->currentItem();

                break;
            }
            // printf("fail to delete %s vs %s\n", it->currentItem()->path().c_str(), _path.c_str());
        }

        // printf("fail to delete %s\n", it->currentItem()->path().c_str());

        // printf("%s", path.c_str());
        // if (_path == path.substr(0, path.find_last_of("/")))
        // {
        //     for (it->first(); !it->isDone(); it->next())
        //     {
        //         if (it->currentItem()->path() == path)
        //         {
        //             vector<Node *>::iterator temp = std::find(_files.begin(), _files.end(), it->currentItem());
        //             _files.erase(temp);
        //             delete it->currentItem();
        //             break;
        //         }
        //     }
        // }
        // else
        // {
        //     for (it->first(); !it->isDone(); it->next())
        //     {
        //         if (it->currentItem()->path().substr(0, it->currentItem()->path().find_last_of("/")) == path.substr(0, it->currentItem()->path().find_last_of("/")) && it->currentItem()->getClassIterator() == false)
        //         {
        //             it->currentItem()->remove(path);
        //             break;
        //         }
        //     }
        // }
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
        // if (it->currentItem()->name() == name)
        // {
        //     return it->currentItem();
        // }
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
    // vector<Node *> _files;
    Iterator *it;
    int _i = 0, _state;
};

#endif // FOLDER
