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
    std::cout << "DrawingMapper::find" << std::endl;
    return static_cast<Drawing *>(abstractFind(id, DrawingMapper::callback));
}

std::string DrawingMapper::findByIdStmt(std::string id) const
{
    std::cout << "DrawingMapper::findByIdStmt" << std::endl;
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
    std::cout << "DrawingMapper::add" << std::endl;
    abstractAdd(Drawing);
}

void DrawingMapper::update(std::string id)
{
    std::cout << "DrawingMapper::update" << std::endl;
    abstractUpdate(DrawingMapper::instance()->find(id));
}

void DrawingMapper::del(std::string id)
{
    std::cout << "DrawingMapper::del" << std::endl;
    abstractDelete(id);
}

std::string DrawingMapper::updateStmt(DomainObject *domainObject) const
{
    std::cout << "DrawingMapper::updateStmt" << std::endl;
    Drawing *drawing = static_cast<Drawing *>(domainObject);
    std::string stmt = "UPDATE drawing SET painter='" + drawing->painter()->id() + "' WHERE ID='" + drawing->id() + "'";
    return stmt;
}

std::string DrawingMapper::addStmt(DomainObject *domainObject) const
{
    std::cout << "DrawingMapper::addStmt" << std::endl;
    Drawing *drawing = static_cast<Drawing *>(domainObject);
    std::cout << "DrawingMapper1:" << drawing->id() << std::endl;
    std::cout << "DrawingMapper2:" << drawing->painter()->name() << std::endl;
    std::string stmt = "INSERT INTO drawing (ID, painter) VALUES ('" + drawing->id() + "', '" + drawing->painter()->id() + "')";
    return stmt;
}

std::string DrawingMapper::deleteByIdStmt(std::string id) const
{
    std::cout << "DrawingMapper::deleteByIdStmt" << std::endl;
    std::string stmt = "DELETE FROM drawing WHERE ID='" + id + "'";
    return stmt;
}

int DrawingMapper::callback(void *notUsed, int argc, char **argv, char **colNames)
{
    std::cout << "DrawingMapper::callback:" << argc << std::endl;
    Painter *painter = PainterMapper::instance()->find(argv[1]);
    Drawing *drawing = nullptr;
    if (argv[2])
    {
        std::cout << "DrawingMapper::callback-1:" << argv[0] << ":" << argv[2] << std::endl;
        Parser *parser = new Parser(new Scanner(), new Builder());
        parser->setInput(argv[2]);
        parser->parse();
        drawing = new Drawing(argv[0], painter, parser->getShapes());
    }
    else
    {
        if(argv[0] == "d_0005")
            std::cout << "DrawingMapper::callback-test:" << argv[2] << ":" << argc << std::endl;
        std::cout << "DrawingMapper::callback-2:" << argv[0] << ":" << argc << std::endl;
        drawing = new Drawing(argv[0], painter);
    }
    DrawingMapper::instance()->load(drawing);
    return 0;
}
