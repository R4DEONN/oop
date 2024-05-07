#ifndef _FIGURECOLLECTION_H
#define _FIGURECOLLECTION_H

#include <functional>
#include <map>
#include "IShape.h"
#include "vector"
#include "memory"

using ShapeHandler = std::function<void(const std::shared_ptr<IShape>&)>;

class FigureCollection
{
public:
	FigureCollection() = default;
	void Insert(const std::shared_ptr<IShape>& shape);
	void EnumerateShapes(const ShapeHandler& cb) const;
	size_t GetLength() const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


#endif //_FIGURECOLLECTION_H
