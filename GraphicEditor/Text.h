#pragma once
#include "Object.h"
#include "stdafx.h"

// Text 명령 대상입니다.

class Text : public Object
{
public:
	Text();
	~Text();
	void virtual draw(CDC*);
	void virtual set(int left, int top, int right, int bottom);
	void virtual move(int dx, int dy);

	bool virtual isin(CPoint p);

	CRect virtual getBoundary();

	void setSize(int n) { size = n; }
	int getSize() { return size; }

	void setFont(CString f) { fontName = f; }
	CString getFontName(){ return fontName; }

	void setItalic(bool s) { bItalic = s; }
	bool getItalic() { return bItalic; }

	void setUnderline(bool s) { bUnderline = s; }
	bool getUnderline() { return bUnderline; }

	void setChar(TCHAR a) { nChar = a; }

	bool beenIn(CRect rect)
	{
		if (rect.PtInRect(point) && rect.PtInRect(point_end))
			return true;
		else
			return false;
	}

	CPoint getPoint_end(){ return point_end; }
	void virtual drawBoundary(CDC*);

	void virtual serialize(CArchive& ar, bool serialize_flag);

private:
	CString fontName;
	CArray <TCHAR, TCHAR> str;
	bool bItalic, bUnderline;
	int size;
	TCHAR nChar;

};
