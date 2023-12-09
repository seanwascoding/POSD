#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>

UnitOfWork *UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork()
{
}

//! extra
UnitOfWork *UnitOfWork::instance()
{
    if (_instance == nullptr)
    {
        _instance = new UnitOfWork();
    }
    return _instance;
}

void UnitOfWork::registerNew(DomainObject *domainObject) {}

void UnitOfWork::registerClean(DomainObject *domainObject)
{
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject *domainObject)
{
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

void UnitOfWork::registerDeleted(DomainObject *domainObject) {}

bool UnitOfWork::inNew(std::string id) const {}

bool UnitOfWork::inClean(std::string id) const
{
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const
{
    return _dirty.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const {}

void UnitOfWork::commit()
{
    for (auto dirty : _dirty)
    {
        DrawingMapper::instance()->update(dirty.second);
        std::cout << _dirty.size() << std::endl;
        registerClean(dirty.second);
    }
    _dirty.clear();
    for (auto newObj : _new)
    {
        PainterMapper::instance()->add(newObj.second);
        registerClean(newObj.second);
    }
    _new.clear();
}