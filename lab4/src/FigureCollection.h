#ifndef _FIGURECOLLECTION_H
#define _FIGURECOLLECTION_H

#include <functional>
#include <map>
#include "IShape.h"
#include "vector"

using ShapeHandler = const std::function<void(const std::vector<IShape*>&)>;

class FigureCollection
{
public:
	FigureCollection() = default;
	void Insert(IShape* shape);
	void EnumerateShapes(ShapeHandler& cb) const;
private:
	std::vector<IShape*> m_shapes;
};


#endif //_FIGURECOLLECTION_H
