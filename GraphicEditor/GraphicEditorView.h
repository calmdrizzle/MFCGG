
// GraphicEditorView.h : CGraphicEditorView 클래스의 인터페이스
//

#pragma once
#include "Object.h"
#include "Line.h"
#include "GPLine.h"
#include "GRectangle.h"
#include "GEllipse.h"
#include "Text.h"

class CGraphicEditorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

	// 특성입니다.
public:
	CGraphicEditorDoc* GetDocument() const;
	bool isdrawing;
	bool ismoving;
	bool isselect;

private:
	bool m_ctrl;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

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
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GraphicEditorView.cpp의 디버그 버전
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
{
	return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument);
}
#endif

