#include "Object.h"
#pragma once

// PolyLine 명령 대상입니다.

class PolyLine : public Object
{
protected:
	DECLARE_SERIAL(PolyLine);
public:
	PolyLine();
	PolyLine(const PolyLine& pPoly);
	virtual ~PolyLine();

public:
	void AddOnePt(CPoint pt);									//점을 그릴 때 점 추가
	void SetPolyStartPoint(CPoint pt);							//시작점 변경
	void SetPolyEndPoint(CPoint pt);							//끝점 변경

protected:
	CArray<CPoint, POINT> m_sArrayPoint;	//좌표 시퀀스
};


