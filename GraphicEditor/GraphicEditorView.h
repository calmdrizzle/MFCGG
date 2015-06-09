
// GraphicEditorView.h : CGraphicEditorView Ŭ������ �������̽�
//

#pragma once


class CGraphicEditorView : public CView
{
	DECLARE_DYNCREATE(CGraphicEditorView)
	//ȭ�� ������ ����
private:
	CDC* _memDc;
	CBitmap *_bitmap, *_oldBitmap;
	CRect _rect;
	CPoint _anchor, _drawTo, _oldPoint;
protected: // serialization������ ��������ϴ�.
	CGraphicEditorView();
	

// Ư���Դϴ�.
public:
	CGraphicEditorDoc* GetDocument() const;
	int m_drawMode;
	BOOL m_selected;
	CPoint m_ptEnd;				//������ ��
	CPoint m_ptStart, m_ptPrev; //�������� �����϶� �����ִ� ��
	COLORREF m_FillColor;
	COLORREF m_FigureLineColor;
	COLORREF m_color;		//�� ��
	int m_FigureThickness;
	int m_LineThickness=1;	//�� �β�
	int m_LinepatternIndex;
	int m_FlagNewLine;
	BOOL m_Draw;	//�׸��� ������� TRUE�� FALSE�� ����

	BOOL m_DrawPoly;	//�������� �׸��� ����
	BOOL m_DBClick; //���� Ŭ�� ����
	CPoint m_CurrPoint;//�������� �׸� �� ���� ���콺 ����
	

// �۾��Դϴ�.
public:
	BOOL m_bsMakeFocusRect;		//�巡�� ����
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdatePolyline(CCmdUI *pCmdUI);
	afx_msg void OnPolyline();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRed();
	afx_msg void OnBlue();
	afx_msg void OnGreen();
	afx_msg void OnBlack();
	afx_msg void Onwhite();
	afx_msg void OnOne();
	afx_msg void OnFive();
	afx_msg void OnTen();
};

#ifndef _DEBUG  // GraphicEditorView.cpp�� ����� ����
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

