
// PeopleDetectorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PeopleDetector.h"
#include "PeopleDetectorDlg.h"
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


// CPeopleDetectorDlg 대화 상자



CPeopleDetectorDlg::CPeopleDetectorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PEOPLEDETECTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPeopleDetectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_Detect);
	DDX_Control(pDX, IDC_RADIO1, m_Hog);
	DDX_Control(pDX, IDC_RADIO2, m_Haar);
}

BEGIN_MESSAGE_MAP(CPeopleDetectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPeopleDetectorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CPeopleDetectorDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CPeopleDetectorDlg 메시지 처리기

BOOL CPeopleDetectorDlg::OnInitDialog()
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
	if (!m_Detect.GetCheck()) {
		m_Hog.EnableWindow(FALSE);
		m_Haar.EnableWindow(FALSE);
	}


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPeopleDetectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPeopleDetectorDlg::OnPaint()
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
HCURSOR CPeopleDetectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPeopleDetectorDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	VideoCapture cap("vtest.avi");

	if (!cap.isOpened()) {
		MessageBox(_T("Video open failed!!"), _T("ERROR"), MB_ICONERROR);
	}

	Mat frame;
	
	if (!m_Detect.GetCheck()) {
		while (true) {
			cap >> frame;
			
			if (frame.empty()) {
				break;
			}

			imshow("frame", frame);

			if (waitKey(10) == 27) {  // press ESC Key
				break;
			}
		}
		destroyWindow("frame");
	}
	else if (m_Detect.GetCheck() && m_Hog.GetCheck()) {
		while (true) {
			cap >> frame;
			
			if (frame.empty()) {
				break;
			}

			HOGDescriptor hog;
			hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

			vector<Rect> detect;
			hog.detectMultiScale(frame, detect);

			for (Rect rc : detect) {
				rectangle(frame, rc, Scalar(0, 255, 0), 2);
			}
			
			imshow("Hog detect", frame);

			if (waitKey(10) == 27) { // press ESC Key
				break;
			}
		}
		destroyWindow("Hog detect");
	}
	else if (m_Detect.GetCheck() && m_Haar.GetCheck()) {
		while (true) {
			cap >> frame;

			if (frame.empty()) {
				break;
			}

			CascadeClassifier classifier("haarcascade_fullbody.xml");

			if (classifier.empty()) {
				MessageBox(_T("Xml load failed!!"), _T("ERROR"), MB_ICONERROR);
				break;
			}

			vector<Rect> detect;
			classifier.detectMultiScale(frame, detect);

			for (Rect rc : detect) {
				rectangle(frame, rc, Scalar(0, 255, 0), 2);
			}

			imshow("Haar detect", frame);

			if (waitKey(10) == 27) { // press ESC Key
				break;
			}
		}
		destroyWindow("Haar detect");
	}
}


void CPeopleDetectorDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Detect.GetCheck()) {
		m_Hog.EnableWindow(TRUE);
		m_Haar.EnableWindow(TRUE);
	}
	else if (!m_Detect.GetCheck()) {
		m_Hog.SetCheck(FALSE);
		m_Haar.SetCheck(FALSE);

		m_Hog.EnableWindow(FALSE);
		m_Haar.EnableWindow(FALSE);
	}
}
