// Line.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Line.h"

// Line 생성자

Line::Line(){
	gobj_type = LINE;
}

Line::~Line()
{
}


void Line::set(int left, int top, int right, int bottom)
{
	point.x = left;
	point.y = top;
	point_end.x = right;
	point_end.y = bottom;
}



void Line::draw(CDC* cdc)
{
	CPen pen(linepattern, thickness, color);
	CPen *oldpen = cdc->SelectObject(&pen);

	cdc->MoveTo(point);
	cdc->LineTo(point_end);

	cdc->SelectObject(&oldpen);
}

CRect Line::getBoundary(){
	CRect crect;

	crect.left = point.x < point_end.x ? point.x : point_end.x;
	crect.top = point.y < point_end.y ? point.y : point_end.y;
	crect.right = point.x >= point_end.x ? point.x : point_end.x;
	crect.bottom = point.y >= point_end.y ? point.y : point_end.y;

	return crect;
}

void Line::move(int dx, int dy)
{
	if (movemode == 0)
	{
		point.x += dx;
		point.y += dy;
		point_end.x += dx;
		point_end.y += dy;
	}

	else if (movemode == 1)
	{
		point.x += dx;
		point.y += dy;
	}
	else if (movemode == 2)
	{
		point_end.x += dx;
		point_end.y += dy;
	}
}

bool Line::isin(CPoint p)
{
	CRect rect = getBoundary();

	if (rect.PtInRect(p)){
		movemode = 0;
		return true;
	}

	else if (CRect(point.x - 5, point.y - 5, point.x + 5, point.y + 5).PtInRect(p))
	{
		movemode = 1;
		return true;
	}

	else if (CRect(point_end.x - 5, point_end.y - 5, point_end.x + 5, point_end.y + 5).PtInRect(p))
	{
		movemode = 2;
		return true;
	}
	else
		return false;

}

void Line::drawBoundary(CDC* cdc)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldpen = cdc->SelectObject(&pen);

	cdc->SelectStockObject(WHITE_BRUSH);

	CPoint p;

	p = point;
	CRect rect(p.x - 5, p.y - 5, p.x + 5, p.y + 5);
	cdc->Rectangle(rect);

	p = point_end;
	rect.SetRect(p.x - 5, p.y - 5, p.x + 5, p.y + 5);
	cdc->Rectangle(rect);

	cdc->SelectObject(&oldpen);
}

void Line::serialize(CArchive &ar, bool serialize_flag){
	serialize_P(ar, serialize_flag);
	if (serialize_flag){
		ar << point_end << linepattern;
	}
	else {
		ar >> point_end >> linepattern;
	}
}
