#include "Object.h"
#pragma once

// Line ��� ����Դϴ�.

class Line : public Object
{
protected:
	DECLARE_SERIAL(Line);
public:
	Line();
	Line(const Line& pointL);

	virtual ~Line();
	void Draw(CDC* cdc);

private:

};


