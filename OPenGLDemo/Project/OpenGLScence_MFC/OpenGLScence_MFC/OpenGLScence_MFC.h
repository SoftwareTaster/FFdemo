
// OpenGLScence_MFC.h : OpenGLScence_MFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COpenGLScence_MFCApp:
// �йش����ʵ�֣������ OpenGLScence_MFC.cpp
//

class COpenGLScence_MFCApp : public CWinAppEx
{
public:
	COpenGLScence_MFCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLScence_MFCApp theApp;
