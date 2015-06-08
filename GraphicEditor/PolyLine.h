#include "Object.h"
#pragma once

// PolyLine ��� ����Դϴ�.

class PolyLine : public Object
{
protected:
	DECLARE_SERIAL(PolyLine);
public:
	PolyLine();
	PolyLine(const PolyLine& pPoly);
	virtual ~PolyLine();

public:
	void AddOnePt(CPoint pt);									//���� �׸� �� �� �߰�
	void SetPolyStartPoint(CPoint pt);							//������ ����
	void SetPolyEndPoint(CPoint pt);							//���� ����

protected:
	CArray<CPoint, POINT> m_sArrayPoint;	//��ǥ ������
};


