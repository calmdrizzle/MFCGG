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
	~Line();
	
	int GetPenStyle() const { return m_PenStyle; }
	int GetStartCap(void) const { return m_StartCap; } //라인 시작 모양 반환
	int GetEndCap(void) const { return m_EndCap; } //라인 끝 모양 반환

public:
	void SetPenStyle(int penStyle);			// 펜 스타일 설정
	void SetStartCap(int startCap);								//선 시작 모양 설정
	void SetEndCap(int endCap);
	//virtual void Serialize(CArchive& ar);
	void Draw(CDC* cdc);


private:
	int m_PenStyle;						// 펜 스타일
	CPoint m_pRgnPoint[4];					// 선택시 리전을 구성하는 포인트배열

	int m_StartCap;	//라인 시작 모양
	int m_EndCap;		//라인  끝모양

};


