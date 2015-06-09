// Text.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Text.h"
#include "Object.h"


// Text

Text::Text()
{
	m_position.SetPoint(0, 0);
}

Text::~Text()
{
}

void Text::draw(CDC* pDc) {
	CFont font;

	font.CreatePointFont(m_fontSize, m_fontName);

	CFont* oldFont = pDc->SelectObject(&font);
	COLORREF oldColor = pDc->SetTextColor(m_fgColor);
	int oldBK = pDc->SetBkMode(m_fontMode);
	COLORREF oldBkColor = pDc->SetBkColor(m_bgColor);

	pDc->TextOut(m_position.x, m_position.y, m_str);

	pDc->SelectObject(oldFont);
	pDc->SetTextColor(oldColor);
	pDc->SetBkMode(oldBK);
	pDc->SetBkColor(oldBkColor);
}

int Text::drawType(void) {
	return TEXT;
}

void Text::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_str << m_position << m_fgColor << m_bgColor << m_fontMode << m_fontSize << m_fontName;
}

void Text::deserialize(CArchive& ar) {
	ar >> m_str >> m_position >> m_fgColor >> m_bgColor >> m_fontMode >> m_fontSize >> m_fontName;
}

void Text::insertChar(UINT& nChar) {
	m_str.AppendChar(nChar);
}

void Text::subtractChar(void) {
	if (m_str.GetLength() > 0) {
		m_str.Delete(m_str.GetLength() - 1);
	}
}

void Text::setPosition(CPoint& point) {
	m_position = point;
}

CPoint& Text::getPosition() {
	return m_position;
}

CString& Text::getString() {
	return m_str;
}
void Text::setColor(COLORREF& fgColor, COLORREF& bgColor)
{
	m_fgColor = fgColor;
	m_bgColor = bgColor;
}

void Text::setFontSize(int& fontSize)
{
	m_fontSize = fontSize;
}
void Text::setFontName(CString& fontName) {
	m_fontName = fontName;
}

void Text::setFontMode(int& fontMode) {
	m_fontMode = fontMode;
}

// Text 멤버 함수
