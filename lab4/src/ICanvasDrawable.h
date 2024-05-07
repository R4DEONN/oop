#ifndef _ICANVASDRAWABLE_H
#define _ICANVASDRAWABLE_H

#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
protected:
	~ICanvasDrawable() = default;
};

#endif //_ICANVASDRAWABLE_H
