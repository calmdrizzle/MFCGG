// PolyLine.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "PolyLine.h"
#include "Object.h"

IMPLEMENT_SERIAL(PolyLine, Object, 0)
// PolyLine

PolyLine::PolyLine()
{
	Object::m_Type = POLYLINE;
}

PolyLine::PolyLine(const PolyLine& pPoly)
{
	this->Object::m_Type = pPoly.Object::m_Type;
	this->Object::m_StartPoint = pPoly.Object::m_StartPoint;
	this->Object::m_EndPoint = pPoly.Object::m_EndPoint;
	this->Object::m_LineColor = pPoly.Object::m_LineColor;
	this->Object::m_Thickness = pPoly.Object::m_Thickness;
}

PolyLine::~PolyLine()
{
}


// PolyLine 멤버 함수
//--------------------------------------------------------------------------
//　점을 그릴 때 점 추가
//--------------------------------------------------------------------------
void PolyLine::AddOnePt(CPoint pt)
{
	m_sArrayPoint.Add(pt);
	//FindStartEndPt();
}

//--------------------------------------------------------------------------
//　시작점 설정 함수
//--------------------------------------------------------------------------
void PolyLine::SetPolyStartPoint(CPoint pt)
{
	m_sArrayPoint.SetAt(0, pt); //좌표 시퀀스의 시작점 지정
	//FindStartEndPt();
}

//--------------------------------------------------------------------------
//　종료점 설정 함수
//--------------------------------------------------------------------------
void PolyLine::SetPolyEndPoint(CPoint pt)
{
	m_sArrayPoint.SetAt(m_sArrayPoint.GetSize() - 1, pt); //좌표 시퀀스의 종료점 지정
	//FindStartEndPt();
}