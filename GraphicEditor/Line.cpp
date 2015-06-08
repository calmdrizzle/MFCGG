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

//--------------------------------------------------------------------------
//　펜 스타일 설정 함수
//--------------------------------------------------------------------------
void Line::SetPenStyle(int penStyle)
{
	this->m_PenStyle = penStyle;
}

//--------------------------------------------------------------------------
//　선 시작 모양 설정 함수
//--------------------------------------------------------------------------
void Line::SetStartCap(int startCap)
{
	m_StartCap = startCap;
}

//--------------------------------------------------------------------------
//　선 끝 모양 설정 함수
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

	// 펜 컬러 및 알파값 지정
	Color penColor = Object::COLORREFtoColor(Object::m_LineColor);
	Pen pen(penColor, REAL(m_Thickness));

	// 라인의 시작과 끝부분 모양지정
	pen.SetStartCap((LineCap)this->m_StartCap);
	pen.SetEndCap((LineCap)this->m_EndCap);

	// 펜 스타일 지정
	Object::SetDashStyle(pen, this->m_PenStyle);

	graphics.DrawLine(&pen, Point(Object::m_StartPoint.x, Object::m_StartPoint.y),
	Point(Object::m_EndPoint.x, Object::m_EndPoint.y));
}


// Line 멤버 함수
