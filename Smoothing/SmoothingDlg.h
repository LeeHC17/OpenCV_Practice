
// SmoothingDlg.h: 헤더 파일
//
#include "opencv2/opencv.hpp"
using namespace cv;
#pragma once


// CSmoothingDlg 대화 상자
class CSmoothingDlg : public CDialogEx
{
// 생성입니다.
public:
	CSmoothingDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMOOTHING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	Mat src = imread("example.jpg");
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Gaussian_Sigma;
	afx_msg void OnBnClickedButton1();
	CEdit m_Median_Ksize;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
