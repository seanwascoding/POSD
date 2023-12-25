#pragma

#include "painter_mapper.h"

class SQLitePainterMapper : public SQLiteAbstractMapper, public PainterMapper
{
public:
    ~SQLitePainterMapper(){};

    void add(DomainObject *Drawing) override;

    Painter *find(std::string id) override;

    void update(std::string id) override;

    void del(std::string id) override;

    static SQLitePainterMapper *instance();

    void cleanCache() override;

private:
    SQLitePainterMapper();

    static int callback(void *notUsed, int argc, char **argv, char **colNames);

    std::string addStmt(DomainObject *domainObject) const override;
    std::string findByIdStmt(std::string id) const override;
    std::string updateStmt(DomainObject *domainObject) const override;
    std::string deleteByIdStmt(std::string id) const override;

private:
    static SQLitePainterMapper *_instance;
};