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
	ON_COMMAND(ID_SELECT, &CGraphicEditorDoc::OnSelect)
	ON_COMMAND(ID_POLYLINE, &CGraphicEditorDoc::OnPolyline)
	ON_COMMAND(ID_LINE, &CGraphicEditorDoc::OnLine)
	ON_COMMAND(ID_COLOR_BLUE, &CGraphicEditorDoc::OnColorBlue)
	ON_COMMAND(ID_THICKNESS_10, &CGraphicEditorDoc::OnThickness10)
	ON_COMMAND(ID_COLOR_GREEN, &CGraphicEditorDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CGraphicEditorDoc::OnColorRed)
	ON_COMMAND(ID_THICKNESS_1, &CGraphicEditorDoc::OnThickness1)
	ON_COMMAND(ID_THICKNESS_5, &CGraphicEditorDoc::OnThickness5)

	ON_COMMAND(ID_LINEPATTERN1, &CGraphicEditorDoc::OnLinepattern1)
	ON_COMMAND(ID_LINEPATTERN2, &CGraphicEditorDoc::OnLinepattern2)
	ON_COMMAND(ID_LINEPATTERN3, &CGraphicEditorDoc::OnLinepattern3)
	ON_COMMAND(ID_RECTANGLE, &CGraphicEditorDoc::OnRectangle)
	ON_COMMAND(ID_INCOLOR_RED, &CGraphicEditorDoc::OnIncolorRed)
	ON_COMMAND(ID_INCOLOR_GREEN, &CGraphicEditorDoc::OnIncolorGreen)
	ON_COMMAND(ID_INCOLOR_BLUE, &CGraphicEditorDoc::OnIncolorBlue)
	ON_COMMAND(ID_ELLIPSE, &CGraphicEditorDoc::OnEllipse)
	ON_COMMAND(ID_TEXT, &CGraphicEditorDoc::OnText)
	ON_COMMAND(ID_INPATTERN1, &CGraphicEditorDoc::OnInpattern1)
	ON_COMMAND(ID_INPATTERN2, &CGraphicEditorDoc::OnInpattern2)
	ON_COMMAND(ID_INPATTERN3, &CGraphicEditorDoc::OnInpattern3)
	/*ON_COMMAND(ID_FCOLOR_RED, &CGraphicEditorDoc::OnFcolorRed)
	ON_COMMAND(ID_FCOLOR_GREEN, &CGraphicEditorDoc::OnFcolorGreen)
	ON_COMMAND(ID_FCOLOR_BLUE, &CGraphicEditorDoc::OnFcolorBlue)
	ON_COMMAND(ID_FONT1, &CGraphicEditorDoc::OnFont1)
	ON_COMMAND(ID_FONT2, &CGraphicEditorDoc::OnFont2)
	ON_COMMAND(ID_FONT3, &CGraphicEditorDoc::OnFont3)
	ON_COMMAND(ID_FONTSIZE30, &CGraphicEditorDoc::OnFontsize30)
	ON_COMMAND(ID_FONTSIZE50, &CGraphicEditorDoc::OnFontsize50)
	ON_COMMAND(ID_FONTSIZE100, &CGraphicEditorDoc::OnFontsize100)
	ON_COMMAND(ID_ITALIC, &CGraphicEditorDoc::OnItalic)
	ON_COMMAND(ID_UNDERLINE, &CGraphicEditorDoc::OnUnderline)*/
	ON_COMMAND(ID_COLOR_BLACK, &CGraphicEditorDoc::OnColorBlack)
	ON_COMMAND(ID_INCOLOR_BLACK, &CGraphicEditorDoc::OnIncolorBlack)
END_MESSAGE_MAP()


// CGraphicEditorDoc ����/�Ҹ�

CGraphicEditorDoc::CGraphicEditorDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	cur_gobj = NULL;

	cur_type = LINE;
	cur_linepattern = PS_SOLID;
	cur_color = RGB(255, 0, 0);
	cur_thickness = 1;

	cur_fullcolor = RGB(255, 0, 0);
	cur_fullpattern = 6;

	bItalic = false;
	bUnderline = false;
	size = 30;
	fontName = "����";
	text_color = RGB(0, 0, 0);

}

CGraphicEditorDoc::~CGraphicEditorDoc()
{
}

