#include <memory>
#include "FigureCollection.h"

void FigureCollection::Insert(const std::shared_ptr<IShape>& shape)
{
	m_shapes.push_back(shape);
}

void FigureCollection::EnumerateShapes(ShapeHandler& cb) const
{
	cb(m_shapes);
}

