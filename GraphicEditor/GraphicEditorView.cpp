
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
	//ON_UPDATE_COMMAND_UI(ID_LINE, &CGraphicEditorView::OnUpdateLine)
	//ON_COMMAND(ID_LINE, &CGraphicEditorView::OnLine)
	//ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CGraphicEditorView::OnUpdateEllipse)
	//ON_COMMAND(ID_ELLIPSE, &CGraphicEditorView::OnEllipse)
	//ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CGraphicEditorView::OnUpdateRectangle)
	//ON_COMMAND(ID_RECTANGLE, &CGraphicEditorView::OnRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//ON_UPDATE_COMMAND_UI(ID_POLYLINE, &CGraphicEditorView::OnUpdatePolyline)
	//ON_COMMAND(ID_POLYLINE, &CGraphicEditorView::OnPolyline)
	ON_WM_LBUTTONDBLCLK()
	/*ON_COMMAND(ID_RED, &CGraphicEditorView::OnRed)
	ON_COMMAND(ID_BLUE, &CGraphicEditorView::OnBlue)
	ON_COMMAND(ID_GREEN, &CGraphicEditorView::OnGreen)
	ON_COMMAND(ID_BLACK, &CGraphicEditorView::OnBlack)
	ON_COMMAND(ID_white, &CGraphicEditorView::Onwhite)
	ON_COMMAND(ID_ONE, &CGraphicEditorView::OnOne)
	ON_COMMAND(ID_FIVE, &CGraphicEditorView::OnFive)
	ON_COMMAND(ID_TEN, &CGraphicEditorView::OnTen)*/
//	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)

ON_COMMAND(ID_LINE, &CGraphicEditorView::OnLine)
ON_UPDATE_COMMAND_UI(ID_LINE, &CGraphicEditorView::OnUpdateLine)
END_MESSAGE_MAP()

// CGraphicEditorView 생성/소멸

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	_bDrawMode = FALSE;
	_bDoing = FALSE;
	_nZoomRate = 100;
	_memDc = NULL;
	_bitmap = NULL;
	_oldRadius = 0;

	_rect.left = _rect.top = 0;
	_rect.bottom = 600;
	_rect.right = 800;

}

