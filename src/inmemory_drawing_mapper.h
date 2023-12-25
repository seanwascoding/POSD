#pragma

#include "drawing_mapper.h"

class InMemoryDrawingMapper : public DrawingMapper
{
public:
    static InMemoryDrawingMapper *instance();

    void add(DomainObject *Drawing) override;

    Drawing *find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    void cleanCache() override;

private:
    static InMemoryDrawingMapper *_instance;
    std::list<DomainObject *> _database;
};