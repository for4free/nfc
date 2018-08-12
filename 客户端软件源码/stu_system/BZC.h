#pragma once
#include "afxwin.h"


// CBZC 对话框

class CBZC : public CDialogEx
{
	DECLARE_DYNAMIC(CBZC)

public:
	CBZC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBZC();


// 对话框数据
	enum { IDD = IDD_DIALOG_BCZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonTchu();	
	afx_msg void OnButtonDch();
	afx_msg void OnButtonSch();
	CEdit m_mdData2;
	afx_msg void OnButtonChj();
};

