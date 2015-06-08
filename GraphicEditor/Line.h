#include "Object.h"
#pragma once

// Line 명령 대상입니다.

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


