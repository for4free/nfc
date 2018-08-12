// GM.cpp : 实现文件
//

#include "stdafx.h"
#include "stu_system.h"
#include "GM.h"
#include "afxdialogex.h"
#include "usersql.h" 
#include "MD5.h" 
#include "goblextern.h"
#include "stu_systemDlg.h"
// CGM 对话框

IMPLEMENT_DYNAMIC(CGM, CDialogEx)

CGM::CGM(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGM::IDD, pParent)
	, m_mmData1(_T(""))
	, m_mmData2(_T(""))
	, m_mmData3(_T(""))
{

}

CGM::~CGM()
{
}

void CGM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ODDMM, m_mmData1);
	DDX_Text(pDX, IDC_EDIT_NEWMM, m_mmData2);
	DDX_Text(pDX, IDC_EDIT_CHMM, m_mmData3);
}


BEGIN_MESSAGE_MAP(CGM, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUE, &CGM::OnButtonQue)
	ON_BN_CLICKED(IDC_BUTTON_TUI, &CGM::OnBnClickedButtonTui)
END_MESSAGE_MAP()


// CGM 消息处理程序


void CGM::OnButtonQue()
{
	// TODO:  在此添加控件通知处理程序代码   m_mmDate1
	MD5 md5;                 //定义MD5的类
	char sql_insert[200];
	MYSQL_ROW column;;
	GetDlgItem(IDC_EDIT_ODDMM)->GetWindowText(m_mmData1);
	GetDlgItem(IDC_EDIT_NEWMM)->GetWindowText(m_mmData2);
	GetDlgItem(IDC_EDIT_CHMM)->GetWindowText(m_mmData3);
	mysql_query(&mysql, "set names gb2312");
	//	CString sql = "123456";           //需要加密的字符串
	md5.update(m_mmData1.GetBuffer());          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string
	m_mmData1 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型
		if (pass == m_mmData1)
		{
			md5.reset();
			mysql_query(&mysql, "set names gb2312");
			//	CString sql = "123456";           //需要加密的字符串
			md5.update(m_mmData2.GetBuffer());          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string
			m_mmData2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型
			md5.reset();
			mysql_query(&mysql, "set names gb2312");
			//	CString sql = "123456";           //需要加密的字符串
			md5.update(m_mmData3.GetBuffer());          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string
			m_mmData3 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型
			if ((m_mmData2 == m_mmData3))
			{
				if (m_mmData2.IsEmpty() || m_mmData3.IsEmpty())
				{
					MessageBox("密码不能为空", "失败", MB_OK);
				}
				else
				{
					sprintf_s(sql_insert, "update jsb set pass = '%s' where id = '%s';", m_mmData2, user);
					mysql_query(&mysql, sql_insert);
					sprintf_s(sql_insert, "select  pass from jsb where id = '%s';", user);
					mysql_query(&mysql, sql_insert);
					resultset = mysql_store_result(&mysql);
					column = mysql_fetch_row(resultset);
					if (column[0] == m_mmData2)
					{
						MessageBox("改密成功", "成功", MB_OK);
						pass = m_mmData2;
					}
					else
					{
						MessageBox("改密失败(网络原因)", "失败", MB_OK);
					}
				}
			}
			else
			{
				MessageBox("两次新密码不一致！", "失败", MB_OK);
			}
		}
		else
		{
			MessageBox("旧密码不正确！", "失败", MB_OK);
		}
}




void CGM::OnBnClickedButtonTui()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}


