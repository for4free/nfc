// stu_systemDlg.h : header file
//

#if !defined(AFX_STU_SYSTEMDLG_H__261C7851_67B2_4B0C_A683_ED0D1C8FA840__INCLUDED_)
#define AFX_STU_SYSTEMDLG_H__261C7851_67B2_4B0C_A683_ED0D1C8FA840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStu_systemDlg dialog

class CStu_systemDlg : public CDialog
{
// Construction
public:
	CStu_systemDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CStu_systemDlg)
	enum { IDD = IDD_STU_SYSTEM_DIALOG };
	CString	m_password;
	CString	m_username;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStu_systemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStu_systemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLogin();
	afx_msg void OnExit();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditPassword();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STU_SYSTEMDLG_H__261C7851_67B2_4B0C_A683_ED0D1C8FA840__INCLUDED_)
