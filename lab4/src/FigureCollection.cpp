#include "FigureCollection.h"

void FigureCollection::Insert(IShape* shape)
{
	m_shapes.push_back(shape);
}

void FigureCollection::EnumerateShapes(ShapeHandler& cb) const
{
	cb(m_shapes);
}

