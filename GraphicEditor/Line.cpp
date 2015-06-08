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

	// 펜 컬러 및 알파값 지정
	Color penColor = GObject::COLORREFtoColor(GObject::m_sLineColor);
	Pen pen(penColor, REAL(m_nsThickness));

	// 라인의 시작과 끝부분 모양지정
	pen.SetStartCap((LineCap)this->m_nsStartCap);
	pen.SetEndCap((LineCap)this->m_nsEndCap);

	// 펜 스타일 지정
	GObject::SetDashStyle(pen, this->m_nsPenStyle);

	graphics.DrawLine(&pen, Point(GObject::m_sStartPoint.x, GObject::m_sStartPoint.y),
	Point(GObject::m_sEndPoint.x, GObject::m_sEndPoint.y));*/
}


// Line 멤버 함수
