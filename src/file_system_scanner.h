#pragma once

#include <string>
#include <dirent.h>
#include <sstream>

using std::string;

class FileSystemScanner
{
public:
    bool isFile(){

    };

    bool isFolder();

    bool isDone();

    void setPath(string path)
    {
        _path = path;
    };

    string currentNodeName(){

    };

    void nextNode(){
        
    };

private:
    Node *_node;
    string _path;
};
