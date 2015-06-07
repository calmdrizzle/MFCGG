// Object.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Object.h"


// Object

Object::Object()
{
}

Object::~Object()
{
}

void Object::Serialize(CArchive& ar)			//직렬화
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) //저장
	{
		ar << (WORD)m_sType;
		ar << m_StartPoint;
		ar << m_EndPoint;
		ar << m_LineColor;
		ar << m_Thickness;
		ar << (WORD)m_Grouped;

	}
	else //로드
	{
		WORD wTemp;
		ar >> wTemp; m_sType = (GraphicObjectType)wTemp;
		ar >> m_StartPoint;
		ar >> m_EndPoint;
		ar >> m_LineColor;
		ar >> m_Thickness;
		ar >> wTemp; m_Grouped = (BOOL)wTemp;

	}
}



bool Object::isin(CPoint p)
{
	CRect rect = getBoundary(); //그래피컬 개체 모양으로 리전 생성
	return rect.PtInRect(p); //클릭 지점이 리전 안에 있는지 반환
}

Point Object::CPointToPoint(CPoint point)
{
	return Point(point.x, point.y);
}

void Object::SetStartPoint(CPoint pt)
{
	m_StartPoint = pt;
}

void Object::SetEndPoint(CPoint endPoint)
{
	m_EndPoint = endPoint;
}

void Object::SetLineColor(COLORREF color)
{
	m_LineColor = color;
}


//추가
void Object::SetFigureLineColor(COLORREF color)
{
	m_FigureLineColor = color;
}


void Object::SetThickness(int thickness)
{
	m_Thickness = thickness;
}

void Object::SetGrouped(BOOL isGrouped)
{
	m_Grouped = isGrouped;
}

void Object::SetDashStyle(Pen& pen, int nPenStyle)
{
	pen.SetDashStyle((DashStyle)nPenStyle);
}

Color Object::COLORREFtoColor(COLORREF color)
{
	//R,G,B값을 얻어옴
	int nR = GetRValue(color);
	int nG = GetGValue(color);
	int nB = GetBValue(color);

	//컬러 반환
	return Color(255, nR, nG, nB);
}
// Object 멤버 함수
