// stu_systemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stu_system.h"
#include "stu_systemDlg.h"
#include "MainInterface.h"
#include "usersql.h"
#include "goble.h" 
#include "MD5.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStu_systemDlg dialog

CStu_systemDlg::CStu_systemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStu_systemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStu_systemDlg)
	m_password = _T("");
	m_username = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStu_systemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStu_systemDlg)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStu_systemDlg, CDialog)
	//{{AFX_MSG_MAP(CStu_systemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, &CStu_systemDlg::OnEnChangeEditPassword)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStu_systemDlg message handlers

BOOL CStu_systemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	SkinH_Attach();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    mysql_init(&mysql);// 初始化mysql结构
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStu_systemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStu_systemDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStu_systemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CStu_systemDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	int ret;
	UpdateData(true);//刷新对话框的数据
	CString strSQL;
	char sql_insert[200];
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "miniserver", "data", 3306, NULL, 0))
	{
		mysql_query(&mysql, "set names gb2312");
		MD5 md5;                 //定义MD5的类
	//	CString sql = "123456";           //需要加密的字符串
		md5.update(m_password.GetBuffer());          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string
		m_password = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

		sprintf_s(sql_insert, "select * from jsb where id ='%s' and pass = '%s' and hol = 0", m_username, m_password);
		if (mysql_query(&mysql, sql_insert))
		{
			MessageBox("数据库查询发生错误!", "Error", MB_OK);
			m_password = "";
			mysql_close(&mysql);//关闭sql
		}
		else
		{
			resultset = mysql_store_result(&mysql);// 获得结果集 
			if (mysql_fetch_row(resultset) != NULL)
			{//如果用户名和密码匹配的话
				pass = m_password;
				user = m_username;
				ret = mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gb2312");//设置中文编码，由于数据库的编码与vc不同
				//this->ShowWindow(SW_HIDE);//隐藏登入窗口
				SendMessage(WM_CLOSE);
				CMainInterface dlg;//定义主界面窗口类对象
				dlg.DoModal();//以模态形式显示一个窗口
				this->ShowWindow(SW_SHOW);
			}
			else
			{
				MessageBox("密码或用户名错误，请重新输入！！", "错误", MB_OK);
				m_password = "";
				mysql_close(&mysql);//关闭sql
			}
			UpdateData(false);
		}
	}
	else
	{
		MessageBox("出现错误！", "错误", MB_OK);
	}

}

void CStu_systemDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CStu_systemDlg::OnEnChangeEditPassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
