
// FlatFieldCorrectionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FlatFieldCorrection.h"
#include "FlatFieldCorrectionDlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);
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


// CFlatFieldCorrectionDlg 대화 상자



CFlatFieldCorrectionDlg::CFlatFieldCorrectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FLATFIELDCORRECTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlatFieldCorrectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFlatFieldCorrectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFlatFieldCorrectionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFlatFieldCorrectionDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFlatFieldCorrectionDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFlatFieldCorrectionDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CFlatFieldCorrectionDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CFlatFieldCorrectionDlg 메시지 처리기

BOOL CFlatFieldCorrectionDlg::OnInitDialog()
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

void CFlatFieldCorrectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFlatFieldCorrectionDlg::OnPaint()
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
HCURSOR CFlatFieldCorrectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFlatFieldCorrectionDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);               // 히스토그램 스트레칭
	resize(dst, dst, Size(dst.cols - 1200, dst.rows - 1200));
	
	imshow("Histogram stretching", dst);
	imshow("StretchingHist", getGrayHistImage(calcGrayHist(dst)));   // 히스토그램 그래프 출력
	
	waitKey(0);
	destroyAllWindows();

}


void CFlatFieldCorrectionDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}

	Mat dst;
	equalizeHist(src, dst);											// 히스토그램 평활화
	
	resize(dst, dst, Size(dst.cols - 1200, dst.rows - 1200));
	
	imshow("Histogram equalization", dst);
	imshow("EqualHist", getGrayHistImage(calcGrayHist(dst)));		// 히스토그램 그래프 출력
	
	waitKey(0);
	destroyAllWindows();
}


void CFlatFieldCorrectionDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox(_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}

	Mat dst;
	Ptr<CLAHE> clahe = createCLAHE();							// 적응형 히스토그램 평활화
	clahe->setClipLimit(2);
	clahe->apply(src, dst);
	
	resize(dst, dst, Size(dst.cols - 1200, dst.rows - 1200));
	
	imshow("CLAHE", dst);
	imshow("CLAHEHist", getGrayHistImage(calcGrayHist(dst)));  // 히스토그램 그래프 출력
	
	waitKey(0);
	destroyAllWindows();
}


void CFlatFieldCorrectionDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat dst;
	resize(src, dst, Size(src.cols - 1200, src.rows - 1200));
	
	namedWindow("Original");
	
	imshow("Original", dst);
	imshow("Hist", getGrayHistImage(calcGrayHist(dst)));
	
	waitKey(0);
	destroyAllWindows();
}

void CFlatFieldCorrectionDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (src.empty()) {
		MessageBox (_T("Image load failed!!"), _T("ERROR"), MB_ICONERROR);
	}
	Mat dst;
	double gamma = 0.5;

	Mat table(1, 256, CV_8UC1);
	uchar* p = table.ptr();
	for (int i = 0; i < 256; i++) {
		p[i] = saturate_cast<uchar> (pow(i / 255.0, gamma) * 255.0);  // 감마 보정
	}

	LUT(src, table, dst);

	resize(dst, dst, Size(dst.cols - 1200, dst.rows - 1200));

	imshow("Gamma correction", dst);
	imshow("GammaHist", getGrayHistImage(calcGrayHist(dst)));
	waitKey(0);
	destroyAllWindows();
}

/* 히스토그램 구하기 */
Mat calcGrayHist(const Mat& img) {  
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

/* 히스토그램 그래프 그리기 */
Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}
