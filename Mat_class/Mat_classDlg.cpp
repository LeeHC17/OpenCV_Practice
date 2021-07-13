
// Mat_classDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Mat_class.h"
#include "Mat_classDlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMatclassDlg 대화 상자



CMatclassDlg::CMatclassDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAT_CLASS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatclassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_Partial_Yes);
	DDX_Control(pDX, IDC_RADIO2, m_Partial_No);
	DDX_Control(pDX, IDC_RADIO3, m_Reversal_Yes);
	DDX_Control(pDX, IDC_RADIO4, m_Reversal_No);
	DDX_Control(pDX, IDC_RADIO5, m_Size_Big);
	DDX_Control(pDX, IDC_RADIO6, m_Size_Small);
	DDX_Control(pDX, IDC_RADIO7, m_Size_Original);
}

BEGIN_MESSAGE_MAP(CMatclassDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMatclassDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMatclassDlg 메시지 처리기

BOOL CMatclassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMatclassDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMatclassDlg::OnPaint()
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
HCURSOR CMatclassDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatclassDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (img.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}

	if (m_Partial_No.GetCheck()) {
		Mat img1 = img;
		if (m_Reversal_Yes.GetCheck()) {
			img1 = ~img1;
		}

		if (m_Size_Big.GetCheck()) {
			Mat big;
			resize(img1, big, Size(img1.cols + 100, img1.rows + 100));
			
			namedWindow("big_image1");
			imshow("big_image1", big);

			waitKey(0);
			destroyWindow("big_image1");
		}
		else if (m_Size_Small.GetCheck()) {
			Mat small;
			resize(img1, small, Size(img1.cols - 800, img1.rows - 800));

			namedWindow("small_image1");
			imshow("small_image1", small);

			waitKey(0);
			destroyWindow("small_image1");
		}
		else if (m_Size_Original.GetCheck()) {
			namedWindow("image1");
			imshow("image1", img1);

			waitKey(0);
			destroyWindow("image1");
		}
	}
	else if (m_Partial_Yes.GetCheck()) {
		Mat img2 = img;
		img2 = img2(Rect(675, 630, 240, 330));

		if (m_Reversal_Yes.GetCheck()) {
			img2 = ~img2;
		}

		if (m_Size_Big.GetCheck()) {
			Mat big;
			resize(img2, big, Size(img2.cols + 300, img2.rows + 300));

			namedWindow("big_image2");
			imshow("big_image2", big);

			waitKey(0);
			destroyWindow("big_image2");
		}
		else if (m_Size_Small.GetCheck()) {
			Mat small;
			resize(img2, small, Size(img2.cols - 100, img2.rows - 100));

			namedWindow("small_image2");
			imshow("small_image2", small);

			waitKey(0);
			destroyWindow("small_image2");
		}
		else if (m_Size_Original.GetCheck()) {
			namedWindow("image2");
			imshow("image2", img2);

			waitKey(0);
			destroyWindow("image2");
		}
	}
}