BOOL CGraphicEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	cur_gobj = NULL;

	cur_type = LINE;
	cur_linepattern = PS_SOLID;
	cur_color = RGB(255, 0, 0);
	cur_thickness = 1;

	cur_fullcolor = RGB(255, 0, 0);
	cur_fullpattern = 6;

	bItalic = false;
	bUnderline = false;
	size = 30;
	fontName = "����";
	text_color = RGB(0, 0, 0);

	gobj_list.RemoveAll();
	gobj_selected_list.RemoveAll();
	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CGraphicEditorDoc serialization

void CGraphicEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int t = cur_type;
		//object_list.Serialize(ar);
		ar << t << point << cur_color << cur_fullcolor << cur_thickness << cur_linepattern << cur_fullpattern << gobj_context_menu_enabled << bItalic << bUnderline << size << fontName << text_color;
		POSITION pos = gobj_list.GetHeadPosition();
		ar << gobj_list.GetCount();
		while (pos){
			Object* temp = (Object*)gobj_list.GetNext(pos);
			temp->serialize(ar, true);
		}
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
	 // TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	 int t; int count;
	 //object_list.Serialize(ar);
	 ar >> t >> point >> cur_color >> cur_fullcolor >> cur_thickness >> cur_linepattern >> cur_fullpattern >> gobj_context_menu_enabled >> bItalic >> bUnderline >> size >> fontName >> text_color;
	 cur_type=(GObj_Type)t;
	 POSITION pos = gobj_list.GetHeadPosition();
	 ar>>count;
	 for (int i = 0; i < count; i++){
	 ar >> t;
	 switch (t){
	 case TEXT:{
	 Text* temp = new Text();
	 gobj_list.AddTail((void*)temp);
	 temp->serialize(ar, false);
	 cur_gobj = temp;
	 break; }
	 case ELLIPSE:{
	 GEllipse* temp = new GEllipse();
	 gobj_list.AddTail((void*)temp);
	 temp->serialize(ar, false);
	 cur_gobj = temp;
	 break; }
	 case RECTANGLE:{
		 GRectangle* temp = new GRectangle();
	 gobj_list.AddTail((void*)temp);
	 temp->serialize(ar, false);
	 cur_gobj = temp;
	 break; }
	 case LINE:{
	 Line* temp = new Line();
	 gobj_list.AddTail((void*)temp);
	 temp->serialize(ar, false);
	 cur_gobj = temp;
	 break; }
	 case POLYLINE:{
	 GPLine* temp = new GPLine();
	 gobj_list.AddTail((void*)temp);
	 temp->serialize(ar, false);
	 cur_gobj = temp;
	 break; }
	 }
	 }
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

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
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
void CGraphicEditorDoc::OnSelect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_type = SELECT;
}


void CGraphicEditorDoc::OnPolyline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_type = POLYLINE;

	POSITION pos = gobj_selected_list.GetHeadPosition();

	while (pos != NULL)
	{
		Object* g = (Object*)gobj_selected_list.GetNext(pos);
		g->resetSelected();
	}
	gobj_selected_list.RemoveAll();

	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	p->Invalidate();
}


void CGraphicEditorDoc::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_type = LINE;

	POSITION pos = gobj_selected_list.GetHeadPosition();

	while (pos != NULL)
	{
		Object* g = (Object*)gobj_selected_list.GetNext(pos);
		g->resetSelected();
	}

	gobj_selected_list.RemoveAll();

	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	p->Invalidate();
}


void CGraphicEditorDoc::OnColorBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_color = RGB(0, 0, 255);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setColor(cur_color);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}

void CGraphicEditorDoc::OnColorGreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_color = RGB(0, 255, 0);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setColor(cur_color);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnColorRed()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_color = RGB(255, 0, 0);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setColor(cur_color);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnThickness1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_thickness = 1;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setThickness(cur_thickness);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}

}

void CGraphicEditorDoc::OnThickness5()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_thickness = 5;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setThickness(cur_thickness);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}

void CGraphicEditorDoc::OnThickness10()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_thickness = 10;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setThickness(cur_thickness);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnLinepattern1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_linepattern = PS_SOLID;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setLinePattern(cur_linepattern);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnLinepattern2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_linepattern = PS_DASH;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setLinePattern(cur_linepattern);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnLinepattern3()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_linepattern = PS_DOT;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setLinePattern(cur_linepattern);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_type = RECTANGLE;

	POSITION pos = gobj_selected_list.GetHeadPosition();

	while (pos != NULL)
	{
		Object* g = (Object*)gobj_selected_list.GetNext(pos);
		g->resetSelected();
	}

	gobj_selected_list.RemoveAll();

	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	p->Invalidate();

}


