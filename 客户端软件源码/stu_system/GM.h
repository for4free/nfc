#pragma once
#include "afxwin.h"

// CGM 对话框

class CGM : public CDialogEx
{
	DECLARE_DYNAMIC(CGM)

public:
	CGM(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGM();

// 对话框数据
	enum { IDD = IDD_GM };
	CString m_mmData1;
	CString m_mmData2;
	CString m_mmData3;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnButtonQue();
	afx_msg void OnEnChangeEditOddmm();
	afx_msg void OnBnClickedButtonTui();
	DECLARE_MESSAGE_MAP()
public:

};
