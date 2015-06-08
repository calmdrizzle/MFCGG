#include "Object.h"
#pragma once

// Line 명령 대상입니다.

class Line : public Object
{
protected:
	DECLARE_SERIAL(Line);
public:
	Line();
	Line(const Line& pointL);
	virtual ~Line();
	
	int GetPenStyle() const { return m_PenStyle; }

public:
	CPoint m_start; //시작 점
	CPoint m_end; //끝점
	COLORREF m_color; //색
	int m_Thickness; // 두께


public:
	void Draw(CDC* cdc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setPoint(CPoint& start, CPoint& end);
	void setLine(int& lineWidth, COLORREF& color);

private:
	int m_PenStyle;						// 펜 스타일
	CPoint m_pRgnPoint[4];					// 선택시 리전을 구성하는 포인트배열



};


