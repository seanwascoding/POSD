#pragma once

#include <string>
#include <list>
#include "domain_object.h"
#include "shape.h"
#include "painter.h"

class Drawing : public DomainObject
{
public:
	Drawing(std::string id, Painter *painter) : DomainObject(id), _painter(painter)
	{
		std::cout << "Drawing--1:" << _id << std::endl;
	}

	Drawing(std::string id, Painter *painter, std::list<Shape *> shapes) : DomainObject(id), _painter(painter), _shapes(shapes)
	{
		std::cout << "Drawing--2:" << _id << ":" << _shapes.size() << std::endl;
	}

	Painter *painter() const
	{
		std::cout << "painter" << std::endl;
		return _painter;
	}

	void setPainter(Painter *painter)
	{
		std::cout << "setPainter" << std::endl;
		_painter = painter;
		UnitOfWork::instance()->registerDirty(this);
	}

	Shape *getShape(int i) const
	{
		std::cout << "getShape:" << this->_id << std::endl;
		std::cout << "getShape:" << this->_painter->id() << std::endl;
		std::cout << "getShape:" << i << std::endl;
		if (i < 0 || _shapes.size() == 0)
		{
			std::cout << "getShape-null" << std::endl;
			// throw "error";
			return nullptr;
		}

		std::cout << "getShape-1" << std::endl;
		auto it = _shapes.begin();
		for (int j = 0; j < i; j++)
			it++;

		std::cout << "getShape-2:" << (*it)->toString() << std::endl;
		return (*it);
	}

	std::string getShapesAsString() const
	{
		std::cout << "getShapesAsString" << std::endl;
		std::string result = "";
		for (auto shape : _shapes)
		{
			result += shape->toString() + "\n";
		}
		return result;
	}

private:
	Painter *_painter;
	std::list<Shape *> _shapes;
};