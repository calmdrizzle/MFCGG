#pragma once
#include "Object.h"

// GRectangle ��� ����Դϴ�.

class GRectangle : public Object
{
protected:
	DECLARE_SERIAL(GRectangle);

public:
	GRectangle();
	virtual ~GRectangle();
};


