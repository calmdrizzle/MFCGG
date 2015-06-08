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
	~Line();
	
	int GetPenStyle() const { return m_PenStyle; }
	int GetStartCap(void) const { return m_StartCap; } //���� ���� ��� ��ȯ
	int GetEndCap(void) const { return m_EndCap; } //���� �� ��� ��ȯ

public:
	void SetPenStyle(int penStyle);			// �� ��Ÿ�� ����
	void SetStartCap(int startCap);								//�� ���� ��� ����
	void SetEndCap(int endCap);
	//virtual void Serialize(CArchive& ar);
	void Draw(CDC* cdc);


private:
	int m_PenStyle;						// �� ��Ÿ��
	CPoint m_pRgnPoint[4];					// ���ý� ������ �����ϴ� ����Ʈ�迭

	int m_StartCap;	//���� ���� ���
	int m_EndCap;		//����  �����

};


