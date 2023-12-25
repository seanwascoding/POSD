#include "inmemory_painter_mapper.h"

InMemoryPainterMapper *InMemoryPainterMapper::_instance = nullptr;

InMemoryPainterMapper *InMemoryPainterMapper::instance()
{
    if (_instance == nullptr)
    {
        _instance = new InMemoryPainterMapper();
    }
    return _instance;
}

void InMemoryPainterMapper::add(DomainObject *Drawing){

};

Painter *InMemoryPainterMapper::find(std::string id){

};

void InMemoryPainterMapper::update(std::string id){

};

void InMemoryPainterMapper::del(std::string id){

};

void InMemoryPainterMapper::cleanCache(){

};