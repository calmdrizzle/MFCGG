// PolyLine.cpp : ���� �����Դϴ�.
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


// PolyLine ��� �Լ�
//--------------------------------------------------------------------------
//������ �׸� �� �� �߰�
//--------------------------------------------------------------------------
void PolyLine::AddOnePt(CPoint pt)
{
	m_sArrayPoint.Add(pt);
	//FindStartEndPt();
}

//--------------------------------------------------------------------------
//�������� ���� �Լ�
//--------------------------------------------------------------------------
void PolyLine::SetPolyStartPoint(CPoint pt)
{
	m_sArrayPoint.SetAt(0, pt); //��ǥ �������� ������ ����
	//FindStartEndPt();
}

//--------------------------------------------------------------------------
//�������� ���� �Լ�
//--------------------------------------------------------------------------
void PolyLine::SetPolyEndPoint(CPoint pt)
{
	m_sArrayPoint.SetAt(m_sArrayPoint.GetSize() - 1, pt); //��ǥ �������� ������ ����
	//FindStartEndPt();
}