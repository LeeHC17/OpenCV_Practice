
// EdgeDetectingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "EdgeDetecting.h"
#include "EdgeDetectingDlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

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


// CEdgeDetectingDlg 대화 상자



CEdgeDetectingDlg::CEdgeDetectingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDGEDETECTING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEdgeDetectingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEdgeDetectingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEdgeDetectingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEdgeDetectingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEdgeDetectingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CEdgeDetectingDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CEdgeDetectingDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CEdgeDetectingDlg 메시지 처리기

BOOL CEdgeDetectingDlg::OnInitDialog()
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

void CEdgeDetectingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEdgeDetectingDlg::OnPaint()
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
HCURSOR CEdgeDetectingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEdgeDetectingDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat small_size_origianl;
	resize(src, small_size_origianl, Size(src.cols - 500, src.rows - 500));
	namedWindow("Original");
	imshow("Original", small_size_origianl);

	waitKey(0);
	destroyWindow("Original");
}


void CEdgeDetectingDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!1"), _T("ERROR"), MB_ICONERROR);
	}

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 130;
	Mat small_size_edge;
	resize(edge, small_size_edge, Size(edge.cols - 500, edge.rows - 500));
	imshow("edge", small_size_edge);

	waitKey(0);
	destroyWindow("edge");
}


void CEdgeDetectingDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}
	Mat dst;
	Canny(src, dst, 50, 150);
	Mat small_size_dst;
	resize(dst, small_size_dst, Size(dst.cols - 500, dst.rows - 500));

	imshow("Canny", small_size_dst);

	waitKey(0);
	destroyWindow("Canny");
}


void CEdgeDetectingDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}
	Mat src2;
	GaussianBlur(src, src2, Size(5,5), 7);
	Mat edge;
	Canny(src2, edge, 50, 200);

	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	Mat small_size_dst;
	resize(dst, small_size_dst, Size(dst.cols - 500, dst.rows - 500));
	imshow("HoughLine", small_size_dst);

	waitKey(0);
	destroyWindow("HoughLine");
}


void CEdgeDetectingDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}
	Mat src2;
	GaussianBlur(src, src2, Size(3, 3), 5);

	Mat edge;
	Canny(src2, edge, 50, 150);

	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}
	Mat small_size_dst;
	resize(dst, small_size_dst, Size(dst.cols - 500, dst.rows - 500));
	imshow("HoughLinesP", small_size_dst);

	waitKey(0);
	destroyWindow("HoughLinesP");
}