CGraphicEditorView::~CGraphicEditorView()
{
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.x = _rect.top;
	cs.y = _rect.left;
	cs.cx = _rect.bottom;
	cs.cy = _rect.right;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

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


void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CGraphicEditorDoc* psDoc = GetDocument(); //도큐먼트 받음
	CClientDC dc(this);
	 //그리기 시작
	_bDrawMode = TRUE;
	
	//다각형 그리는 중..
	/*if (doc->CurDrawType == POLYGON && _bDoing) {
		CPen cpen(PS_SOLID, ToolValues::LineWidth, ToolValues::FgColor);
		CPen *oldPen = dc.SelectObject(&cpen);

		dc.MoveTo(_drawTo);
		dc.LineTo(point);
		_oldPoint = point;

		dc.SelectObject(oldPen);
		return;
	}*/

	//SetCapture();
	
	if (_bDrawMode == TRUE){
		
		switch (psDoc->m_CurrentType)
		{
		case SELECT:
			break;

		case LINE:
			psDoc->GetLine(TRUE);
			psDoc->GetLine()->setBeeLine(Object::LineWidth, Object::FgColor);
			break;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//도큐먼트 얻어오기
	//CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CGraphicEditorDoc* psDoc = GetDocument();
	CClientDC dc(this);
	
	int oldMode;
	int radius;
	
	if (_bDrawMode == TRUE)
	{

		switch (psDoc->m_CurrentType)
{
		case LINE:
			oldMode = dc.SetROP2(R2_NOT);

			dc.MoveTo(_anchor);
			dc.LineTo(_oldPoint);

			dc.MoveTo(_anchor);
			dc.LineTo(point);
			_oldPoint = point;

			dc.SetROP2(oldMode);
			break;

		
	}
		//Invalidate();
}

	CView::OnMouseMove(nFlags, point);
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	 //도큐먼트 얻어오기
	//CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//pMainFrame->m_wndStatusBar.SetPaneText(2, str);

	if (_bDrawMode) {
		_bDrawMode = FALSE;
		CGraphicEditorDoc* psDoc = GetDocument();
		ASSERT_VALID(psDoc);

		/*if (doc->CurDrawType == POLYGON) {
			CClientDC dc(this);

			CPen cpen(PS_SOLID, ToolValues::LineWidth, ToolValues::FgColor);
			CPen *oldPen = dc.SelectObject(&cpen);

			dc.MoveTo(_drawTo);
			dc.LineTo(point);

			dc.SelectObject(oldPen);

			doc->getPolygonDraw()->addPoint(point);

			_drawTo = point;
			_bDoing = TRUE;
			return;
		}*/
		::ReleaseCapture();
		//CRect selectRect = MakeSelectRect();
		switch (psDoc->m_CurrentType)
		{
		case LINE:
			psDoc->GetLine()->setPoint(_anchor, point);
			break;
		}
		Invalidate(FALSE);
	}
	CView::OnLButtonUp(nFlags, point);
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	TRACE("OnButtonDblClk : %d\n", nFlags);
	_bDrawMode = FALSE;
	CGraphicEditorDoc* psDoc = GetDocument();
	ASSERT_VALID(psDoc);

	/*
	if ((psDoc->CurDrawType == POLYLINE) && _bDoing) {
		psDoc->getPolygonDraw()->addPoint(point);

		_bDoing = FALSE;
		Invalidate(FALSE);
	}*/
	::ReleaseCapture();
	CView::OnLButtonDblClk(nFlags, point);


}
/*
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

void CGraphicEditorView::OnUpdatePolyline(CCmdUI *pCmdUI)
	{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	BOOL bsEnable = GetDocument()->m_CurrentType == POLYLINE;
	pCmdUI->SetCheck(bsEnable);
	
}



// CGraphicEditorView 메시지 처리기

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
	CGraphicEditorDoc* psDoc = GetDocument();
	psDoc->m_CurrentType = ELLIPSE;
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
	
void CGraphicEditorView::OnPolyline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* psDoc = GetDocument();
	psDoc->m_CurrentType = POLYLINE;
	m_drawMode = 1;
	m_selected = FALSE;
	m_Draw = TRUE;
	if (!m_selected){
		CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
		//doc->m_sSelectedList.RemoveAll();
	}
}
*/




/*
void CGraphicEditorView::OnRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_color = RGB(255, 0, 0);
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);    // 빨간색 펜 생성
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);        // 빨간색으로 선을 그림
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::OnBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_color = RGB(0, 0, 255);
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);    // 빨간색 펜 생성
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);        // 빨간색으로 선을 그림
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::OnGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_color = RGB(0, 255, 0);
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);    // 빨간색 펜 생성
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);        // 빨간색으로 선을 그림
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::OnBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_color = RGB(0, 0, 0);
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);    // 빨간색 펜 생성
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);        // 빨간색으로 선을 그림
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::Onwhite()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_color = RGB(255, 255, 255);
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);    // 빨간색 펜 생성
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);        // 빨간색으로 선을 그림
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::OnOne()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_LineThickness = 1;
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::OnFive()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_LineThickness = 5;
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);
	dc.SelectObject(oldPen);
}


void CGraphicEditorView::OnTen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	CPen pen;
	m_LineThickness = 10;
	pen.CreatePen(PS_SOLID, m_LineThickness, m_color);
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);
	dc.SelectObject(oldPen);
}
*/

void CGraphicEditorView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//GetDocument()->m_CurrentType = LINE;
	CGraphicEditorDoc* psDoc = GetDocument();
	psDoc->m_CurrentType = LINE;
	//m_drawMode = 1;
	m_selected = FALSE;
	_bDrawMode = TRUE;
	if (!m_selected){
		CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
		//doc->m_sSelectedList.RemoveAll();
	}
}


void CGraphicEditorView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	BOOL bsEnable = GetDocument()->m_CurrentType == LINE;
	pCmdUI->SetCheck(bsEnable);
	_bDrawMode = TRUE;
}
