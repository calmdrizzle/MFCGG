// GRectangle.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "GRectangle.h"

//IMPLEMENT_SERIAL(GRectangle, Object, 0)
// GRectangle

GRectangle::GRectangle()
{
}

GRectangle::~GRectangle()
{
}

void GRectangle::draw(CDC* pDc) {
	if (m_type == BORDERONLY) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);

		CPen *oldPen = pDc->SelectObject(&pen);
		CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);

		pDc->Rectangle(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);

	}
	else if (m_type == BORDERFILL) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);
		CBrush brush(m_fillColor);

		CPen* oldPen = pDc->SelectObject(&pen);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Rectangle(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);

	}
	else if (m_type == NOBORDERFILL) {
		CBrush brush(m_fillColor);

		CGdiObject* oldPen = pDc->SelectStockObject(NULL_PEN);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Rectangle(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);
	}
}

int GRectangle::drawType(void) {
	return RECTANGLE;
}

void GRectangle::serialize(CArchive& ar) {
	int type = m_type;
	ar << drawType();
	ar << m_topLeft << m_bottomRight << m_type << m_Thickness << m_lineColor << m_fillColor;
}

void GRectangle::deserialize(CArchive& ar) {
	int type;
	ar >> m_topLeft >> m_bottomRight >> type >> m_Thickness >> m_lineColor >> m_fillColor;
	m_type = (FIGURETYPE)type;
}

void GRectangle::setRect(CPoint& topLeft, CPoint& bottomRight)
{
	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

void GRectangle::setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor) {
	m_type = type;
	m_Thickness = lineWidth;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}
// GRectangle 멤버 함수
