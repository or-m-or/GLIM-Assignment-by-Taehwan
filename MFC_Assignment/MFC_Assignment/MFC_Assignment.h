#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"


/*-----------------------------
  CMFCAssignmentApp 앱 진입점
-------------------------------*/

class CMFCAssignmentApp : public CWinApp
{
public:
	CMFCAssignmentApp();

// 재정의
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMFCAssignmentApp theApp;
