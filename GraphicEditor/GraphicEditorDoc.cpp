
// GraphicEditorDoc.cpp : CGraphicEditorDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif

#include "GraphicEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphicEditorDoc

IMPLEMENT_DYNCREATE(CGraphicEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicEditorDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicEditorDoc 생성/소멸

CGraphicEditorDoc::CGraphicEditorDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGraphicEditorDoc::~CGraphicEditorDoc()
{
}

BOOL CGraphicEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	Object* obj;
	POSITION pos = m_DrawObjs.GetHeadPosition();
	while (pos != NULL) {
		obj = (Object*)m_DrawObjs.GetNext(pos);
		delete obj;
	}
	m_DrawObjs.RemoveAll();

	return TRUE;
}




// CGraphicEditorDoc serialization

void CGraphicEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {		//저장
		POSITION pos = m_DrawObjs.GetHeadPosition();
		while (pos != NULL) {
			((Object*)m_DrawObjs.GetNext(pos))->serialize(ar);
		}

	} else {	//로드
		int toolType;
		Object *obj;

		do {
			ar >> toolType;

			switch (toolType) {
			case LINE:
				obj = new Line(); break;
			case ELLIPSE:
				obj = new GEllipse(); break;
			case RECTANGLE:
				obj = new GRectangle(); break;
			}

			obj->deserialize(ar);
			m_DrawObjs.AddTail(obj);

		} while (!ar.IsBufferEmpty());

		((CFrameWnd*)AfxGetMainWnd())->GetActiveView()->Invalidate(TRUE);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGraphicEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGraphicEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGraphicEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphicEditorDoc 진단

#ifdef _DEBUG
void CGraphicEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicEditorDoc 명령

Line* CGraphicEditorDoc::GetLine(BOOL bIsNew)
{
	if (bIsNew == TRUE)
	{
		m_CurrObject = new Line(); //새로운 Line 객체 생성
		//m_ObjectList.AddTail(m_sCurrObject); //리스트에 추가

		return (Line*)m_CurrObject;
	}
	else if (m_CurrObject != NULL && m_CurrType == LINE) //현재 타입이 라인이고, NULL이 아닐 때
		return (Line*)m_CurrObject;

	return NULL; //잘못된 사용 시에는 NULL을 반환
}

PolyLine* CGraphicEditorDoc::GetPolyLine(BOOL bIsNew)
{
	if (bIsNew == TRUE)
	{
		m_CurrObject = new PolyLine(); //새로운 GPolyline 객체 생성
		//m_sGObjectList.AddTail(m_sCurrObject); //리스트에 추가

		return (PolyLine*)m_CurrObject;
	}
	else if (m_CurrObject != NULL && m_CurrType == POLYLINE) //현재 타입이 폴리라인이고, NULL이 아닐 때
		return (PolyLine*)m_CurrObject;

	return NULL; //잘못된 사용 시에는 NULL을 반환하도록 함
}

GRectangle* CGraphicEditorDoc::GetGRectangle(BOOL blsNew)
{
	if (blsNew) {
		m_CurrObject = new GRectangle();
		//m_DrawObjs.AddTail(m_Cur);

		return (GRectangle*)m_CurrObject;
	}
	if (m_CurrObject != NULL && m_CurrType == RECTANGLE) {
		return (GRectangle*)m_CurrObject;
	}
	return NULL;
}