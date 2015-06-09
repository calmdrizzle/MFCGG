// GEllipse.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "GEllipse.h"
#include "Object.h"
IMPLEMENT_SERIAL(GEllipse, Object, 0)
// GEllipse

GEllipse::GEllipse()
{
	Object::m_Type = ELLIPSE;
	m_FillColor = RGB(255, 255, 255);
}

GEllipse::~GEllipse()
{
}

void GEllipse::Serialize(CArchive& ar)
{
	Object::Serialize(ar);
	if (ar.IsStoring()) //저장
	{
		ar << (WORD)m_PenStyle;
		ar << m_FillColor;
	}
	else //로드
	{
		WORD wTemp;
		ar >> wTemp; m_PenStyle = wTemp;
		ar >> m_FillColor;
	}
}

int GEllipse::GetPenStyle()
{
	return m_PenStyle;
}

COLORREF GEllipse::GetFillColor()
{
	return m_FillColor;
}

void GEllipse::Move(int dX, int dY){

	Object::m_StartPoint.Offset(dX, dY);
	Object::m_EndPoint.Offset(dX, dY);
}


void GEllipse::SetPenStyle(int penStyle)
{
	m_PenStyle = penStyle;
}

void GEllipse::SetFillColor(COLORREF brushColor) {
	this->m_FillColor = brushColor;
}

CRect GEllipse::getBoundary()
{
	CRect crect;

	crect.left = m_StartPoint.x < m_EndPoint.x ? m_StartPoint.x : m_EndPoint.x;
	crect.top = m_StartPoint.y < m_EndPoint.y ? m_StartPoint.y : m_EndPoint.y;
	crect.right = m_StartPoint.x >= m_EndPoint.x ? m_StartPoint.x : m_EndPoint.x;
	crect.bottom = m_StartPoint.y >= m_EndPoint.y ? m_StartPoint.y : m_EndPoint.y;

	return crect;
}
void GEllipse::drawBoundary(CDC* cdc)
{
	CRect rect = getBoundary();
	CPen pen(PS_DOT, 1, RGB(0, 0, 0));

	cdc->SelectObject(&pen);
	cdc->SelectStockObject(NULL_BRUSH);
	cdc->Rectangle(rect);

	cdc->SelectStockObject(WHITE_BRUSH);
	CRect box(rect.BottomRight().x - 5, rect.BottomRight().y - 5, rect.BottomRight().x + 5, rect.BottomRight().y + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.TopLeft().x - 5, rect.TopLeft().y - 5, rect.TopLeft().x + 5, rect.TopLeft().y + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.left - 5, rect.bottom - 5, rect.left + 5, rect.bottom + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.right - 5, rect.top - 5, rect.right + 5, rect.top + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.CenterPoint().x - 5, rect.bottom - 5, rect.CenterPoint().x + 5, rect.bottom + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.CenterPoint().x - 5, rect.top - 5, rect.CenterPoint().x + 5, rect.top + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.right - 5, rect.CenterPoint().y - 5, rect.right + 5, rect.CenterPoint().y + 5);
	cdc->Rectangle(box);

	box.SetRect(rect.left - 5, rect.CenterPoint().y - 5, rect.left + 5, rect.CenterPoint().y + 5);
	cdc->Rectangle(box);
}
bool GEllipse::isin(CPoint p)
{
	CRect rect = getBoundary();

	m_StartPoint = rect.TopLeft();
	m_EndPoint = rect.BottomRight();

	if (rect.left - p.x < 5 && rect.left - p.x > -5){
		if (rect.top - p.y <5 && rect.top - p.y> -5)
			moveMode = 1;
		else if (rect.bottom - p.y <5 && rect.bottom - p.y>-5)
			moveMode = 7;
		else
			moveMode = 8;

		return true;
	}
	else if (rect.right - p.x < 5 && rect.right - p.x >-5){
		if (rect.top - p.y <5 && rect.top - p.y> -5)
			moveMode = 3;
		else if (rect.bottom - p.y <5 && rect.bottom - p.y>-5)
			moveMode = 5;
		else
			moveMode = 4;
		return true;
	}
	else{
		if (rect.top - p.y <5 && rect.top - p.y> -5)
		{
			moveMode = 2;
			return true;
		}
		else if (rect.bottom - p.y <5 && rect.bottom - p.y>-5)
		{
			moveMode = 6;
			return true;
		}
		else if (CRect(getBoundary()).PtInRect(p))
		{
			moveMode = 0;
			return true;
		}
		else
			return false;
	}
}

void GEllipse::Draw(CDC* cdc){
	Graphics graphics(*cdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);		// Antialiasing

	// 펜 컬러 및 알파값 지정
	Color penColor = Object::COLORREFtoColor(Object::GetFigureLineColor());
	Color foreColor = Object::COLORREFtoColor(Object::m_fillColor);

	Pen pen(penColor, Object::m_Thickness);

	Object::SetDashStyle(pen, this->m_PenStyle); //라인 패턴 설정

	Rect tempRect(Object::m_StartPoint.x, Object::m_StartPoint.y,
		Object::m_EndPoint.x - Object::m_StartPoint.x, Object::m_EndPoint.y - Object::m_StartPoint.y);

	//브러쉬 선언
	SolidBrush pSolidBrush(foreColor);	//단색 브러쉬
	HatchBrush pHatchBrush((HatchStyle)m_n_HatchStyle, foreColor, Color::Transparent); // 격자무늬 브러쉬

	//없으면 내부색상 사라짐
	graphics.FillEllipse(&pSolidBrush, tempRect);
	//없으면 외곽선 사라짐
	graphics.DrawEllipse(&pen, tempRect);

}
// GEllipse 멤버 함수
