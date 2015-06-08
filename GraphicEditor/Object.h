#pragma once

// Object ��� ����Դϴ�.
enum GraphicObjectType
{
	SELECT,
	LINE,
	POLYLINE,
	ELLIPSE,
	RECTANGLE,
	TEXT,
	GGROUP
};

class Object : public CObject
{
public:
	Object();
	virtual ~Object();
	virtual void Serialize(CArchive& ar);

public:
	GraphicObjectType GetType(void) const { return m_Type; }	//�׷����� ��ü�� Ÿ���� ��ȯ
	int getMoveMode(){ return moveMode; }
	CPoint GetStartPoint(void) const { return m_StartPoint; }	//������ ��ȯ
	CPoint GetEndPoint(void) const { return m_EndPoint; }		//������ ��ȯ
	void setMoveMode(int n){ moveMode = n; }
	COLORREF GetFigureLineColor(void) const { return m_FigureLineColor; }

	COLORREF GetLineColor(void) const { return m_LineColor; }	//���� �� ��ȯ
	int GetThickness(void) const { return m_Thickness; }		//���� ���� ��ȯ
	BOOL getSelectedObj() { return m_selectedObj; }
	virtual bool isin(CPoint p);
	virtual CRect getBoundary() { return 0; };
	virtual void drawBoundary(CDC*) {}
	BOOL IsGrouped(void) const { return m_Grouped; }			//�׷� ���� ��ȯ

	Point CPointToPoint(CPoint point);							//CPoint���� GDI+���� ����ϴ� Point������ ��ȯ

	void SetStartPoint(CPoint pt);								//������ ����
	void SetEndPoint(CPoint endPoint);							//���� ����

	void SetFigureLineColor(COLORREF color);


	void setFillColor(COLORREF color){ m_fillColor = color; }
	void SetLineColor(COLORREF color);							//���� �� ����
	void SetThickness(int thickness);							//���� ���� ����
	void SetGrouped(BOOL isGrouped);							//�׷� ���� ����
	Color Object::COLORREFtoColor(COLORREF color);
	void SetDashStyle(Pen& pen, int nPenStyle);					//�� ����
	void setSelectedObj(BOOL s) { m_selectedObj = s; }
	virtual void Draw(CDC* cdc) {}								//�� �Լ����� �׷����� ��ü �׸�
	void setLinePattern(int pattern){ m_linePattern = pattern; }
	virtual void Move(int dX, int dY) {}						//��ǥ �̵�
protected:
	GraphicObjectType m_Type;		//�׷����� ��ü�� Ÿ��
	CPoint m_StartPoint;			//������(left,top�� ��ǥ)	
	CPoint m_EndPoint;				//������(right,bottom�� ��ǥ)
	COLORREF m_LineColor;			//�� ��
	COLORREF m_fillColor;
	COLORREF m_FigureLineColor;		//���� �� ��

	int m_Thickness;				//�� ����
	BOOL m_selectedObj;
	int moveMode;
	int m_linePattern;
	BOOL m_Grouped;					//�׷�ȭ ����
};


