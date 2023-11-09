#pragma once

#include <list>
#include <sys/stat.h>
#include "node.h"
#include "dfs_iterator.h"

using namespace std;

class Folder : public Node
{
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node *target) override
    {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path) : Node(path)
    {
        struct stat fileInfo;
        const char *c = path.c_str();
        if (lstat(c, &fileInfo) == 0)
        {
            if (S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node *node) override
    {
        if (node->path() != this->path() + "/" + node->name())
        {
            throw string("Incorrect path of node: " + node->path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node *getChildByName(const char *name) const override
    {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            if ((*it)->name() == name)
            {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override
    {
        int num = 0;
        if (_nodes.size() == 0)
        {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    //! default
    Iterator *createIterator() override
    {
        return new FolderIterator(this, _operationCount);
    }

    //! Add function => orderby template
    Iterator *createIterator(OrderBy orderby) override
    {
        _operationCount = static_cast<int>(orderby);
        cout << "create iterator:" << _operationCount << endl;
        if (_operationCount == 0)
            return new FolderIterator(this, _operationCount);
        else if (_operationCount == 1)
            return new OrderByNameIterator(this, _operationCount);
        else if (_operationCount == 2)
            return new OrderByNameWithFolderFirstIterator(this, _operationCount);
        else if (_operationCount == 3)
            return new OrderByKindIterator(this, _operationCount);
        else
            throw "error orderbyValue";
    }

    Node *find(string path) override
    {
        if (this->path() == path)
        {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index)
        {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            Node *result = (*it)->find(path);
            if (result)
            {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override
    {
        std::list<string> pathList;
        if (this->name() == name)
        {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);
            }
        }

        return pathList;
    }

    void remove(string path) override
    {
        Node *target = find(path);
        if (target)
        {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor *visitor) override
    {
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator
    {
    public:
        FolderIterator(Folder *composite, int operationCount) : _host(composite), _operationCount(operationCount) {}

        ~FolderIterator() {}

        void first()
        {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node *currentItem() const
        {
            return *_current;
        }

        void next()
        {
            checkAvailable();
            _current++;
        }

        bool isDone() const
        {
            return _current == _host->_nodes.end();
        }

    private:
        Folder *const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        //! invalid if the structure of the target folder is changed
        void checkAvailable() const
        {
            if (_host->_operationCount != _operationCount)
            {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator : public Iterator
    {
    public:
        OrderByNameIterator(Folder *composite, int operationCount) : _host(composite), _operationCount(operationCount)
        {
            arrangeNodes(dynamic_cast<Folder *>(_host));
            _it = new DfsIterator(composite);
            for (_it->first(); !_it->isDone(); _it->next())
            {
                if (dynamic_cast<Folder *>(_it->currentItem()))
                {
                    _stack.push(dynamic_cast<Folder *>(_it->currentItem()));
                }
            }

            while (!_stack.empty())
            {
                arrangeNodes(_stack.top());
                _stack.pop();
            }

            delete _it;
            _it = new DfsIterator(composite);
        }

        ~OrderByNameIterator() {}

        void first() override
        {
            checkAvailable();
            _it->first();
        }

        Node *currentItem() const override
        {
            return _it->currentItem();
        }

        void next() override
        {
            checkAvailable();
            _it->next();
        }

        bool isDone() const override
        {
            return _it->isDone();
        }

    private:
        Node *const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;
        Iterator *_it;
        std::stack<Folder *> _stack;

        void arrangeNodes(Folder *compound)
        {
            compound->_nodes.sort(compareNodeByName);
        }

        static bool compareNodeByName(const Node *node1, const Node *node2)
        {
            return node1->name() < node2->name();
        }

        void checkAvailable() const
        {
            if (dynamic_cast<Folder *>(_host)->_operationCount != _operationCount)
            {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameWithFolderFirstIterator : public Iterator
    {
    public:
        OrderByNameWithFolderFirstIterator(Folder *composite, int operationCount) : _host(composite), _operationCount(operationCount)
        {
            arrangeNodes(dynamic_cast<Folder *>(_host));
            _it = new DfsIterator(composite);
            for (_it->first(); !_it->isDone(); _it->next())
            {
                if (dynamic_cast<Folder *>(_it->currentItem()))
                {
                    _stack.push(dynamic_cast<Folder *>(_it->currentItem()));
                }
            }

            while (!_stack.empty())
            {
                arrangeNodes(_stack.top());
                _stack.pop();
            }

            delete _it;
            _it = new DfsIterator(composite);
        }

        ~OrderByNameWithFolderFirstIterator() {}

        void first() override
        {
            checkAvailable();
            _it->first();
        }

        Node *currentItem() const override
        {
            return _it->currentItem();
        }

        void next() override
        {
            checkAvailable();
            _it->next();
        }

        bool isDone() const override
        {
            return _it->isDone();
        }

    private:
        Node *const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;
        Iterator *_it;
        std::stack<Folder *> _stack;

        void arrangeNodes(Folder *compound)
        {
            compound->_nodes.sort(compareNodeByName);
        }

        static bool compareNodeByName(Node *node1, Node *node2)
        {
            if (!node1->createIterator()->isDone() && node2->createIterator()->isDone())
            {
                return true;
            }
            else if (node1->createIterator()->isDone() && !node2->createIterator()->isDone())
            {
                return false;
            }

            return node1->name() < node2->name();
        }

        void checkAvailable() const
        {
            if (dynamic_cast<Folder *>(_host)->_operationCount != _operationCount)
            {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByKindIterator : public Iterator
    {
    public:
        OrderByKindIterator(Folder *composite, int operationCount) : _host(composite), _operationCount(operationCount)
        {
            arrangeNodes(dynamic_cast<Folder *>(_host));
            _it = new DfsIterator(composite);
            for (_it->first(); !_it->isDone(); _it->next())
            {
                if (dynamic_cast<Folder *>(_it->currentItem()))
                {
                    _stack.push(dynamic_cast<Folder *>(_it->currentItem()));
                }
            }

            while (!_stack.empty())
            {
                arrangeNodes(_stack.top());
                _stack.pop();
            }

            delete _it;
            _it = new DfsIterator(composite);
        }

        ~OrderByKindIterator() {}

        void first() override
        {
            checkAvailable();
            _it->first();
        }

        Node *currentItem() const override
        {
            return _it->currentItem();
        }

        void next() override
        {
            checkAvailable();
            _it->next();
        }

        bool isDone() const override
        {
            return _it->isDone();
        }

    private:
        Node *const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;
        Iterator *_it;
        std::stack<Folder *> _stack;

        void arrangeNodes(Folder *compound)
        {
            compound->_nodes.sort(compareNodeByName);
        }

        static bool compareNodeByName(Node *node1, Node *node2)
        {
            if (!node1->createIterator()->isDone() && node2->createIterator()->isDone())
            {
                return true;
            }
            else if (node1->createIterator()->isDone() && !node2->createIterator()->isDone())
            {
                return false;
            }

            return node1->name() < node2->name();
        }

        void checkAvailable() const
        {
            if (dynamic_cast<Folder *>(_host)->_operationCount != _operationCount)
            {
                throw "Iterator Not Avaliable";
            }
        }
    };
};
