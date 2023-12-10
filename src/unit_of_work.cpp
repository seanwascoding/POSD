#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>

UnitOfWork *UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() {}

//! extra
UnitOfWork *UnitOfWork::instance()
{
    if (_instance == nullptr)
    {
        _instance = new UnitOfWork();
    }
    return _instance;
}

void UnitOfWork::registerNew(DomainObject *domainObject)
{
    std::cout << "new" << std::endl;
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerClean(DomainObject *domainObject)
{
    std::cout << "clean" << std::endl;
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject *domainObject)
{
    std::cout << "dirty" << std::endl;
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

void UnitOfWork::registerDeleted(DomainObject *domainObject)
{
    std::cout << "deleted" << std::endl;
    _deleted[domainObject->id()] = domainObject;
    _new.erase(domainObject->id());
    _clean.erase(domainObject->id());
    if (dynamic_cast<Drawing *>(domainObject))
    {
        std::cout << "deleted-drawing" << std::endl;
        DrawingMapper::instance()->del(domainObject->id());
    }
    else
    {
        std::cout << "deleted-painter" << std::endl;
        PainterMapper::instance()->del(domainObject->id());
    }
}

bool UnitOfWork::inNew(std::string id) const
{
    std::cout << "innew" << std::endl;
    return _new.count(id);
}

bool UnitOfWork::inClean(std::string id) const
{
    std::cout << "inclean" << std::endl;
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const
{
    std::cout << "indirty" << std::endl;
    return _dirty.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const
{
    std::cout << "indelete" << std::endl;
    return _deleted.count(id);
}

void UnitOfWork::commit()
{
    std::cout << "commit" << std::endl;
    for (auto dirty : _dirty)
    {
        if (dynamic_cast<Drawing *>(dirty.second))
            DrawingMapper::instance()->update(dirty.second->id());
        else
            PainterMapper::instance()->update(dirty.second->id());
        registerClean(dirty.second);
    }
    _dirty.clear();
    for (auto newObj : _new)
    {
        if (dynamic_cast<Drawing *>(newObj.second))
            DrawingMapper::instance()->add(newObj.second);
        else
            PainterMapper::instance()->add(newObj.second);
        registerClean(newObj.second);
    }
    _new.clear();
    std::cout << "commit end" << std::endl;
}