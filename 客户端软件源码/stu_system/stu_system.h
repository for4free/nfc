// stu_system.h : main header file for the STU_SYSTEM application
//

#if !defined(AFX_STU_SYSTEM_H__CF1D5446_EF0B_4BEE_9775_0B9F2780B67C__INCLUDED_)
#define AFX_STU_SYSTEM_H__CF1D5446_EF0B_4BEE_9775_0B9F2780B67C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStu_systemApp:
// See stu_system.cpp for the implementation of this class
//

class CStu_systemApp : public CWinApp
{
public:
	CStu_systemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStu_systemApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStu_systemApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STU_SYSTEM_H__CF1D5446_EF0B_4BEE_9775_0B9F2780B67C__INCLUDED_)
