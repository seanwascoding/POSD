#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"

PainterMapper *PainterMapper::_instance = nullptr;
PainterMapper::PainterMapper()
{
}

Painter *PainterMapper::find(std::string id)
{
}

void PainterMapper::add(DomainObject *Painter)
{
}

void PainterMapper::update(std::string id)
{
}

void PainterMapper::del(std::string id)
{
}

std::string PainterMapper::updateStmt(DomainObject *domainObject) const
{
}

std::string PainterMapper::findByIdStmt(std::string id) const
{
}

std::string PainterMapper::addStmt(DomainObject *domainObject) const
{
}

std::string PainterMapper::deleteByIdStmt(std::string id) const
{
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
}