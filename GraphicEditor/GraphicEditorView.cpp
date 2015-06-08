
// GraphicEditorView.cpp : CGraphicEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#include "MainFrm.h" 
#include "Object.h"

#endif

#include "GraphicEditorDoc.h"
#include "GraphicEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CGraphicEditorView::OnUpdateLine)
	ON_COMMAND(ID_LINE, &CGraphicEditorView::OnLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CGraphicEditorView::OnUpdateEllipse)
	ON_COMMAND(ID_ELLIPSE, &CGraphicEditorView::OnEllipse)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CGraphicEditorView::OnUpdateRectangle)
	ON_COMMAND(ID_RECTANGLE, &CGraphicEditorView::OnRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_drawMode = 1;
	m_selected = FALSE;

}

CGraphicEditorView::~CGraphicEditorView()
{
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGraphicEditorView �׸���

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rec, rect;
	GetClientRect(rec);

	TRACE("OnDraw Rect(%d, %d, %d, %d)\n", rec.top, rec.left, rec.bottom, rec.right);
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

}


// CGraphicEditorView �μ�

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGraphicEditorView ����

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG

void CGraphicEditorView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	BOOL bsEnable = GetDocument()->m_CurrentType == ELLIPSE;
	pCmdUI->SetCheck(bsEnable);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateLine(CCmdUI *pCmdUI)
{
	BOOL bsEnable = GetDocument()->m_CurrentType == LINE;
	pCmdUI->SetCheck(bsEnable);
	m_Draw = TRUE;
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	BOOL bsEnable = GetDocument()->m_CurrentType == RECTANGLE;
	pCmdUI->SetCheck(bsEnable);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

// CGraphicEditorView �޽��� ó����


void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	TRACE("OnButtonDown : %d [%d, %d]\n", nFlags, point.x, point.y);

	CMainFrame *ppMainFrame = (CMainFrame *)AfxGetMainWnd();
	CGraphicEditorDoc* psDoc = GetDocument(); //��ť��Ʈ ����

	m_Draw = TRUE; //�׸��� ����

	m_ptStart = point;//���콺 �����Ͱ� Ŭ���ϴ� ������ �׸��� ����

	switch (psDoc->m_CurrentType)
	{
	case SELECT:
		break;

	case LINE:
		psDoc->GetLine(TRUE)->SetStartPoint(point);//���� ���� ����
		//psDoc->GetLine(TRUE);
		//m_ptStart = point;//���콺 �����Ͱ� Ŭ���ϴ� ������ �׸��� ����
		//psDoc->GetLine()->setLine(ToolValues::LineWidth, ToolValues::FgColor);
		break;

	case ELLIPSE:
		break;
	
	case RECTANGLE:
		psDoc->GetGRectangle(TRUE);
		psDoc->GetGRectangle()->setProps(Object::LineWidth, Object::FgColor, Object::BgColor);
		break;
	}

	_anchor = _drawTo = _oldPoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void CGraphicEditorView::OnLine()
{
	//GetDocument()->m_CurrentType = LINE;
	CGraphicEditorDoc* psDoc = GetDocument();
	psDoc->m_CurrentType = LINE;
	m_drawMode = 1;
	m_selected = FALSE;
	m_Draw = TRUE;
	if (!m_selected){
		CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
		//doc->m_sSelectedList.RemoveAll();
	}
}

void CGraphicEditorView::OnEllipse()
{
	GetDocument()->m_CurrentType = ELLIPSE;
	m_drawMode = 1;
	m_selected = FALSE;
	if (!m_selected){
		CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
		//doc->m_sSelectedList.RemoveAll();
	}
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnRectangle()
{
	GetDocument()->m_CurrentType = RECTANGLE;
	m_drawMode = 1;
	m_selected = FALSE;
	if (!m_selected){
		CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
		//doc->m_sSelectedList.RemoveAll();
	}
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	
	
	//TRACE("FOCUS: %d\n", m_bsMakeFocusRect);
	TRACE("OnButtonUp : %d\n", nFlags);
	CGraphicEditorDoc* psDoc = GetDocument(); //��ť��Ʈ ������
	if (m_Draw == TRUE)
	{
		//CRect selectRect = MakeSelectRect();
		switch (psDoc->m_CurrentType)
		{
		case LINE:
			//psDoc->GetLine()->setPoint(_anchor, point);
			m_ptEnd = point;
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
			break;
		case RECTANGLE:
			
			psDoc->GetGRectangle()->setRect(_anchor, point);
			break;
		}
		//Invalidate(FALSE);
	}
	CView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString str;
	str.Format(_T("���콺 ��ǥ (%4d, %4d)"), point.x, point.y);
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//pMainFrame->m_wndStatusBar.SetPaneText(2, str);
		CGraphicEditorDoc* psDoc = GetDocument(); //��ť��Ʈ ������
		CClientDC dc(this);
		//�̵� �� delta x,y ���ϱ�
		int dx = point.x - psDoc->m_ClickedPoint.x,
			dy = point.y - psDoc->m_ClickedPoint.y;
		psDoc->m_ClickedPoint = point; //Ŭ�������� ���� ����Ʈ��
		int oldMode;
	//int radius;

	if (m_Draw == TRUE)
	{

		switch (psDoc->m_CurrentType)
		{
		case LINE:
			//psDoc->GetLine()->SetEndPoint(point); //�̵� �߿� ��� �������� ������
			oldMode = dc.SetROP2(R2_NOT);

			dc.MoveTo(_anchor);
			dc.LineTo(_oldPoint);

			dc.MoveTo(_anchor);
			dc.LineTo(_oldPoint);
			//_oldPoint = point;
			dc.SetROP2(oldMode);
			break;
		case RECTANGLE:
			oldMode = dc.SetROP2(R2_NOT);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(_oldPoint.x, _oldPoint.y, _anchor.x, _anchor.y);
			dc.Rectangle(_anchor.x, _anchor.y, point.x, point.y);
			_oldPoint = point;
			dc.SetROP2(oldMode);
			break;
		}
		//Invalidate();
	}
	
	CView::OnMouseMove(nFlags, point);
}
