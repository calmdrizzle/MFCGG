
// GEditor.h : GEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGEditorApp:
// �� Ŭ������ ������ ���ؼ��� GEditor.cpp�� �����Ͻʽÿ�.
//

class CGEditorApp : public CWinApp
{
public:
	CGEditorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGEditorApp theApp;
