#pragma once

// GEllipse ��� ����Դϴ�.
#include "Object.h"
class GEllipse : public Object
{
protected:
	DECLARE_SERIAL(GEllipse);
public:
	GEllipse();
	virtual ~GEllipse();
	virtual void Serialize(CArchive& ar);	//����ȭ

	CRect virtual getBoundary();				// ������ ��ȯ
	void virtual drawBoundary(CDC* cdc);
	bool virtual isin(CPoint p);									// ������ ��ȯ
	int GetPenStyle();										//�� ��Ÿ�� ��ȯ
	COLORREF GetFillColor(void);							//ä���� ��ȯ
	void Move(int dX, int dY);								// ��ǥ �̵�
	void SetPenStyle(int penStyle);							// �� ��Ÿ�� ����
	void SetFillColor(COLORREF brushColor);
	void Draw(CDC* cdc);

private:
	int m_PenStyle;							// �� ��Ÿ��
	COLORREF m_FillColor;					// �귯�� Į��
	int m_n_HatchStyle;	

};


