
// MFCOpenGl.h : MFCOpenGl Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCOpenGlApp:
// �йش����ʵ�֣������ MFCOpenGl.cpp
//

class CMFCOpenGlApp : public CWinApp
{
public:
	CMFCOpenGlApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenGlApp theApp;
