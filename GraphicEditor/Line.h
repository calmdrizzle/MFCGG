#include "Object.h"
#pragma once

// Line ��� ����Դϴ�.

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
	CPoint m_start; //���� ��
	CPoint m_end; //����
	COLORREF m_color; //��
	int m_Thickness; // �β�


public:
	void Draw(CDC* cdc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setPoint(CPoint& start, CPoint& end);
	void setLine(int& lineWidth, COLORREF& color);

private:
	int m_PenStyle;						// �� ��Ÿ��
	CPoint m_pRgnPoint[4];					// ���ý� ������ �����ϴ� ����Ʈ�迭



};


