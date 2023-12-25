#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "sqlite_abstract_mapper.h"

class PainterMapper
{
public:
    virtual void add(DomainObject *Painter) = 0;

    virtual Painter *find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    static PainterMapper *instance();

    virtual void cleanCache() = 0;

protected:
    // PainterMapper();

    // static int callback(void *notUsed, int argc, char **argv, char **colNames);

    // std::string addStmt(DomainObject *domainObject) const;
    // std::string findByIdStmt(std::string id) const;
    // std::string updateStmt(DomainObject *domainObject) const;
    // std::string deleteByIdStmt(std::string id) const;

private:
    static PainterMapper *_instance;
};