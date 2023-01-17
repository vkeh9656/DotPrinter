
// DotPrinterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DotPrinter.h"
#include "DotPrinterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDotPrinterDlg 대화 상자



CDotPrinterDlg::CDotPrinterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOTPRINTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDotPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_msg_list);
}

BEGIN_MESSAGE_MAP(CDotPrinterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PIXEL_BTN, &CDotPrinterDlg::OnBnClickedPixelBtn)
	ON_BN_CLICKED(IDC_PIXELV_BTN, &CDotPrinterDlg::OnBnClickedPixelvBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MEM_PIXEL_BTN, &CDotPrinterDlg::OnBnClickedMemPixelBtn)
	ON_BN_CLICKED(IDC_MEM_PIXELV_BTN, &CDotPrinterDlg::OnBnClickedMemPixelvBtn)
	ON_BN_CLICKED(IDC_MEM_DIRECT_BTN, &CDotPrinterDlg::OnBnClickedMemDirectBtn)
	ON_BN_CLICKED(IDC_R_PIXEL_BTN, &CDotPrinterDlg::OnBnClickedRPixelBtn)
	ON_BN_CLICKED(IDC_R_MEM_PIXEL_BTN, &CDotPrinterDlg::OnBnClickedRMemPixelBtn)
	
	ON_BN_CLICKED(IDC_R_MEM_DIRECT_BTN, &CDotPrinterDlg::OnBnClickedRMemDirectBtn)
	ON_BN_CLICKED(IDC_NOISE_START_BTN, &CDotPrinterDlg::OnBnClickedNoiseStartBtn)
	ON_BN_CLICKED(IDC_NOISE_STOP_BTN, &CDotPrinterDlg::OnBnClickedNoiseStopBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDotPrinterDlg 메시지 처리기

BOOL CDotPrinterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_my_image.Create(450, 400, 32);
	m_my_dc.Attach(m_my_image.GetDC());	// 영구 객체 생성

	GetObject((HBITMAP)m_my_image, sizeof(BITMAP), &m_bmp_info);
	mp_image_data = (unsigned int *)m_my_image.GetBits(); // 첫 줄 제일 위 (0,0)
	mp_image_data += m_bmp_info.bmWidthBytes / sizeof(unsigned int); // 에서 맨 끝으로 이동 ,4의 배수로 나눈 정수
	
	srand((unsigned int)time(NULL));
	// CDC* p_dc = CDC::FromHandle(h_dc); // 임시 객체 생성

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDotPrinterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDotPrinterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDotPrinterDlg::AddTimeToList(const wchar_t* ap_msg, int a_time_value)
{
	CString str;
	str.Format(L"%s : %d", ap_msg, a_time_value);
	int index = m_msg_list.InsertString(-1, str);
	m_msg_list.SetCurSel(index);
}

void CDotPrinterDlg::OnBnClickedPixelBtn()
{
	CClientDC dc(this);

	int start_tick = GetTickCount();
	for (int y = 0; y < m_bmp_info.bmHeight; y++)
	{
		for (int x = 0; x < m_bmp_info.bmWidth; x++)
		{
			dc.SetPixel(x, y, RGB(0, 0, 255));
		}
	}

	int end_tick = GetTickCount();
	AddTimeToList(L"SetPixel 사용", end_tick - start_tick);
	
	
}


void CDotPrinterDlg::OnBnClickedPixelvBtn()
{
	CClientDC dc(this);

	int start_tick = GetTickCount();
	for (int y = 0; y < m_bmp_info.bmHeight; y++)
	{
		for (int x = 0; x < m_bmp_info.bmWidth; x++)
		{
			dc.SetPixelV(x, y, RGB(0, 255, 0));
		}
	}

	int end_tick = GetTickCount();
	AddTimeToList(L"SetPixelV 사용", end_tick - start_tick);
}


void CDotPrinterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_my_dc.Detach();
	m_my_image.ReleaseDC();
}


void CDotPrinterDlg::OnBnClickedMemPixelBtn()
{
	CClientDC dc(this);

	int start_tick = GetTickCount();
	for (int y = 0; y < m_bmp_info.bmHeight; y++)
	{
		for (int x = 0; x < m_bmp_info.bmWidth; x++)
		{
			m_my_dc.SetPixel(x, y, RGB(0, 255, 255));
		}
	}

	int end_tick = GetTickCount();
	AddTimeToList(L"CImage SetPixel 사용 - 출력 전", end_tick - start_tick);
	m_my_image.Draw(dc, 0, 0);
	AddTimeToList(L"CImage SetPixel 사용 - 출력 후", end_tick - start_tick);
}


