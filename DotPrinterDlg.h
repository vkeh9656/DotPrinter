
// DotPrinterDlg.h: 헤더 파일
//

#pragma once


// CDotPrinterDlg 대화 상자
class CDotPrinterDlg : public CDialogEx
{
private:
	CImage m_my_image;
	CDC m_my_dc;

	BITMAP m_bmp_info;
	unsigned int* mp_image_data;
// 생성입니다.
public:
	CDotPrinterDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void AddTimeToList(const wchar_t* ap_msg, int a_time_value);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOTPRINTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPixelBtn();
	CListBox m_msg_list;
	afx_msg void OnBnClickedPixelvBtn();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMemPixelBtn();
	afx_msg void OnBnClickedMemPixelvBtn();
	afx_msg void OnBnClickedMemDirectBtn();
};
