
// GraphicEditorView.cpp : CGraphicEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif

#include "GraphicEditorDoc.h"
#include "GraphicEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CView)
	//ON_WM_CONTEXTMENU()
	//ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	isdrawing = false;
	ismoving = false;
	isselect = false;

	m_ctrl = false;

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
	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();

	POSITION pos = doc->gobj_list.GetHeadPosition();

	while (pos != NULL)
	{
		Object* gobj = (Object*)doc->gobj_list.GetNext(pos);

		CPen pen(gobj->getLinePattern(), gobj->getThickness(), gobj->getColor());
		CPen *oldpen = pDC->SelectObject(&pen);

		gobj->draw(pDC);

		if (gobj->isSelected())
			gobj->drawBoundary(pDC);

		pDC->SelectObject(&oldpen);
	}
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CGraphicEditorView �޽��� ó����
void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();

	switch (doc->cur_type){
		/*case TEXT:
		{
		isdrawing = true;

		GText* g = new GText();
		g->set(point.x, point.y, point.x, point.y);
		g->setColor(doc->text_color);
		g->setFont(doc->fontName);
		g->setSize(doc->size);
		g->setItalic(doc->bItalic);
		g->setUnderline(doc->bUnderline);

		doc->cur_gobj = g;
		doc->gobj_list.AddTail((void*)g);
		break;
		}*/
	case ELLIPSE:
	{
		isdrawing = true;

		GEllipse* g = new GEllipse();
		g->set(point.x, point.y, point.x, point.y);
		g->setColor(doc->cur_color);
		g->setFull_color(doc->cur_fullcolor);
		g->setThickness(doc->cur_thickness);
		g->setLinePattern(doc->cur_linepattern);
		g->setFull_pattern(doc->cur_fullpattern);
		doc->cur_gobj = g;
		doc->gobj_list.AddTail((void*)g);
		break;
	}
	case RECTANGLE:
	{
		isdrawing = true;

		GRectangle* g = new GRectangle();
		g->set(point.x, point.y, point.x, point.y);
		g->setColor(doc->cur_color);
		g->setThickness(doc->cur_thickness);
		g->setLinePattern(doc->cur_linepattern);

		g->setFull_color(doc->cur_fullcolor);
		g->setFull_pattern(doc->cur_fullpattern);

		doc->cur_gobj = g;
		doc->gobj_list.AddTail((void*)g);
		break;
	}
	/*case LINE:
	{
	isdrawing = true;

	Line* g = new Line();
	g->set(point.x, point.y, point.x, point.y);
	g->setColor(doc->cur_color);
	g->setThickness(doc->cur_thickness);
	g->setLinePattern(doc->cur_linepattern);

	doc->cur_gobj = g;
	doc->gobj_list.AddTail((void*)g);

	break;
	}

	case POLYLINE:
	{
	isdrawing = true;

	GPLine* g;
	if (doc->cur_gobj != NULL)
	{
	g = (GPLine*)doc->cur_gobj;
	g->set(point.x, point.y, point.x, point.y);
	g->setArr();

	}

	else
	{
	g = new GPLine();
	g->set(point.x, point.y, point.x, point.y);
	g->setArr();
	g->setColor(doc->cur_color);
	g->setThickness(doc->cur_thickness);
	g->setLinePattern(doc->cur_linepattern);

	doc->cur_gobj = g;
	doc->gobj_list.AddTail((void*)g);
	}
	break;
	}
	*/
	case SELECT:
	{
		{
			POSITION pos = doc->gobj_list.GetTailPosition();

			bool found = false;
			Object* gobj = NULL;
			while (pos != NULL)
			{
				gobj = (Object*)doc->gobj_list.GetPrev(pos);
				if (gobj->isin(point))
				{
					found = true;
					doc->cur_gobj = gobj;

					// �� ���θ� CTRLŰ�� ����ä Ŭ������ ���
					if (m_ctrl)
					{
						// �̹� ���� ������ ���, ����Ʈ ����
						if (gobj->isSelected())
						{
							POSITION temp = doc->gobj_selected_list.Find(gobj);
							doc->gobj_selected_list.RemoveAt(temp);
						}

						// ��ü�� ������ �ȵ����� ��� �����ϰ� ����Ʈ�� �߰�
						else
							doc->gobj_selected_list.AddTail(gobj);

					}
					// �� ���θ� CTRLŰ�� �� ä Ŭ������ ���
					else if (!m_ctrl)
					{
						ismoving = true;
						isselect = true;
						// ������ up���� ó��
					}
					break;
				} // ���� ���� ��

			}
			// �ܺθ� �������� ���
			if (!found)
			{
				if (m_ctrl)
					;
				else if (!m_ctrl)
					doc->gobj_selected_list.RemoveAll();
			}

			// gobj_list ����, bool selected
			// ALL gobj->selected = false;
			// ButtonUP
		}

	}
	Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();

	if (isdrawing)
	{
		CClientDC dc(this);

		CPen pen(doc->cur_gobj->getLinePattern(), doc->cur_gobj->getThickness(), doc->cur_gobj->getColor());
		CPen *oldpen = dc.SelectObject(&pen);

		doc->cur_gobj->draw(&dc);

		dc.SelectObject(&oldpen);
	}

	if (doc->cur_type == POLYLINE)
		;
	else if (doc->cur_type == TEXT)
		isdrawing = false;

	else if (doc->cur_type == SELECT){

		if (!m_ctrl && doc->cur_gobj != NULL && isselect)
		{
			doc->gobj_selected_list.RemoveAll();
			doc->gobj_selected_list.AddTail(doc->cur_gobj);
			isselect = !isselect;
		}

		POSITION p = doc->gobj_list.GetHeadPosition();
		while (p != NULL)
		{
			Object* obj = (Object*)doc->gobj_list.GetNext(p);
			obj->resetSelected();
		}

		p = doc->gobj_selected_list.GetHeadPosition();
		while (p != NULL)
		{
			Object* obj = (Object*)doc->gobj_selected_list.GetNext(p);
			obj->setSelected();
		}

		ismoving = false;
		doc->cur_gobj = NULL;
	}

	else{
		isdrawing = false;
		doc->cur_gobj = NULL;
	}

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);

	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
	int dx = point.x - doc->point.x;
	int dy = point.y - doc->point.y;
	doc->point = point;

	isselect = false;
	Object* cur_gobj = NULL;
	if (isdrawing || ismoving)
	{
		if (isdrawing)
		{
			int oldrop2 = dc.GetROP2();
			dc.SetROP2(R2_XORPEN);


			cur_gobj = doc->cur_gobj;

			cur_gobj->draw(&dc);
			cur_gobj->set(point.x, point.y);

			cur_gobj->draw(&dc);

			dc.SetROP2(oldrop2);
		}

		else if (ismoving){
			POSITION pos = doc->gobj_selected_list.GetHeadPosition();

			while (pos != NULL)
			{
				int oldrop2 = dc.GetROP2();
				dc.SetROP2(R2_XORPEN);

				cur_gobj = (Object*)doc->gobj_selected_list.GetNext(pos);

				if (cur_gobj->type() == TEXT)
				{
					COLORREF temp = cur_gobj->getColor();
					cur_gobj->setColor(RGB(255, 255, 255));
					cur_gobj->draw(&dc);
					cur_gobj->move(dx, dy);
					cur_gobj->draw(&dc);
					Invalidate();

					cur_gobj->setColor(temp);

				}
				else{

					cur_gobj->draw(&dc);
					cur_gobj->move(dx, dy);
					cur_gobj->draw(&dc);
					dc.SetROP2(oldrop2);
				}
			}
		}
	}

	CView::OnMouseMove(nFlags, point);
}


