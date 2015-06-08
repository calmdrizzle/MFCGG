
// GraphicEditorView.cpp : CGraphicEditorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CGraphicEditorView 생성/소멸

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_drawMode = 1;
	m_selected = FALSE;

}

CGraphicEditorView::~CGraphicEditorView()
{
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGraphicEditorView 그리기

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rec, rect;
	GetClientRect(rec);

	TRACE("OnDraw Rect(%d, %d, %d, %d)\n", rec.top, rec.left, rec.bottom, rec.right);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

}


// CGraphicEditorView 인쇄

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGraphicEditorView 진단

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG

void CGraphicEditorView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	BOOL bsEnable = GetDocument()->m_CurrentType == ELLIPSE;
	pCmdUI->SetCheck(bsEnable);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateLine(CCmdUI *pCmdUI)
{
	BOOL bsEnable = GetDocument()->m_CurrentType == LINE;
	pCmdUI->SetCheck(bsEnable);
	m_Draw = TRUE;
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	BOOL bsEnable = GetDocument()->m_CurrentType == RECTANGLE;
	pCmdUI->SetCheck(bsEnable);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

// CGraphicEditorView 메시지 처리기


void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	TRACE("OnButtonDown : %d [%d, %d]\n", nFlags, point.x, point.y);

	CMainFrame *ppMainFrame = (CMainFrame *)AfxGetMainWnd();
	CGraphicEditorDoc* psDoc = GetDocument(); //도큐먼트 받음

	m_Draw = TRUE; //그리기 시작

	m_ptStart = point;//마우스 포인터가 클릭하는 곳으로 그리기 시작

	switch (psDoc->m_CurrentType)
	{
	case SELECT:
		break;

	case LINE:
		psDoc->GetLine(TRUE)->SetStartPoint(point);//라인 새로 생성
		//psDoc->GetLine(TRUE);
		//m_ptStart = point;//마우스 포인터가 클릭하는 곳으로 그리기 시작
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	
	
	//TRACE("FOCUS: %d\n", m_bsMakeFocusRect);
	TRACE("OnButtonUp : %d\n", nFlags);
	CGraphicEditorDoc* psDoc = GetDocument(); //도큐먼트 얻어오기
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	str.Format(_T("마우스 좌표 (%4d, %4d)"), point.x, point.y);
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//pMainFrame->m_wndStatusBar.SetPaneText(2, str);
		CGraphicEditorDoc* psDoc = GetDocument(); //도큐먼트 얻어오기
		CClientDC dc(this);
		//이동 시 delta x,y 구하기
		int dx = point.x - psDoc->m_ClickedPoint.x,
			dy = point.y - psDoc->m_ClickedPoint.y;
		psDoc->m_ClickedPoint = point; //클릭지점은 현재 포인트로
		int oldMode;
	//int radius;

	if (m_Draw == TRUE)
	{

		switch (psDoc->m_CurrentType)
		{
		case LINE:
			//psDoc->GetLine()->SetEndPoint(point); //이동 중에 계속 종료점을 재지정
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
