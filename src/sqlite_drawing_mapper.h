#pragma

#include "drawing_mapper.h"

class SQLiteDrawingMapper : public DrawingMapper, public SQLiteAbstractMapper
{
public:
    ~SQLiteDrawingMapper()
    {
        delete _parser;
    }

    void add(DomainObject *Drawing) override;

    Drawing *find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    static DrawingMapper *instance();

    void cleanCache() override;

protected:
    SQLiteDrawingMapper();

    static int callback(void *notUsed, int argc, char **argv, char **colNames);

    std::list<Shape *> convertShapes(char *shape_string);

    std::string addStmt(DomainObject *domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject *domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    static DrawingMapper *_instance;
    Parser *_parser;
};