#pragma once

// Object 명령 대상입니다.
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
	GraphicObjectType GetType(void) const { return m_Type; }	//그래피컬 개체의 타입을 반환
	int getMoveMode(){ return moveMode; }
	CPoint GetStartPoint(void) const { return m_StartPoint; }	//시작점 반환
	CPoint GetEndPoint(void) const { return m_EndPoint; }		//종료점 반환
	void setMoveMode(int n){ moveMode = n; }
	COLORREF GetFigureLineColor(void) const { return m_FigureLineColor; }

	COLORREF GetLineColor(void) const { return m_LineColor; }	//라인 색 반환
	int GetThickness(void) const { return m_Thickness; }		//라인 굵기 반환
	BOOL getSelectedObj() { return m_selectedObj; }
	virtual bool isin(CPoint p);
	virtual CRect getBoundary() { return 0; };
	virtual void drawBoundary(CDC*) {}
	BOOL IsGrouped(void) const { return m_Grouped; }			//그룹 여부 반환

	Point CPointToPoint(CPoint point);							//CPoint형을 GDI+에서 사용하는 Point형으로 변환

	void SetStartPoint(CPoint pt);								//시작점 변경
	void SetEndPoint(CPoint endPoint);							//끝점 변경

	void SetFigureLineColor(COLORREF color);


	void setFillColor(COLORREF color){ m_fillColor = color; }
	void SetLineColor(COLORREF color);							//라인 색 변경
	void SetThickness(int thickness);							//라인 굵기 변경
	void SetGrouped(BOOL isGrouped);							//그룹 여부 설정
	Color Object::COLORREFtoColor(COLORREF color);
	void SetDashStyle(Pen& pen, int nPenStyle);					//펜 설정
	void setSelectedObj(BOOL s) { m_selectedObj = s; }
	virtual void Draw(CDC* cdc) {}								//이 함수에서 그래피컬 개체 그림
	void setLinePattern(int pattern){ m_linePattern = pattern; }
	virtual void Move(int dX, int dY) {}						//좌표 이동
protected:
	GraphicObjectType m_Type;		//그래피컬 개체의 타입
	CPoint m_StartPoint;			//시작점(left,top의 좌표)	
	CPoint m_EndPoint;				//종료점(right,bottom의 좌표)
	COLORREF m_LineColor;			//선 색
	COLORREF m_fillColor;
	COLORREF m_FigureLineColor;		//도형 선 색

	int m_Thickness;				//선 굵기
	BOOL m_selectedObj;
	int moveMode;
	int m_linePattern;
	BOOL m_Grouped;					//그룹화 여부
};


