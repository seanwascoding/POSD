#include "inmemory_drawing_mapper.h"

InMemoryDrawingMapper *InMemoryDrawingMapper::_instance = nullptr;

InMemoryDrawingMapper *InMemoryDrawingMapper::instance()
{
    if (_instance == nullptr)
    {
        _instance = new InMemoryDrawingMapper();
    }
    return _instance;
}

void InMemoryDrawingMapper::add(DomainObject *Drawing)
{
    _database.push_back(Drawing);
};

Drawing *InMemoryDrawingMapper::find(std::string id){

};

void InMemoryDrawingMapper::update(std::string id){

};

void InMemoryDrawingMapper::del(std::string id)
{
    auto it = _database.begin();
    for (auto element : _database)
    {
        if (element->id() == id)
        {
            _database.erase(it);
        }
        it++;
    }
};

void InMemoryDrawingMapper::cleanCache()
{
    _database.clear();
};