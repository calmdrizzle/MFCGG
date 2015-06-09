#include "Object.h"
#pragma once

// Line 명령 대상입니다.

class Line : public Object
{
private:
	CPoint m_start;
	CPoint m_end;

	int m_lineThickness;
	COLORREF m_color;

public:
	Line(void);
	virtual ~Line(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setPoint(CPoint& start, CPoint& end);
	void setBeeLine(int& lineWidth, COLORREF& color);
};


