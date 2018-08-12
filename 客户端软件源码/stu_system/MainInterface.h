#include "mscomm1.h"
#include "afxwin.h"
#if !defined(AFX_MAININTERFACE_H__344688FB_CB20_42D0_8CCE_0DADACA2090D__INCLUDED_)
#define AFX_MAININTERFACE_H__344688FB_CB20_42D0_8CCE_0DADACA2090D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainInterface.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CMainInterface dialog

class CMainInterface : public CDialog
{
// Construction
public:
	CMainInterface(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainInterface)
	enum { IDD = IDD_MAIN_INTERFACE };
//	CListCtrl	m_list;
//	CString	m_edit_name;
	CString	m_edit_num;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainInterface)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainInterface)
	afx_msg void OnFindButton();
	afx_msg void OnExitSystem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strRecvData;
	CMscomm1 m_cComm;
	DECLARE_EVENTSINK_MAP()
	void OnComm();
	afx_msg void OnButtonRecv();
	afx_msg void OnLvnItemchangedListDisplay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditRecv();
	afx_msg void OnDisplay2();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnButtonDm();
	afx_msg void OnButtonTJ();
	afx_msg void OnButtonGm();
	//CComboBox m_mdData;
	CComboBox m_ckData;
	CString m_xgData;
	afx_msg void OnButtonYd();
	afx_msg void OnButtonWd();
	afx_msg void OnButtonQj();
	afx_msg void OnButtonCj();
	//×Ô¶¯¼à²â´®¿Ú
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAININTERFACE_H__344688FB_CB20_42D0_8CCE_0DADACA2090D__INCLUDED_)
