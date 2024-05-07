#ifndef _ISOLIDSHAPE_H
#define _ISOLIDSHAPE_H

#include "IShape.h"

class ISolidShape : virtual public IShape
{
	virtual uint32_t GetFillColor() const = 0;
};

#endif //_ISOLIDSHAPE_H
