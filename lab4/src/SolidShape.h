#ifndef _SOLIDSHAPE_H
#define _SOLIDSHAPE_H

#include "ISolidShape.h"
#include "Shape.h"

class SolidShape : public ISolidShape, public Shape
{
public:
	explicit SolidShape(uint32_t outlineColor, uint32_t fillColor);
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
protected:
	~SolidShape() = default;
private:
	uint32_t m_fillColor;
};


#endif //_SOLIDSHAPE_H
