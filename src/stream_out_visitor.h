#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor
{
private:
    string _contents;

public:
    void visitFile(File *file) override
    {
        ifstream input(file->path());
        if (!input)
        {
            std::cerr << "Cannot open: " << file->name() << std::endl;
            return;
        }

        std::stringstream contentStream;

        contentStream << "_____________________________________________" << "\n";
        contentStream << file->path() << '\n';
        contentStream << "---------------------------------------------" << "\n";

        std::string line;
        while (std::getline(input, line))
        {
            // std::cout << line << std::endl;
            // _contents.append(line + "\n");
            contentStream << line << "\n";
        }
        input.close();

        contentStream << "_____________________________________________" << "\n";

        _contents.append(contentStream.str());
    };

    void visitFolder(Folder *folder) override
    {
        auto it = folder->dfsIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            it->currentItem()->accept(this);
            _contents.append("\n");
        }
        delete it;
    };

    string getResult() const
    {
        return _contents;
    };
};