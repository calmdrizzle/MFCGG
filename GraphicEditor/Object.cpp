// Object.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Object.h"


// Object

Object::Object()
{
	thickness = 5;
	color = RGB(255, 255, 255);
	selected = false;
}

Object::~Object()
{
}
bool Object::isin(CPoint p)
{
	CRect crect = getBoundary();

	if (crect.left <= p.x && p.x <= crect.right
		&& crect.top <= p.y && p.y <= crect.bottom)
		return true;
	else
		return false;
}

void Object::serialize_P(CArchive& ar, bool serialize_flag)
{
	if (serialize_flag){
		int temp = gobj_type;
		ar << temp << thickness << color << point << movemode << selected;
		serialize_flag = true;
	}
	else {
		ar >> thickness >> color >> point >> movemode >> selected;
		serialize_flag = false;
	}
}

// Object 멤버 함수