void CDotPrinterDlg::OnBnClickedMemPixelvBtn()
{
	CClientDC dc(this);

	int start_tick = GetTickCount();
	for (int y = 0; y < m_bmp_info.bmHeight; y++)
	{
		for (int x = 0; x < m_bmp_info.bmWidth; x++)
		{
			m_my_dc.SetPixelV(x, y, RGB(255, 0, 255));
		}
	}

	int end_tick = GetTickCount();
	AddTimeToList(L"CImage SetPixelV 사용 - 출력 전", end_tick - start_tick);
	m_my_image.Draw(dc, 0, 0);
	AddTimeToList(L"CImage SetPixelV 사용 - 출력 후", end_tick - start_tick);
}


void CDotPrinterDlg::OnBnClickedMemDirectBtn()
{
	CClientDC dc(this);

	unsigned int* p = mp_image_data;
	int count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	int start_tick = GetTickCount();

	for (int i = 0; i < count; i++)
	{
		// *p = 0xAARRGGBB
		*p = 0x00FF0000; // 빨간색
		p--;
	}
	/*for (int y = 0; y < 400; y++)
	{
		for (int x = 0; x < 450; x++)
		{
			m_my_dc.SetPixelV(x, y, RGB(255, 0, 255));
		}
	}*/

	int end_tick = GetTickCount();
	AddTimeToList(L"CImage 직접 출력 사용 - 출력 전", end_tick - start_tick);
	m_my_image.Draw(dc, 0, 0);
	AddTimeToList(L"CImage 직접 출력 사용 - 출력 후", end_tick - start_tick);
}


void CDotPrinterDlg::OnBnClickedRPixelBtn()
{
	CClientDC dc(this);

	int limit = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	int start_tick = GetTickCount(), x, y;
	
	for (int i = 0; i < 100000; i++)
	{
		x = rand() % m_bmp_info.bmWidth;
		y = rand() % m_bmp_info.bmHeight;
		dc.SetPixel(x, y, RGB(rand()%256, rand() % 256, rand() % 256));
	}

	int end_tick = GetTickCount();
	AddTimeToList(L"난수 SetPixel 사용", end_tick - start_tick);
	
}



void CDotPrinterDlg::OnBnClickedRMemPixelBtn()
{
	CClientDC dc(this);

	int limit = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	int start_tick = GetTickCount(), x, y;

	for (int i = 0; i < 100000; i++)
	{
		x = rand() % m_bmp_info.bmWidth;
		y = rand() % m_bmp_info.bmHeight;
		m_my_dc.SetPixel(x, y, RGB(rand() % 256, rand() % 256, rand() % 256));
	}


	int end_tick = GetTickCount();
	AddTimeToList(L"(CImage) 난수 SetPixel 사용 - 출력 전", end_tick - start_tick);
	m_my_image.Draw(dc, 0, 0);
	AddTimeToList(L"(CImage) 난수 SetPixel 사용 - 출력 후", end_tick - start_tick);
}



void CDotPrinterDlg::OnBnClickedRMemDirectBtn()
{
	CClientDC dc(this);

	unsigned int* p = mp_image_data;
	int start_tick = GetTickCount(), x, y;

	for (int i = 0; i < 100000; i++)
	{
		x = rand() % m_bmp_info.bmWidth;
		y = rand() % m_bmp_info.bmHeight;
		*(p - (m_bmp_info.bmWidth - x) - y * m_bmp_info.bmWidth)= RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	int end_tick = GetTickCount();
	AddTimeToList(L"(CImage) 난수 직접 출력 사용 - 출력 전", end_tick - start_tick);
	m_my_image.Draw(dc, 0, 0);
	AddTimeToList(L"(CImage) 난수 직접 출력 사용 - 출력 후", end_tick - start_tick);
}


void CDotPrinterDlg::OnBnClickedNoiseStartBtn()
{
	SetTimer(1, 1, NULL);
}


void CDotPrinterDlg::OnBnClickedNoiseStopBtn()
{
	KillTimer(1);
}


void CDotPrinterDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		/*CClientDC dc(this);

		int start_tick = GetTickCount();
		for (int y = 0; y < m_bmp_info.bmHeight; y++)
		{
			for (int x = 0; x < m_bmp_info.bmWidth; x++)
			{
				x = rand() % m_bmp_info.bmWidth;
				y = rand() % m_bmp_info.bmHeight;
				m_my_dc.SetPixel(x, y, RGB(rand()%256, rand() % 256, rand() % 256));
			}
		}
		m_my_image.Draw(dc, 0, 0);*/



		CClientDC dc(this);

		unsigned int* p = mp_image_data;
		int start_tick = GetTickCount(), x, y;

		for (int i = 0; i < 100000; i++)
		{
			x = rand() % m_bmp_info.bmWidth;
			y = rand() % m_bmp_info.bmHeight;
			*(p - (m_bmp_info.bmWidth - x) - y * m_bmp_info.bmWidth) = RGB(rand() % 256, rand() % 256, rand() % 256);
		}

		int end_tick = GetTickCount();
		
		m_my_image.Draw(dc, 0, 0);
		

	}

	CDialogEx::OnTimer(nIDEvent);
}
