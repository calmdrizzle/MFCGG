#pragma once
#include "Object.h"

// Text 명령 대상입니다.

class Text : public Object
{
public:
	Text();
	virtual ~Text();
private:
	CString m_str;
	CPoint m_position;
	COLORREF m_fgColor, m_bgColor;
	int m_fontSize;
	CString m_fontName;
	int m_fontMode;

public:
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void insertChar(UINT& nChar);
	void subtractChar(void);
	void setPosition(CPoint& point);
	CPoint& getPosition();
	CString& getString();
	void setColor(COLORREF& fgColor, COLORREF& bgColor);
	void setFontSize(int& fontSize);
	void setFontName(CString& fontName);
	void setFontMode(int& fontMode);
};


