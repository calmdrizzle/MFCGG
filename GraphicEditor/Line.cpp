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

void Line::Draw(CDC* pDC)
{
	//Graphics
	/*Graphics graphics(*pDC);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);		// Antialiasing

	// �� �÷� �� ���İ� ����
	Color penColor = GObject::COLORREFtoColor(GObject::m_sLineColor);
	Pen pen(penColor, REAL(m_nsThickness));

	// ������ ���۰� ���κ� �������
	pen.SetStartCap((LineCap)this->m_nsStartCap);
	pen.SetEndCap((LineCap)this->m_nsEndCap);

	// �� ��Ÿ�� ����
	GObject::SetDashStyle(pen, this->m_nsPenStyle);

	graphics.DrawLine(&pen, Point(GObject::m_sStartPoint.x, GObject::m_sStartPoint.y),
	Point(GObject::m_sEndPoint.x, GObject::m_sEndPoint.y));*/
}


// Line ��� �Լ�
