
// GraphicEditorDoc.cpp : CGraphicEditorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CGraphicEditorDoc ����/�Ҹ�

CGraphicEditorDoc::CGraphicEditorDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CGraphicEditorDoc::~CGraphicEditorDoc()
{
}

BOOL CGraphicEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
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
	if (ar.IsStoring()) {		//����
		POSITION pos = m_DrawObjs.GetHeadPosition();
		while (pos != NULL) {
			((Object*)m_DrawObjs.GetNext(pos))->serialize(ar);
		}

	} else {	//�ε�
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

// ����� �׸��� �����մϴ�.
void CGraphicEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CGraphicEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CGraphicEditorDoc ����

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


// CGraphicEditorDoc ���

Line* CGraphicEditorDoc::GetLine(BOOL bIsNew)
{
	if (bIsNew == TRUE)
	{
		m_CurrObject = new Line(); //���ο� Line ��ü ����
		//m_ObjectList.AddTail(m_sCurrObject); //����Ʈ�� �߰�

		return (Line*)m_CurrObject;
	}
	else if (m_CurrObject != NULL && m_CurrType == LINE) //���� Ÿ���� �����̰�, NULL�� �ƴ� ��
		return (Line*)m_CurrObject;

	return NULL; //�߸��� ��� �ÿ��� NULL�� ��ȯ
}

PolyLine* CGraphicEditorDoc::GetPolyLine(BOOL bIsNew)
{
	if (bIsNew == TRUE)
	{
		m_CurrObject = new PolyLine(); //���ο� GPolyline ��ü ����
		//m_sGObjectList.AddTail(m_sCurrObject); //����Ʈ�� �߰�

		return (PolyLine*)m_CurrObject;
	}
	else if (m_CurrObject != NULL && m_CurrType == POLYLINE) //���� Ÿ���� ���������̰�, NULL�� �ƴ� ��
		return (PolyLine*)m_CurrObject;

	return NULL; //�߸��� ��� �ÿ��� NULL�� ��ȯ�ϵ��� ��
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