
// GraphicEditor.h : GraphicEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGraphicEditorApp:
// �� Ŭ������ ������ ���ؼ��� GraphicEditor.cpp�� �����Ͻʽÿ�.
//

class CGraphicEditorApp : public CWinApp
{
public:
	CGraphicEditorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicEditorApp theApp;
