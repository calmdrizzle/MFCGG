// Object.cpp : ���� �����Դϴ�.
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

void Object::Serialize(CArchive& ar)			//����ȭ
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) //����
	{
		ar << (WORD)m_sType;
		ar << m_StartPoint;
		ar << m_EndPoint;
		ar << m_LineColor;
		ar << m_Thickness;
		ar << (WORD)m_Grouped;

	}
	else //�ε�
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
	CRect rect = getBoundary(); //�׷����� ��ü ������� ���� ����
	return rect.PtInRect(p); //Ŭ�� ������ ���� �ȿ� �ִ��� ��ȯ
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


//�߰�
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
	//R,G,B���� ����
	int nR = GetRValue(color);
	int nG = GetGValue(color);
	int nB = GetBValue(color);

	//�÷� ��ȯ
	return Color(255, nR, nG, nB);
}
// Object ��� �Լ�
