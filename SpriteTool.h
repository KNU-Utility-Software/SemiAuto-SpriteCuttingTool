
// SpriteTool.h : SpriteTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSpriteToolApp:
// �� Ŭ������ ������ ���ؼ��� SpriteTool.cpp�� �����Ͻʽÿ�.
//

class CSpriteToolApp : public CWinAppEx
{
public:
	CSpriteToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnImageOpen();
};

extern CSpriteToolApp theApp;
