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
	}

	Drawing(std::string id, Painter *painter, std::list<Shape *> shapes) : DomainObject(id), _painter(painter), _shapes(shapes)
	{
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
		std::cout << "getShape" << std::endl;
		if (i < 0 || _shapes.size() == 0)
		{
			std::cout << "getShape-null" << std::endl;
			return nullptr;
		}

		std::cout << "getShape-1" << std::endl;
		auto it = _shapes.begin();
		for (int j = 0; j < i; j++)
			it++;

		std::cout << "getShape-2" << std::endl;
		return *it;
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