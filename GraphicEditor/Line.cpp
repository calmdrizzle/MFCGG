// Line.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Line.h"

IMPLEMENT_SERIAL(Line, Object, 0)

// Line 생성자

Line::Line()
{
	Object::m_Type = LINE;
}

Line::Line(const Line& ponitL)//복사 생성자
{
	this->Object::m_Type = ponitL.Object::m_Type;
	this->Object::m_LineColor = ponitL.Object::m_LineColor;
	this->Object::m_StartPoint = ponitL.Object::m_StartPoint;
	this->Object::m_EndPoint = ponitL.Object::m_EndPoint;
	this->Object::m_Thickness = ponitL.Object::m_Thickness;
}

Line::~Line()
{
}


void Line::Draw(CDC* pDC)
{
	CPen pen(PS_SOLID, m_Thickness, m_color);
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(m_start);
	pDC->LineTo(m_end);

	pDC->SelectObject(oldPen);
}

int Line::drawType(void) {
	return LINE;
}
void Line::setPoint(CPoint& start, CPoint& end)
{
	m_start = start;
	m_end = end;
}

void Line::setLine(int& lineThickness, COLORREF& color) {
	m_Thickness = lineThickness;
	m_color = color;
}

void Line::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_start << m_end << m_Thickness << m_color;
}

void Line::deserialize(CArchive& ar) {
	ar >> m_start >> m_end >> m_Thickness >> m_color;
}

// Line 멤버 함수
