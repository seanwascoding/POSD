#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"
#include "drawing_mapper.h"

PainterMapper *PainterMapper::_instance = nullptr;
PainterMapper::PainterMapper()
{
}

Painter *PainterMapper::find(std::string id)
{
    std::cout << "PainterMapper::find" << std::endl;
    return static_cast<Painter *>(abstractFind(id, PainterMapper::callback));
}

void PainterMapper::add(DomainObject *Painter)
{
    std::cout << "PainterMapper::add" << std::endl;
    abstractAdd(Painter);
}

void PainterMapper::update(std::string id)
{
    std::cout << "PainterMapper::update" << std::endl;
    abstractUpdate(DrawingMapper::instance()->find(id));
}

void PainterMapper::del(std::string id)
{
    std::cout << "PainterMapper::del" << std::endl;
    abstractDelete(id);
}

std::string PainterMapper::updateStmt(DomainObject *domainObject) const
{
    std::cout << "PainterMapper::updateStmt" << std::endl;
    Painter *painter = dynamic_cast<Painter *>(domainObject);
    std::cout << "PainterMapper::updateStmt-2" << std::endl;
    std::string stmt = "UPDATE painter SET name='" + painter->name() + "' WHERE ID='" + painter->id() + "'";
    std::cout << "PainterMapper::updateStmt-3" << std::endl;
    return stmt;
}

std::string PainterMapper::findByIdStmt(std::string id) const
{
    std::cout << "PainterMapper::findByIdStmt" << std::endl;
    std::string stmt = "SELECT * FROM painter WHERE ID='" + id + "'";
    return stmt;
}

std::string PainterMapper::addStmt(DomainObject *domainObject) const
{
    std::cout << "PainterMapper::addStmt" << std::endl;
    Painter *painter = static_cast<Painter *>(domainObject);
    std::cout << painter->id() << std::endl;
    std::cout << painter->name() << std::endl;
    std::string stmt = "INSERT INTO painter (Name, ID) VALUES ('" + painter->name() + "', '" + painter->id() + "')";
    return stmt;
}

std::string PainterMapper::deleteByIdStmt(std::string id) const
{
    std::cout << "PainterMapper::deleteByIdStmt" << std::endl;
    std::string stmt = "DELETE FROM painter WHERE ID='" + id + "'";
    return stmt;
}

PainterMapper *PainterMapper::instance()
{
    if (_instance == nullptr)
    {
        _instance = new PainterMapper();
    }
    return _instance;
}

int PainterMapper::callback(void *notUsed, int argc, char **argv, char **colNames)
{
    std::cout << "PainterMapper::callback" << std::endl;
    Painter *painter = new Painter(argv[0], argv[1]);
    PainterMapper::instance()->load(painter);
    return 0;
}