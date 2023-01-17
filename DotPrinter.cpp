
// DotPrinter.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DotPrinter.h"
#include "DotPrinterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDotPrinterApp

BEGIN_MESSAGE_MAP(CDotPrinterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDotPrinterApp 생성

CDotPrinterApp::CDotPrinterApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CDotPrinterApp 개체입니다.

CDotPrinterApp theApp;


// CDotPrinterApp 초기화

BOOL CDotPrinterApp::InitInstance()
{
	CWinApp::InitInstance();

	CDotPrinterDlg dlg;
	dlg.DoModal();
	return FALSE;
}