void CGraphicEditorDoc::OnEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_type = ELLIPSE;

	POSITION pos = gobj_selected_list.GetHeadPosition();

	while (pos != NULL)
	{
		Object* g = (Object*)gobj_selected_list.GetNext(pos);
		g->resetSelected();
	}

	gobj_selected_list.RemoveAll();

	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	p->Invalidate();

}


void CGraphicEditorDoc::OnText()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_type = TEXT;

	POSITION pos = gobj_selected_list.GetHeadPosition();

	while (pos != NULL)
	{
		Object* g = (Object*)gobj_selected_list.GetNext(pos);
		g->resetSelected();
	}

	gobj_selected_list.RemoveAll();

	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	p->Invalidate();
}



void CGraphicEditorDoc::OnIncolorRed()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullcolor = RGB(255, 0, 0);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_color(cur_fullcolor);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_color(cur_fullcolor);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}

}


void CGraphicEditorDoc::OnIncolorGreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullcolor = RGB(0, 255, 0);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_color(cur_fullcolor);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_color(cur_fullcolor);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}

}


void CGraphicEditorDoc::OnIncolorBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullcolor = RGB(0, 0, 255);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_color(cur_fullcolor);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_color(cur_fullcolor);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}

void CGraphicEditorDoc::OnInpattern1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullpattern = 6;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_pattern(cur_fullpattern);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_pattern(cur_fullpattern);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnInpattern2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullpattern = HS_FDIAGONAL;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_pattern(cur_fullpattern);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_pattern(cur_fullpattern);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}

}


void CGraphicEditorDoc::OnInpattern3()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullpattern = HS_CROSS;

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_pattern(cur_fullpattern);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_pattern(cur_fullpattern);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}

/*
void CGraphicEditorDoc::OnFcolorRed()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
text_color = RGB(255, 0, 0);

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setColor(text_color);
}


}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGraphicEditorDoc::OnFcolorGreen()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
text_color = RGB(0, 255, 0);

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setColor(text_color);
}


}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnFcolorBlue()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
text_color = RGB(0, 0, 255);

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setColor(text_color);
}


}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnFont1()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
fontName = "�ü�";

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setFont(fontName);
}

}


CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnFont2()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
fontName = "����";

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setFont(fontName);
}

}


CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}

}


void CGEditorDoc::OnFont3()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
fontName = "����";

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setFont(fontName);
}

}


CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnFontsize30()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
size = 30;

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setSize(size);
}

}


CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnFontsize50()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
size = 50;

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setSize(size);
}

}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnFontsize100()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
size = 100;

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setSize(size);
}

}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}


void CGEditorDoc::OnItalic()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
bItalic = !bItalic;

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setItalic(bItalic);
}

}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}

void CGEditorDoc::OnUnderline()
{
// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
bUnderline = !bUnderline;

if (gobj_context_menu_enabled == true)
{
POSITION pos = gobj_selected_list.GetHeadPosition();

while (pos != NULL)
{
GObj* gobj = (GObj*)gobj_selected_list.GetNext(pos);

if (gobj->type() == TEXT)
{
GText* g = (GText*)gobj;
g->setUnderline(bUnderline);
}

}

CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
p->Invalidate();
}
}
*/

void CGraphicEditorDoc::OnColorBlack()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_color = RGB(0, 0, 0);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);
			gobj->setColor(cur_color);
		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}


void CGraphicEditorDoc::OnIncolorBlack()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	cur_fullcolor = RGB(0, 0, 0);

	if (gobj_context_menu_enabled == true)
	{
		POSITION pos = gobj_selected_list.GetHeadPosition();

		while (pos != NULL)
		{
			Object* gobj = (Object*)gobj_selected_list.GetNext(pos);

			if (gobj->type() == RECTANGLE)
			{
				GRectangle* g = (GRectangle*)gobj;
				g->setFull_color(cur_fullcolor);
			}
			else if (gobj->type() == ELLIPSE)
			{
				GEllipse *g = (GEllipse*)gobj;
				g->setFull_color(cur_fullcolor);
			}

		}

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		p->Invalidate();
	}
}
