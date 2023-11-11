#pragma once

#include <string>
#include <dirent.h>

using std::string;

class FileSystemScanner
{
public:
    ~FileSystemScanner()
    {
        closedir(dir);
    }

    bool isFile()
    {
        return entry->d_type == 8;
    };

    bool isFolder()
    {
        if (string(entry->d_name) == "." || string(entry->d_name) == "..")
            return false;
        return entry->d_type == 4;
    };

    bool isDone()
    {
        return entry == NULL;
    };

    void setPath(string path)
    {
        dir = opendir(path.c_str());
    };

    string currentNodeName()
    {
        return entry->d_name;
    };

    void nextNode()
    {
        entry = readdir(dir);
    };

private:
    Node *_node;
    string _result;
    DIR *dir;
    struct dirent *entry;
};
