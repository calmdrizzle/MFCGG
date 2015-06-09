#include "Object.h"
#pragma once

// Line 명령 대상입니다.

class Line : public Object
{
public:
	Line();
	~Line();
	void virtual draw(CDC*);
	void virtual set(int left, int top, int right, int bottom);
	void virtual move(int dx, int dy);

	CRect virtual getBoundary();
	void virtual drawBoundary(CDC*);

	bool virtual isin(CPoint p);

	void virtual serialize(CArchive& ar, bool serialize_flag);
private:

};