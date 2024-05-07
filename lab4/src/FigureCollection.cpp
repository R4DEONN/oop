#include <memory>
#include "FigureCollection.h"

void FigureCollection::Insert(const std::shared_ptr<IShape>& shape)
{
	m_shapes.push_back(shape);
}

void FigureCollection::EnumerateShapes(const ShapeHandler& cb) const
{
	for (const auto& shape : m_shapes)
	{
		cb(shape);
	}
}

size_t FigureCollection::GetLength() const
{
	return m_shapes.size();
}

