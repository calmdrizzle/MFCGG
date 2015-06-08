#pragma once
#include "Object.h"

// GRectangle 명령 대상입니다.

class GRectangle : public Object
{
protected:
	DECLARE_SERIAL(GRectangle);

public:
	GRectangle();
	virtual ~GRectangle();
};


