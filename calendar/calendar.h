
// calendar.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcalendarApp:
// �йش����ʵ�֣������ calendar.cpp
//

class CcalendarApp : public CWinAppEx
{
public:
	CcalendarApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcalendarApp theApp;