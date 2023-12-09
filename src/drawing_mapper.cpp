#include "drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "painter_mapper.h"

DrawingMapper *DrawingMapper::_instance = nullptr;

Drawing *DrawingMapper::find(std::string id)
{
    return static_cast<Drawing *>(abstractFind(id, DrawingMapper::callback));
}

std::string DrawingMapper::findByIdStmt(std::string id) const
{
    std::string stmt = "SELECT * FROM drawing WHERE ID = '" + id + "'";
    return stmt;
}

DrawingMapper *DrawingMapper::instance()
{
    if (_instance == nullptr)
    {
        _instance = new DrawingMapper();
    }
    return _instance;
}

DrawingMapper::DrawingMapper()
{
    _builder = new Builder();
    _scanner = new Scanner();
    _parser = new Parser(_scanner, _builder);
}

std::list<Shape *> DrawingMapper::convertShapes(int argc, char **argv)
{
    std::cout << "convertShapes" << std::endl;
    _parser->clear();
    _parser->setInput(argv[2]);
    _parser->parse();
    return _parser->getShapes();
}

//! extra

void DrawingMapper::add(DomainObject *Drawing) 
{
    abstractAdd(Drawing);
}

void DrawingMapper::update(std::string id)
{
    abstractUpdate(DrawingMapper::instance()->find(id));
}

void DrawingMapper::del(std::string id) 
{
    abstractDelete(id);
}

std::string DrawingMapper::updateStmt(DomainObject *domainObject) const 
{
    Drawing *drawing = static_cast<Drawing *>(domainObject);
    std::string stmt = "UPDATE drawing SET Painter='" + drawing->painter()->id() + "' WHERE ID='" + drawing->id() + "'";
    return stmt;
}

std::string DrawingMapper::addStmt(DomainObject *domainObject) const 
{
    Drawing *drawing = static_cast<Drawing *>(domainObject);
    std::string stmt = "INSERT INTO drawing (ID, Painter) VALUES ('" + drawing->id() + "', '" + drawing->painter()->id() + "')";
    return stmt;
}

std::string DrawingMapper::deleteByIdStmt(std::string id) const 
{
    std::string stmt = "DELETE FROM drawing WHERE ID='" + id + "'";
    return stmt;
}

int DrawingMapper::callback(void *notUsed, int argc, char **argv, char **colNames)
{
    std::cout << "DrawingMapper::callback" << std::endl;
    Painter *painter = PainterMapper::instance()->find(argv[1]);
    Parser *parser = new Parser(new Scanner(), new Builder());
    parser->setInput(argv[2]);
    parser->parse();
    Drawing *drawing = new Drawing(argv[0], painter, parser->getShapes());
    DrawingMapper::instance()->load(drawing);
    return 0;
}