/*void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();

isdrawing = false;
if (doc->cur_type == POLYLINE)
{
GPLine *g = (GPLine*)doc->cur_gobj;
g->complete();
}
doc->cur_gobj = NULL;

CView::OnLButtonDblClk(nFlags, point);
}*/


void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();

	if (nChar == VK_CONTROL)
	{
		m_ctrl = true;
	}

	else if (nChar == VK_DELETE)
	{
		/*if (doc->cur_type == SELECT)
		{
		POSITION pos = doc->gobj_selected_list.GetHeadPosition();

		Object* pobj = (Object*)doc->gobj_selected_list.GetHead();

		if (doc->gobj_selected_list.GetCount() == 1 && pobj->type() == POLYLINE && pobj->getmovemode() != -1)
		{
		GPLine* pline = (GPLine*)pobj;
		pline->onePointdel();
		}
		else{
		while (pos != NULL)
		{
		Object* obj = (Object*)doc->gobj_selected_list.GetNext(pos);

		POSITION p = doc->gobj_list.GetHeadPosition();
		while (p != NULL)
		{
		POSITION temp = p;
		Object* g = (Object*)doc->gobj_list.GetNext(p);

		if (obj == g){
		doc->gobj_list.RemoveAt(temp);
		delete g;
		}
		}
		}

		doc->gobj_selected_list.RemoveAll();
		}
		}*/
	}

	if (nChar == 'C'){
		doc->temp_list.RemoveAll();
		if (!doc->gobj_selected_list.IsEmpty()){
			POSITION pos = doc->gobj_selected_list.GetHeadPosition();
			while (pos){
				Object* temp = (Object*)(doc->gobj_selected_list.GetNext(pos));
				doc->temp_list.AddTail((void*)temp);
			}
		}
		else
			doc->temp_list.AddTail((void*)doc->cur_gobj);
		POSITION pos = doc->temp_list.GetHeadPosition();
		while (pos){
			Object* temp = (Object*)(doc->temp_list.GetNext(pos));

			switch (temp->type())
			{
			case RECTANGLE:
			{
				GRectangle* rec = (GRectangle*)temp;

				doc->gobj_selected_list.RemoveAll();
				GRectangle* g = new GRectangle();
				g->set(rec->getPoint().x, rec->getPoint().y, rec->getPoint_end().x, rec->getPoint_end().y);
				g->setColor(rec->getColor());
				g->setFull_color(rec->getFull_color());
				g->setThickness(rec->getThickness());
				g->setLinePattern(rec->getLinePattern());
				g->setFull_pattern(rec->getFull_pattern());
				g->move(50, 50);
				POSITION p = doc->temp_list.Find(temp);
				doc->temp_list.SetAt(p, (void*)g);
				break;
			}
			case ELLIPSE:
			{
				GEllipse* ell = (GEllipse*)temp;

				doc->gobj_selected_list.RemoveAll();
				GEllipse* g = new GEllipse();
				g->set(temp->getPoint().x, temp->getPoint().y, temp->getPoint_end().x, temp->getPoint_end().y);
				g->setColor(temp->getColor());
				g->setFull_color(ell->getFull_color());
				g->setThickness(temp->getThickness());
				g->setLinePattern(ell->getLinePattern());
				g->setFull_pattern(ell->getFull_pattern());
				g->move(50, 50);
				POSITION p = doc->temp_list.Find(temp);
				doc->temp_list.SetAt(p, (void*)g);
				break;
			}
			/*case TEXT:
			{
			GText* txt = (GText*)temp;

			doc->gobj_selected_list.RemoveAll();
			GText* g = new GText();
			g->set(temp->getPoint().x, temp->getPoint().y, temp->getPoint_end().x, temp->getPoint_end().y);
			g->setColor(temp->getColor());
			g->setFont(txt->getFontName());
			g->setSize(txt->getSize());
			g->setItalic(txt->getItalic());
			g->setUnderline(txt->getUnderline());
			g->move(50, 50);
			POSITION p = doc->temp_list.Find(temp);
			doc->temp_list.SetAt(p, (void*)g);
			break;
			}*/
			}
		}
	}
	if (nChar == 'V'){
		POSITION pos = doc->temp_list.GetHeadPosition();
		while (pos){
			Object* temp = (Object*)(doc->temp_list.GetNext(pos));
			doc->gobj_list.AddTail((void*)temp);
			//POSITION p = doc->temp_list.Find(temp);
			//doc->temp_list.SetAt(p,(void*)temp);
		}
		doc->temp_list.RemoveAll();
		Invalidate();
	}

	if (nChar == 'X'){
		doc->temp_list.RemoveAll();
		if (!doc->gobj_selected_list.IsEmpty()){
			POSITION pos = doc->gobj_selected_list.GetHeadPosition();
			while (pos){
				Object* temp = (Object*)(doc->gobj_selected_list.GetNext(pos));
				doc->temp_list.AddTail((void*)temp);
			}
		}
		else
			doc->temp_list.AddTail((void*)doc->cur_gobj);

		POSITION pos = doc->temp_list.GetHeadPosition();
		while (pos){
			Object* temp = (Object*)(doc->temp_list.GetNext(pos));

			switch (temp->type())
			{
			case RECTANGLE:
			{

				GRectangle* rec = (GRectangle*)temp;
				doc->gobj_selected_list.RemoveAll();
				GRectangle* g = new GRectangle();
				g->set(temp->getPoint().x, temp->getPoint().y, temp->getPoint_end().x, temp->getPoint_end().y);
				g->setColor(temp->getColor());
				g->setFull_color(rec->getFull_color());
				g->setThickness(temp->getThickness());
				g->setLinePattern(rec->getLinePattern());
				g->setFull_pattern(rec->getFull_pattern());
				g->move(50, 50);
				POSITION p = doc->temp_list.Find(temp);
				doc->temp_list.SetAt(p, (void*)g);
				p = doc->gobj_list.Find(temp);
				delete(temp);
				doc->gobj_list.RemoveAt(p);
				doc->cur_gobj = NULL;
				break;
			}
			case ELLIPSE:
			{
				GEllipse* ell = (GEllipse*)temp;

				doc->gobj_selected_list.RemoveAll();
				GEllipse* g = new GEllipse();
				g->set(temp->getPoint().x, temp->getPoint().y, temp->getPoint_end().x, temp->getPoint_end().y);
				g->setColor(temp->getColor());
				g->setFull_color(ell->getFull_color());
				g->setThickness(temp->getThickness());
				g->setLinePattern(ell->getLinePattern());
				g->setFull_pattern(ell->getFull_pattern());
				g->move(50, 50);
				POSITION p = doc->temp_list.Find(temp);
				doc->temp_list.SetAt(p, (void*)g);
				p = doc->gobj_list.Find(temp);
				delete(temp);
				doc->gobj_list.RemoveAt(p);
				doc->cur_gobj = NULL;
				break;
			}
			/*case TEXT:
			{
			GText* txt = (GText*)temp;

			doc->gobj_selected_list.RemoveAll();
			GText* g = new GText();
			g->set(temp->getPoint().x, temp->getPoint().y, temp->getPoint_end().x, temp->getPoint_end().y);
			g->setColor(temp->getColor());
			g->setFont(txt->getFontName());
			g->setSize(txt->getSize());
			g->setItalic(txt->getItalic());
			g->setUnderline(txt->getUnderline());
			g->move(50, 50);
			POSITION p = doc->temp_list.Find(temp);
			doc->temp_list.SetAt(p, (void*)g);
			p = doc->gobj_list.Find(temp);
			delete(temp);
			doc->gobj_list.RemoveAt(p);
			doc->cur_gobj = NULL;
			break;
			}*/
			}
		}
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGraphicEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_ctrl = false;

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();
	CClientDC dc(this);

	bool found = false;
	if (doc->gobj_selected_list.GetCount() == 1){
		Object* obj = (Object*)doc->gobj_selected_list.GetHead();

		if (obj->type() == TEXT){
			doc->cur_gobj = obj;
			found = true;
		}
	}

	/*if (doc->cur_type == TEXT || found){
	GText *g = (GText*)doc->cur_gobj;
	g->setChar(nChar);
	g->draw(&dc);
	Invalidate();
	g->setChar(NULL);
	}*/

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* doc = (CGraphicEditorDoc*)GetDocument();

	switch (doc->cur_type)
	{
	case SELECT:
	{
		POSITION pos = doc->gobj_list.GetTailPosition();
		bool found = false;

		Object* gobj = NULL;

		while (pos != NULL)
		{
			gobj = (Object*)doc->gobj_list.GetPrev(pos);
			if (gobj->isin(point))
			{
				found = true;
				break;
			}
		}

		if (found) {
			doc->cur_gobj = gobj;
			doc->gobj_context_menu_enabled = true;

			CMenu menu;
			menu.LoadMenu(IDR_MAINFRAME);
			CMenu* pMenu = menu.GetSubMenu(4);

			POINT screen_coord_pt = point;
			ClientToScreen(&screen_coord_pt);

			pMenu->TrackPopupMenu(
				TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				screen_coord_pt.x, screen_coord_pt.y, this);

			break;
		}

	}
	}
	CView::OnRButtonDown(nFlags, point);
}

