#ifndef _ISHAPE_H
#define _ISHAPE_H

#include <string>
#include <cstdint>
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
	[[nodiscard]] virtual double GetArea() const = 0;
	[[nodiscard]] virtual double GetPerimeter() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;
protected:
	~IShape() = default;
};


#endif //_ISHAPE_H
