
// GEditorView.cpp : CGEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GEditor.h"
#endif

#include "GEditorDoc.h"
#include "GEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGEditorView

IMPLEMENT_DYNCREATE(CGEditorView, CView)

BEGIN_MESSAGE_MAP(CGEditorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGEditorView ����/�Ҹ�

CGEditorView::CGEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGEditorView::~CGEditorView()
{
}

BOOL CGEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGEditorView �׸���

void CGEditorView::OnDraw(CDC* /*pDC*/)
{
	CGEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CGEditorView �μ�

BOOL CGEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGEditorView ����

#ifdef _DEBUG
void CGEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGEditorDoc* CGEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGEditorDoc)));
	return (CGEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGEditorView �޽��� ó����
