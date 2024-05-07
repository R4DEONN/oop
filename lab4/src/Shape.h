#ifndef _SHAPE_H
#define _SHAPE_H

#include "IShape.h"

class Shape : virtual public IShape
{
public:
	explicit Shape(uint32_t outlineColor);
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
protected:
	~Shape() = default;
private:
	uint32_t m_outlineColor;
};


#endif //_SHAPE_H
