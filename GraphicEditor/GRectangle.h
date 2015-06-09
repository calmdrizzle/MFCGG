#pragma once
#include "Object.h"

// GRectangle 명령 대상입니다.

class GRectangle : public Object
{
protected:
	DECLARE_SERIAL(GRectangle);
	CPoint m_topLeft, m_bottomRight;
	FIGURETYPE m_type;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;
private:

public:
	GRectangle(void);
	virtual ~GRectangle(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setRect(CPoint& topLeft, CPoint& bottomRight);
	void setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor);
};


