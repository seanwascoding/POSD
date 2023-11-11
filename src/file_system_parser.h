#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser
{
public:
    FileSystemParser(FileSystemBuilder *builder) : _builder(builder){};

    Folder *getRoot() const
    {
        return _builder->getRoot();
    };

    void parse()
    {
        _scanner = _stacks.top();
        _scanner->nextNode();
        while (!_scanner->isDone())
        {
            if (_scanner->isFolder())
            {
                cout << "folder:" << _scanner->currentNodeName() << endl;
                setPath(_scanner->currentNodeName());
                _builder->buildFolder(_path);
                _path += '/';
            }
            else if (_scanner->isFile())
            {
                cout << "file:" << _scanner->currentNodeName() << endl;
                _builder->buildFile(_path + _scanner->currentNodeName());
            }

            _scanner = _stacks.top();
            _scanner->nextNode();

            if (_scanner->isDone())
            {
                cout << "end folder" << endl;
                //! remove path
                size_t pos = _path.rfind('/');
                size_t pos2 = _path.rfind('/', pos - 1);
                _path.erase(pos2 + 1);

                //! switch
                _stacks.pop();
                if (_stacks.empty())
                {
                    continue;
                }
                else
                {
                    _scanner = _stacks.top();
                    _builder->endFolder();
                    _scanner->nextNode();
                }
            }
        }
    };

    void setPath(string path)
    {
        _path += path;
        // cout << _path << endl;
        FileSystemScanner *scanner = new FileSystemScanner();
        scanner->setPath(_path);
        _stacks.push(scanner);
        if (_state == 0)
        {
            _builder->buildFolder(_path);
            _path += '/';
        }
        _state++;
    };

private:
    FileSystemBuilder *_builder;
    FileSystemScanner *_scanner;
    stack<FileSystemScanner *> _stacks;
    string _path;
    int _state = 0;
};
