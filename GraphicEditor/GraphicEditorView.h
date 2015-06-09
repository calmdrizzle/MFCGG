
// GraphicEditorView.h : CGraphicEditorView 클래스의 인터페이스
//

#pragma once


class CGraphicEditorView : public CView
{
	DECLARE_DYNCREATE(CGraphicEditorView)
	//화면 깜빡임 방지
private:
	CDC* _memDc;
	CBitmap *_bitmap, *_oldBitmap;
	CRect _rect;

	//현재 그려지는 GDIObject의 속성들
	CPen m_curPen;
	CPoint m_ptStart;
	BOOL _bDrawMode;
	CPoint _anchor, _drawTo, _oldPoint;
	BOOL _bDoing;
	BOOL m_selected;

	int _nZoomRate;
	int _oldRadius;		//원 그리기 이전 반지름

	int getOblique(CPoint& p1, CPoint& p2);
	void setStatusBar();

protected: // serialization에서만 만들어집니다.
	CGraphicEditorView();
	

// 특성입니다.
public:
	virtual void OnDraw(CDC* pDC);
	CGraphicEditorDoc* GetDocument() const;
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	//virtual void OnInitialUpdate();

	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();

	afx_msg void OnFileNew();
	afx_msg void OnPencil();
	afx_msg void OnUpdatePencil(CCmdUI* pCmdUI);
	afx_msg void OnFill();
	afx_msg void OnUpdateFill(CCmdUI* pCmdUI);
	afx_msg void OnBeeLine();
	afx_msg void OnUpdateBeeLine(CCmdUI* pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnPolygon();
	afx_msg void OnUpdatePolygon(CCmdUI* pCmdUI);
	afx_msg void OnFont();
	afx_msg void OnUpdateFont(CCmdUI* pCmdUI);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnViewZoomdefault();

	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI *pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // testView.cpp의 디버그 버전
inline YKPainterDoc* YKPainterDoc::GetDocument() const
{
	return reinterpret_cast<YKPainterDoc*>(m_pDocument);
}
#endif