// Line.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Line.h"

// Line 생성자

Line::Line()
{
}
Line::~Line()
{
}

void Line::draw(CDC* pDc) {
	CPen pen(PS_SOLID, m_lineThickness, m_color);
	CPen* oldPen = pDc->SelectObject(&pen);

	pDc->MoveTo(m_start);
	pDc->LineTo(m_end);

	pDc->SelectObject(oldPen);
}

int Line::drawType(void) {
	return LINE;
}
void Line::setPoint(CPoint& start, CPoint& end)
{
	m_start = start;
	m_end = end;
}

void Line::setBeeLine(int& lineThickness, COLORREF& color) {
	m_lineThickness = lineThickness;
	m_color = color;
}

void Line::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_start << m_end << m_lineThickness << m_color;
}

void Line::deserialize(CArchive& ar) {
	ar >> m_start >> m_end >> m_lineThickness >> m_color;
}

