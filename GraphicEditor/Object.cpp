// Object.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Object.h"


// Object
COLORREF Object::FgColor = RGB(0, 0, 0);
COLORREF Object::BgColor = RGB(255, 255, 255);
int Object::LineWidth = 1;
FIGURETYPE Object::FigureType = BORDERONLY;
int Object::FontSize = 100;
CString Object::FontName = _T("Arial");
int Object::FontMode = TRANSPARENT;

Object::Object()
{
}

Object::~Object()
{
}