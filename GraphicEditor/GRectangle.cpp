// GRectangle.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "GRectangle.h"

IMPLEMENT_SERIAL(GRectangle, Object, 0)
// GRectangle

GRectangle::GRectangle()
{
}

GRectangle::~GRectangle()
{
}
COLORREF Object::FgColor = RGB(0, 0, 0);
COLORREF Object::BgColor = RGB(255, 255, 255);
int Object::LineWidth = 1;

void GRectangle::draw(CDC* pDc) {

	CPen pen(PS_SOLID, m_Thickness, m_lineColor);

	CPen *oldPen = pDc->SelectObject(&pen);
	CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);

	pDc->Rectangle(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

	pDc->SelectObject(oldBrush);
	pDc->SelectObject(oldPen);
}

int GRectangle::drawType(void) {
	return RECTANGLE;
}

void GRectangle::Serialize(CArchive& ar) {
	//int type = m_type;
	ar << drawType();
	ar << m_topLeft << m_bottomRight/* << m_type*/ << m_Thickness << m_lineColor << m_fillColor;
}

void GRectangle::deserialize(CArchive& ar) {
	//int type;
	ar >> m_topLeft >> m_bottomRight /*>> type*/ >> m_Thickness >> m_lineColor >> m_fillColor;
	//m_type = (FIGURETYPE)type;
}


void GRectangle::setRect(CPoint& topLeft, CPoint& bottomRight)
{
	//m_topLeft = topLeft;
	//m_bottomRight = bottomRight;
}	

/*void GRectangle::setProps(int& lineWidth, COLORREF& lineColor, COLORREF& fillColor) {
	//m_type = type;
	m_Thickness = lineWidth;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}*/
// GRectangle 멤버 함수
