#pragma once
#include "Object.h"

// GRectangle 명령 대상입니다.

class GRectangle : public Object
{
protected:
	DECLARE_SERIAL(GRectangle);

private:
	CPoint m_topLeft, m_bottomRight;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;

public:
	GRectangle();
	virtual ~GRectangle();
	void draw(CDC* pDc);
	int drawType(void);
	virtual void Serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setRect(CPoint& topLeft, CPoint& bottomRight);
	//void setProps(int& lineWidth, COLORREF& lineColor, COLORREF& fillColor);
};


