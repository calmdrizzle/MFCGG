// GEllipse.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "GEllipse.h"

IMPLEMENT_SERIAL(GEllipse, Object, 0)
// GEllipse

GEllipse::GEllipse()
{
}

GEllipse::~GEllipse()
{
}

void GEllipse::draw(CDC* pDc) {
	if (m_type == BORDERONLY) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);

		CPen *oldPen = pDc->SelectObject(&pen);
		CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);

		pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);

}
	else if (m_type == BORDERFILL) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);
		CBrush brush(m_fillColor);

		CPen* oldPen = pDc->SelectObject(&pen);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);

}
	else if (m_type == NOBORDERFILL) {
		CBrush brush(m_fillColor);

		CGdiObject* oldPen = pDc->SelectStockObject(NULL_PEN);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);
}
}

int GEllipse::drawType(void) {
	return ELLIPSE;
}

void GEllipse::setRect(CPoint& topLeft, CPoint& bottomRight) {
	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

void GEllipse::setCircle(CPoint& center, int radius)
{
	m_topLeft.x = center.x - radius;
	m_topLeft.y = center.y - radius;

	m_bottomRight.x = center.x + radius;
	m_bottomRight.y = center.y + radius;
}

void GEllipse::setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor) {
	m_type = type;
	m_Thickness = lineWidth;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}

void GEllipse::serialize(CArchive& ar) {
	int type = m_type;
	ar << drawType();
	ar << m_topLeft << m_bottomRight << type << m_Thickness << m_lineColor << m_fillColor;
}

void GEllipse::deserialize(CArchive& ar) {
	int type;

	ar >> m_topLeft >> m_bottomRight >> type >> m_Thickness >> m_lineColor >> m_fillColor;
	m_type = (FIGURETYPE)type;
}
// GEllipse 멤버 함수
