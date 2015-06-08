// Line.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Line.h"

IMPLEMENT_SERIAL(Line, Object, 0)

// Line ������

Line::Line()
{
	Object::m_Type = LINE;
}

Line::Line(const Line& ponitL)//���� ������
{
	this->Object::m_Type = ponitL.Object::m_Type;
	this->Object::m_LineColor = ponitL.Object::m_LineColor;
	this->Object::m_StartPoint = ponitL.Object::m_StartPoint;
	this->Object::m_EndPoint = ponitL.Object::m_EndPoint;
	this->Object::m_Thickness = ponitL.Object::m_Thickness;
	//this->MENU::m_Grouped = pointL.MENU::m_bsGrouped;
}

Line::~Line()
{
}

//--------------------------------------------------------------------------
//���� ��Ÿ�� ���� �Լ�
//--------------------------------------------------------------------------
void Line::SetPenStyle(int penStyle)
{
	this->m_PenStyle = penStyle;
}

//--------------------------------------------------------------------------
//���� ���� ��� ���� �Լ�
//--------------------------------------------------------------------------
void Line::SetStartCap(int startCap)
{
	m_StartCap = startCap;
}

//--------------------------------------------------------------------------
//���� �� ��� ���� �Լ�
//--------------------------------------------------------------------------
void Line::SetEndCap(int endCap)
{
	m_EndCap = endCap;
}

void Line::Draw(CDC* pDC)
{
	//Graphics
	Graphics graphics(*pDC);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);		// Antialiasing

	// �� �÷� �� ���İ� ����
	Color penColor = Object::COLORREFtoColor(Object::m_LineColor);
	Pen pen(penColor, REAL(m_Thickness));

	// ������ ���۰� ���κ� �������
	pen.SetStartCap((LineCap)this->m_StartCap);
	pen.SetEndCap((LineCap)this->m_EndCap);

	// �� ��Ÿ�� ����
	Object::SetDashStyle(pen, this->m_PenStyle);

	graphics.DrawLine(&pen, Point(Object::m_StartPoint.x, Object::m_StartPoint.y),
	Point(Object::m_EndPoint.x, Object::m_EndPoint.y));
}


// Line ��� �Լ�
