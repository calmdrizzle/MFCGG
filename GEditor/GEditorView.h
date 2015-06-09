
// GEditorView.h : CGEditorView Ŭ������ �������̽�
//

#pragma once


class CGEditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGEditorView();
	DECLARE_DYNCREATE(CGEditorView)

// Ư���Դϴ�.
public:
	CGEditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

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
	virtual ~CGEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GEditorView.cpp�� ����� ����
inline CGEditorDoc* CGEditorView::GetDocument() const
   { return reinterpret_cast<CGEditorDoc*>(m_pDocument); }
#endif

