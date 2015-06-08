
// GraphicEditorView.h : CGraphicEditorView 클래스의 인터페이스
//

#pragma once


class CGraphicEditorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

// 특성입니다.
public:
	CGraphicEditorDoc* GetDocument() const;
	int m_drawMode;
	BOOL m_selected;
	CPoint m_ptEnd;				//끝나는 점
	CPoint m_ptStart, m_ptPrev; //시작점과 움직일때 보여주는 점
	COLORREF m_FillColor;
	COLORREF m_FigureLineColor;
	COLORREF m_color;		//선 색
	int m_FigureThickness;
	int m_LineThickness;	//선 두께
	int m_LinepatternIndex;
	int m_FlagNewLine;
	BOOL m_Draw;	//그리기 모드인지 TRUE와 FALSE로 구분

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnLine();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GraphicEditorView.cpp의 디버그 버전
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

