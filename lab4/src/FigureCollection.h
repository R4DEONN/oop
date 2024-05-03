#ifndef _FIGURECOLLECTION_H
#define _FIGURECOLLECTION_H

#include <functional>
#include <map>
#include "IShape.h"
#include "vector"
#include "memory"

using ShapeHandler = const std::function<void(const std::vector<std::shared_ptr<IShape>>&)>;

class FigureCollection
{
public:
	FigureCollection() = default;
	void Insert(const std::shared_ptr<IShape>& shape);
	void EnumerateShapes(ShapeHandler& cb) const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


#endif //_FIGURECOLLECTION_H
