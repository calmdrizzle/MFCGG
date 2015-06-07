#pragma once

// GEllipse 명령 대상입니다.
#include "Object.h"
class GEllipse : public Object
{
protected:
	DECLARE_SERIAL(GEllipse);
public:
	GEllipse();
	virtual ~GEllipse();
	virtual void Serialize(CArchive& ar);	//직렬화

	CRect virtual getBoundary();				// 리전을 반환
	void virtual drawBoundary(CDC* cdc);
	bool virtual isin(CPoint p);									// 리전을 반환
	int GetPenStyle();										//펜 스타일 반환
	COLORREF GetFillColor(void);							//채우기색 반환
	void Move(int dX, int dY);								// 좌표 이동
	void SetPenStyle(int penStyle);							// 펜 스타일 설정
	void SetFillColor(COLORREF brushColor);
	void Draw(CDC* cdc);

private:
	int m_PenStyle;							// 펜 스타일
	COLORREF m_FillColor;					// 브러쉬 칼라
	int m_n_HatchStyle;	

};


