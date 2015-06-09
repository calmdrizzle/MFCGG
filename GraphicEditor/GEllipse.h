#pragma once

// GEllipse 명령 대상입니다.
#include "Object.h"
class GEllipse : public Object
{
protected:
	DECLARE_SERIAL(GEllipse);
private:
	CPoint m_topLeft;
	CPoint m_bottomRight;

	FIGURETYPE m_type;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;

public:
	GEllipse(void);
	virtual ~GEllipse(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setRect(CPoint& topLeft, CPoint& bottomRight);
	void setCircle(CPoint& center, int radius);
	void setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor);

};


