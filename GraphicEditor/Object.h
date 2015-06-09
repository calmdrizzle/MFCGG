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

typedef enum figuretype_
{ 
	BORDERONLY,
	BORDERFILL,
	NOBORDERFILL
} FIGURETYPE;

class Object : public CObject
{
public:
	Object();
	virtual ~Object();
	static COLORREF FgColor;
	static COLORREF BgColor;
	static int LineWidth;
	static FIGURETYPE FigureType;
	static int FontSize;
	static CString FontName;
	static int FontMode;
	CPoint m_StartPoint;

	virtual void draw(CDC* pDc) = 0;
	virtual int drawType(void) = 0;
	virtual void serialize(CArchive& ar) = 0;
	virtual void deserialize(CArchive& ar) = 0;
	CPoint GetStartPoint(void) const { return m_StartPoint; }	//시작점 반환
	void SetStartPoint(CPoint pt);
	
};


