
// Mat_classDlg.h: 헤더 파일
//
#include "opencv2/opencv.hpp"
using namespace cv;
#pragma once


// CMatclassDlg 대화 상자
class CMatclassDlg : public CDialogEx
{
// 생성입니다.
public:
	CMatclassDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAT_CLASS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	Mat img = imread("example.jpg");
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_Partial_Yes;
	CButton m_Partial_No;
	CButton m_Reversal_Yes;
	CButton m_Reversal_No;
	CButton m_Size_Big;
	CButton m_Size_Small;
	CButton m_Size_Original;
	afx_msg void OnBnClickedButton1();
};
