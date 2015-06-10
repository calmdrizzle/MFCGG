
// GraphicEditorDoc.h : CGraphicEditorDoc Ŭ������ �������̽�
//


#pragma once
#include "Object.h"
#include "MainFrm.h"
#include "Line.h"
#include "GPLine.h"
#include "GEllipse.h"
#include "GRectangle.h"
#include "Text.h"


class CGraphicEditorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

	// Ư���Դϴ�.
public:
	bool gobj_context_menu_enabled;
	Object* cur_gobj;
	CPtrList gobj_list;
	GObj_Type cur_type;
	CPoint point;
	CPtrList temp_list;

	int cur_thickness;
	COLORREF cur_color;
	COLORREF cur_fullcolor;
	int cur_linepattern;
	int cur_fullpattern;

	// text
	bool bItalic, bUnderline;
	int size;
	CString fontName;
	COLORREF text_color;


	CPtrList gobj_selected_list;
	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// �����Դϴ�.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnSelect();
	afx_msg void OnPolyline();
	afx_msg void OnLine();
	afx_msg void OnColorBlue();
	afx_msg void OnThickness10();
	afx_msg void OnColorGreen();
	afx_msg void OnColorRed();
	afx_msg void OnThickness1();
	afx_msg void OnThickness5();
	afx_msg void OnLinepattern1();
	afx_msg void OnLinepattern2();
	afx_msg void OnLinepattern3();
	afx_msg void OnRectangle();
	afx_msg void OnIncolorRed();
	afx_msg void OnIncolorGreen();
	afx_msg void OnIncolorBlue();
	afx_msg void OnEllipse();
	afx_msg void OnText();
	afx_msg void OnInpattern1();
	afx_msg void OnInpattern2();
	afx_msg void OnInpattern3();
	afx_msg void OnFcolorRed();
	afx_msg void OnFcolorGreen();
	afx_msg void OnFcolorBlue();
	afx_msg void OnFont1();
	afx_msg void OnFont2();
	afx_msg void OnFont3();
	afx_msg void OnFontsize30();
	afx_msg void OnFontsize50();
	afx_msg void OnFontsize100();
	afx_msg void OnItalic();
	afx_msg void OnUnderline();
	afx_msg void OnColorBlack();
	afx_msg void OnIncolorBlack();
	afx_msg void OnColorWhite();
	afx_msg void OnIncolorWhite();
};
