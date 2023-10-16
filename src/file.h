#pragma once

#include "node.h"

class File : public Node
{
private:
    struct stat _sb;

public:
    File(string path) : Node(path)
    {
        if (stat(path.c_str(), &_sb) == -1)
        {
            throw string("error to read");
        }
        else if (S_ISREG(_sb.st_mode))
        {
            cout << "working to read the file" << endl;
        }
        else
        {
            throw string("it is not a file");
        }
    }

    int numberOfFiles() const
    {
        return 1;
    }

    Node *find(string path)
    {
        if (this->path() == path)
        {
            return this;
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
        return pathList;
    }

    void accept(Visitor *visitor) override
    {
        visitor->visitFile(this);
    }
};