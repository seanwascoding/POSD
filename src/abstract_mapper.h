#pragma once

#include <unordered_map>
#include "domain_object.h"
#include "unit_of_work.h"
#include <iostream>
#include "drawing.h"

typedef int (*CallbackType)(void *, int argc, char **argv, char **col_names);

class AbstractMapper
{
public:
    virtual ~AbstractMapper()
    {
    }

    virtual std::string updateStmt(DomainObject *domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string addStmt(DomainObject *domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;

    void setDB(std::string db_file)
    {
        std::cout << "setDB" << std::endl;
        sqlite3_open(db_file.c_str(), &_db);
    }

    bool isLoaded(const std::string &id) const
    {
        std::cout << "isLoaded" << std::endl;
        return _domainObjects.count(id);
    }

    void cleanCache()
    {
        std::cout << "cleanCache" << std::endl;
        _domainObjects.clear();
    }

protected:
    std::unordered_map<std::string, DomainObject *> _domainObjects;
    sqlite3 *_db;

    DomainObject *getDomainObject(std::string id)
    {
        std::cout << "getDomainObject" << std::endl;
        if (_domainObjects.count(id))
        {
            return _domainObjects.at(id);
        }
        return nullptr;
    }

    DomainObject *abstractFind(std::string id, CallbackType callback)
    {
        std::cout << "1" << std::endl;
        DomainObject *domainObject = getDomainObject(id);
        if (domainObject != nullptr)
        {
            std::cout << "not null" << std::endl;
            return domainObject;
        }
        std::cout << "2" << std::endl;
        sqlite3_exec(_db, findByIdStmt(id).c_str(), callback, NULL, &_errorMessage);
        DomainObject *object = getDomainObject(id);
        if (object != nullptr)
        {
            std::cout << "work to add" << std::endl;
            UnitOfWork::instance()->registerClean(object);
        }
        std::cout << "3" << ":"<< id << std::endl;
        if(object == nullptr)
            std::cout << "fail" << std::endl;
        else
            std::cout << "4" << ":"<< object->id() << std::endl;
        return object;
    };

    void abstractAdd(DomainObject *domainObject)
    {
        std::cout << "abstractAdd" << std::endl;
        int temp = sqlite3_exec(_db, addStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
        std::cout << "abstractAdd - result:" << (temp == SQLITE_OK) << std::endl;
    };

    void abstractUpdate(DomainObject *domainObject)
    {
        std::cout << "abstractUpdate" << std::endl;
        sqlite3_exec(_db, updateStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
    };

    void abstractDelete(std::string id)
    {
        std::cout << "abstractDelete" << std::endl;
        _domainObjects.erase(id);
        sqlite3_exec(_db, deleteByIdStmt(id).c_str(), NULL, NULL, &_errorMessage);
    };

    void load(DomainObject *domainObject)
    {
        std::cout << "load" << std::endl;
        _domainObjects[domainObject->id()] = domainObject;
    };

private:
    char *_errorMessage;
};