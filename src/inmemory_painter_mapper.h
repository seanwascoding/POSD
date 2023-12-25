#pragma

#include "painter_mapper.h"

class InMemoryPainterMapper : public PainterMapper
{
public:
    static InMemoryPainterMapper *instance();

    void add(DomainObject *Drawing) override;

    Painter *find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    void cleanCache() override;

private:
    static InMemoryPainterMapper *_instance;
    std::list<DomainObject *> _database;
};