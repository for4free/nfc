// MainInterface.cpp : implementation file
//

#include "stdafx.h"
#include "stu_system.h"
#include "MainInterface.h"
#include "usersql.h" 
#include "goblextern.h"
#include "GM.h"
#include "BZC.h"
#include "Winspool.h"   //遍历串口函数相关
#include "Dbt.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CMainInterface dialog
int ser2 = 0;
CString seru;
DWORD pcReturned = 0;  // number of ports received


CMainInterface::CMainInterface(CWnd* pParent /*=NULL*/)
	: CDialog(CMainInterface::IDD, pParent)
	, m_strRecvData(_T(""))
	, m_xgData(_T(""))
{
	//{{AFX_DATA_INIT(CMainInterface)
	//m_edit_name = _T("");
	m_edit_num = _T("");
	//}}AFX_DATA_INIT
}


void CMainInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainInterface)
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_list);
	//DDX_Text(pDX, IDC_EDIT_NAME, m_edit_name);
	DDX_Text(pDX, IDC_EDIT_NUM, m_edit_num);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_RECV, m_strRecvData);
	DDX_Control(pDX, IDC_MSCOMM1, m_cComm);
	DDX_Control(pDX, IDC_COMBO1, m_mdData);
	DDX_Control(pDX, IDC_COMBO_CK, m_ckData);
	DDX_Text(pDX, IDC_EDIT_XG, m_xgData);
	if (result1 == "")
	{
		char sql_insert[200];
		int i = 0;
		int nRow = 0;
		int j = 0;
		sprintf_s(sql_insert, "select bm from dyb where id = '%s';", user);
		mysql_query(&mysql, sql_insert);
		resultset = mysql_store_result(&mysql);// 获得结果集         
		if (mysql_num_rows(resultset) != NULL)
		{
			int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
			int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
			while (row = mysql_fetch_row(resultset))
			{
				m_mdData.AddString(_T(row[0]));

			}
		}
		CRect rc;
		m_mdData.SetCurSel(0);
		m_mdData.GetDroppedControlRect(&rc);
		m_mdData.GetParent()->ScreenToClient(&rc);
		rc.bottom += 150;
		m_mdData.MoveWindow(&rc);
		mysql_free_result(resultset);
	}
	int selectedPos = m_mdData.GetCurSel();
	m_mdData.GetLBText(selectedPos, result1);
	///枚举串口
	if (ser1 == "") //ser1 没有赋值，则枚举串口
	{
		//访问注册表获取串口信息
		HKEY hKey;
		if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey))   //打开串口注册表对应的键值 
		{
			int seri = 0;
			TCHAR portName[256], commName[256];
			DWORD dwLong, dwSize;
			while (1)
			{
				dwLong = dwSize = sizeof(portName);
				if (::RegEnumValue(hKey,
					seri,
					portName,
					&dwLong,
					NULL,
					NULL,
					(PUCHAR)commName,
					&dwSize) == ERROR_NO_MORE_ITEMS)//   枚举串口  
					break;
					m_ckData.AddString(commName);   // commName就是串口名字  
					ser1 = "1";
					seri++;
			}
			//高度信息
			CRect rc;
			m_ckData.SetCurSel(0);
			m_ckData.GetDroppedControlRect(&rc);
			m_ckData.GetParent()->ScreenToClient(&rc);
			rc.bottom += 150;
			m_ckData.MoveWindow(&rc);
			RegCloseKey(hKey);
		}
	}

	//请假信息初始化
	char sql_insert[200];
	MYSQL_ROW column;
	sprintf_s(sql_insert, "select bm from dyb where id = '%s';", user);
	if (mysql_query(&mysql, sql_insert))
	{
		MessageBox("数据库查询发生错误!", "Error", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);// 获得结果集         
		if (mysql_num_rows(resultset) != NULL)
		{
			while (row = mysql_fetch_row(resultset))
			{
				//写入1
				//MessageBox(row[0], "错误", MB_OK);
				sprintf_s(sql_insert, "UPDATE %s SET leav=1 WHERE no in ( select no from qjb)", row[0]);
				mysql_query(&mysql, sql_insert);
			}
		}
		else
		{
			MessageBox("没有数据!", "错误", MB_OK);
		}
		mysql_free_result(resultset);  // 释放结果集
	}


}


BEGIN_MESSAGE_MAP(CMainInterface, CDialog)
	//{{AFX_MSG_MAP(CMainInterface)
	ON_BN_CLICKED(IDC_FIND_BUTTON, OnFindButton)
	ON_BN_CLICKED(IDC_EXIT_SYSTEM, OnExitSystem)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_RECV, &CMainInterface::OnButtonRecv)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DISPLAY, &CMainInterface::OnLvnItemchangedListDisplay)
	ON_EN_CHANGE(IDC_EDIT_RECV, &CMainInterface::OnEnChangeEditRecv)
	ON_BN_CLICKED(IDC_DISPLAY2, &CMainInterface::OnDisplay2)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CMainInterface::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_BUTTON_DM, &CMainInterface::OnButtonDm)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainInterface::OnButtonTJ)
	ON_BN_CLICKED(IDC_BUTTON_GM, &CMainInterface::OnButtonGm)
	ON_BN_CLICKED(IDC_BUTTON_YD, &CMainInterface::OnButtonYd)
	ON_BN_CLICKED(IDC_BUTTON_WD, &CMainInterface::OnButtonWd)
	ON_BN_CLICKED(IDC_BUTTON_QJ, &CMainInterface::OnButtonQj)
	ON_BN_CLICKED(IDC_BUTTON_CJ, &CMainInterface::OnButtonCj)
	ON_WM_DEVICECHANGE()   //自动监测串口相关
END_MESSAGE_MAP()



BOOL CMainInterface::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	//0x4d36e978L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18  
	//DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;  


	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE://移除设备  
#if 1 
		m_ckData.ResetContent();
		//访问注册表获取串口信息
		MessageBox("设备已移除！请重新连接设备！", "");

#endif 
		break;
	case DBT_DEVICEARRIVAL://添加设备  
#if 1 
		MessageBox("设备已接入！", "");
		//访问注册表获取串口信息
		HKEY hKey;
		if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey))   //打开串口注册表对应的键值 
		{
			int seri = 0;
			TCHAR portName[256], commName[256];
			DWORD dwLong, dwSize;
			while (1)
			{
				dwLong = dwSize = sizeof(portName);
				if (::RegEnumValue(hKey,
					seri,
					portName,
					&dwLong,
					NULL,
					NULL,
					(PUCHAR)commName,
					&dwSize) == ERROR_NO_MORE_ITEMS)//   枚举串口 
					break;
					m_ckData.AddString(commName);   // commName就是串口名字  
					ser1 = "1";
					seri++;
			}
			//高度信息
			CRect rc;
			m_ckData.SetCurSel(0);
			m_ckData.GetDroppedControlRect(&rc);
			m_ckData.GetParent()->ScreenToClient(&rc);
			rc.bottom += 150;
			m_ckData.MoveWindow(&rc);
			RegCloseKey(hKey);
		}
#endif 
		break;

	default:
		break;
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainInterface message handlers

void CMainInterface::OnFindButton() 
{
	OnButtonDm();
	// TODO: Add your control notification handler code here
	int j = 0;
//	int nRow ;//插入行
	int flag=0;
	CString info;
	char sql_insert[200];
	UpdateData(true);
	sprintf_s(sql_insert, "select %s.no,zb.name,%s.att from zb,%s where %s.no = zb.no", result1, result1, result1, result1);
	if (mysql_query(&mysql, sql_insert))
		{
			MessageBox("数据库查询发生错误!", "Error", MB_OK);
		}
	else
		{                           
           resultset = mysql_store_result(&mysql);// 获得结果集         
           if (mysql_num_rows(resultset) != NULL)
           {
				int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
				int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
                while (row = mysql_fetch_row(resultset))
                {
					int i = 0;
				//	nRow = m_list.InsertItem(j, "");
					CString TEMP = _T("\t");
					CString TEMP1 = _T("\t已签到");
					CString TEMP2 = _T("\t未签到");
					for (i = 0; i< numFields; i++)
                    {
                        if((row[i]==m_edit_num))//||(row[i]==m_edit_name)
						{
							flag=1;
							if(row[i]==m_edit_num)
							{	
								if ((CString)row[i + 2] == '1')
								{
									info = (CString)row[i] + TEMP + (CString)row[i + 1] + TEMP1;
								}
								else
								{
									info = (CString)row[i] + TEMP + (CString)row[i + 1] + TEMP2;
								}
							}
							else 
							{
								if ((CString)row[i] == '1')
								{
									info = (CString)row[i - 2] + TEMP + (CString)row[i - 1] + TEMP1;
								}
								else
								{
									info = (CString)row[i - 2] + TEMP + (CString)row[i - 1] + TEMP2;
								}

							}
							MessageBox(info,"考勤", MB_OK);
						}
                    }
                    j++;					
                 }
				if(flag==0)
					{
						MessageBox("未找到!!","考勤", MB_OK);
					}
			}
			else
			{
				 MessageBox("没有数据!", "错误", MB_OK);
			} 
			mysql_free_result(resultset);  // 释放结果集
		}
		UpdateData(false);
}

void CMainInterface::OnExitSystem() 
{
	// TODO: Add your control notification handler code here
	char sql_insert[200];
	for (int i = 0; i <m_list.GetItemCount(); i++)  //勾选的   att = 1
	{
		if (m_list.GetCheck(i)) //这个是某行选中  //这个是前面的checkbox被选中 
		{
			sprintf_s(sql_insert, "update %s set att = 1 where id = '%d';", result1,i + 1);
			mysql_query(&mysql, sql_insert);
		}
	}
	sprintf_s(sql_insert, "select * from %s where att = 1;", result1);
	mysql_query(&mysql, sql_insert);
	resultset = mysql_store_result(&mysql);
	if (mysql_num_rows(resultset) != NULL)
	{
		sprintf_s(sql_insert, "update %s set att = 0,sum = sum+1 where att = 1;", result1);
		mysql_query(&mysql, sql_insert);
	}
	sprintf_s(sql_insert, "select * from %s where leav = 1;", result1);
	mysql_query(&mysql, sql_insert);
	resultset = mysql_store_result(&mysql);
	if (mysql_num_rows(resultset) != NULL)
	{
		sprintf_s(sql_insert, "update %s set leav = 0,lea = lea+1 where leav = 1;", result1);
		mysql_query(&mysql, sql_insert);
	}
	mysql_close(&mysql);
	SendMessage(WM_CLOSE);
	if (m_cComm.get_PortOpen()) //如果发现串口本来是打开的，则关闭串口
	{
		m_cComm.put_PortOpen(FALSE);
	}
}

BEGIN_EVENTSINK_MAP(CMainInterface, CDialog)
	ON_EVENT(CMainInterface, IDC_MSCOMM1, 1, CMainInterface::OnComm, VTS_NONE)
END_EVENTSINK_MAP()


void CMainInterface::OnComm()
{
	// TODO:  在此处添加消息处理程序代码
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len, k;
	byte rxdata[512]; //设置BYTE数组
	char sql[10] = { 0 };
	CString strtemp;
	if (m_cComm.get_CommEvent() == 2) //值为表示接收缓冲区内有字符
	{
		variant_inp = m_cComm.get_Input(); //读缓冲区消息
		safearray_inp = variant_inp; ///变量转换
		len = safearray_inp.GetOneDimSize(); //得到有效的数据长度
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata + k);
		for (k = 0; k<len; k++) //将数组转换为CString型变量
		{
			char bt = *(char*)(rxdata + k);//字符型
			sql[k] = bt;
			strtemp.Format(_T("%c"), bt); //将字符送入临时变量strtemp存放
			//	m_strRecvData += strtemp; //加入接收编辑框对应字符串
		}
	}

	MYSQL_ROW column;
	char sql_insert[200];
	//mysql_real_connect(&mysql, "localhost", "root", "new_pass", "test", 3306, NULL, 0);
	//sprintf_s(sql, "6B248AE9");
	sprintf_s(sql_insert, "select * from zb,%s where zb.no = %s.no and zb.cardid = '%c%c%c%c%c%c%c%c';", result1, result1, sql[0], sql[1], sql[2], sql[3], sql[4], sql[5], sql[6], sql[7]);
	mysql_query(&mysql, sql_insert);
	resultset = mysql_store_result(&mysql);
	if (mysql_num_rows(resultset) != NULL)
	{
		sprintf_s(sql_insert, "update %s,zb set %s.att = 1 where zb.no = %s.no and zb.cardid = '%c%c%c%c%c%c%c%c';", result1, result1, result1, sql[0], sql[1], sql[2], sql[3], sql[4], sql[5], sql[6], sql[7]);
	mysql_query(&mysql, sql_insert);
	//查询卡号对应的学号no 签到情况att
	CString temp, temp1;
	sprintf_s(sql_insert, "select zb.no,zb.name,%s.att,%s.sum from zb,%s where zb.no = %s.no and cardid = '%c%c%c%c%c%c%c%c';", result1, result1, result1, result1, sql[0], sql[1], sql[2], sql[3], sql[4], sql[5], sql[6], sql[7]);
	mysql_query(&mysql, sql_insert);
	resultset = mysql_store_result(&mysql);
	column = mysql_fetch_row(resultset);
		char *b = "1";
		CString fh;
		fh.Format(_T("1"));
		if (*column[2] == *b)
		{
			m_cComm.put_Output(COleVariant(fh));
			temp = (_T("-签到成功!"));
			temp1 = (_T("-"));  
			temp = temp1 + column[1] + temp;
			m_strRecvData = column[0] + temp;
		}
		else
		{
			temp = (_T("-签到失败!"));
			temp1 = (_T("-"));
			temp = temp1 + column[1] + temp;
			m_strRecvData = column[0] + temp;
		}
	}
	else
	{
		CString temp;
		temp = (_T("没有该卡片数据信息!"));
		m_strRecvData = temp;
	}
		//CString temp = (_T("签到成功! \n")); //显示完成后要自动换行
	UpdateData(FALSE); //更新编辑框内容
	OnButtonDm();
}


void CMainInterface::OnButtonRecv()
{
	if (ser1=="")
	{
		MessageBox("未连接刷卡设备或驱动有问题！","错误");
	}
	else
	{
		int selectedPos1 = m_ckData.GetCurSel();
		m_ckData.GetLBText(selectedPos1, ser1);
		char temp[200];
		for (int i = 1; i < 20; i++)
		{
			sprintf_s(temp, "COM%d", i);
			if (ser1 == temp)
			{
				ser2 = i;
				break;
			}
		}
		// TODO:  在此添加控件通知处理程序代码
		if (m_cComm.get_PortOpen()) //如果发现串口本来是打开的，则关闭串口
		{
			m_cComm.put_PortOpen(FALSE);
		}
		m_cComm.put_CommPort(ser2); //选择COM4端口
		m_cComm.put_InputMode(1); //输入方式为二进制方式
		m_cComm.put_InBufferSize(1024); //设置输入缓冲区
		m_cComm.put_OutBufferSize(512); //设置输出缓冲区
		m_cComm.put_Settings(TEXT("9600,n,8,1"));//波特率，无校验，个数据位，个停止位
		m_cComm.put_RThreshold(9); //每接收到一个字符时，触发OnComm事件
		m_cComm.put_PortOpen(true); //打开串口
		if (m_cComm.get_PortOpen()) //如果发现打开，显示名单
		{
			OnButtonDm();
		}
	}
}


void CMainInterface::OnLvnItemchangedListDisplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
 

void CMainInterface::OnEnChangeEditRecv()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMainInterface::OnDisplay2()
{
	OnButtonDm();
	// TODO:  在此添加控件通知处理程序代码
	char sql_insert[200];
	for (int i = 0; i < m_list.GetItemCount(); i++)   //勾选框处理
	{
		if (m_list.GetCheck(i)) //这个是某行选中  //这个是前面的checkbox被选中 
		{
			sprintf_s(sql_insert, "update %s,zb set %s.att = 1 where %s.no = zb.no and %s.id = '%d';", result1, result1, result1, result1, i + 1);
			mysql_query(&mysql, sql_insert);
		}
	}
	//显示未到
	int j = 0;//行标号
	UpdateData(true);
	m_list.DeleteAllItems();//删除listview控件中的所有项
	int nRow;//插入行
	while (m_list.DeleteColumn(0));//删除所有列
	m_list.InsertColumn(0, "学号", LVCFMT_LEFT, 125);//插入列
	m_list.InsertColumn(1, "姓名", LVCFMT_LEFT, 55);
	m_list.InsertColumn(2, "出勤", LVCFMT_LEFT, 42);
	m_list.InsertColumn(3, "总计", LVCFMT_LEFT, 40);
	m_list.InsertColumn(4, "请假", LVCFMT_LEFT, 40);
	m_list.InsertColumn(5, "假次", LVCFMT_LEFT, 40);
	//mysql_query(&mysql, "update qd set id = 1 where id = 2013");
	sprintf_s(sql_insert, "select %s.no,zb.name,%s.att,%s.sum,%s.leav,%s.lea from %s,zb where %s.no = zb.no and %s.att = 0", result1, result1, result1, result1, result1, result1, result1, result1);
	if (mysql_query(&mysql, sql_insert))
	{
		//	AfxMessageBox(mysql_error(&mysql));
		MessageBox("数据库查询发生错误!", "Error", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);// 获得结果集         
		if (mysql_num_rows(resultset) != NULL)
		{
			int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
			int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
			while (row = mysql_fetch_row(resultset))
			{
				int i = 0;
				nRow = m_list.InsertItem(j, "0");
				for (i = 0; i < numFields; i++)
				{
					//fprintf(stdout, " %s", row[i]); // 打印字段值	
					m_list.SetItemText(nRow, i, row[i]);//设置数据
				}
				j++;
			}
		}
		else
		{
			MessageBox("没有数据!", "Error", MB_OK);
		}
		mysql_free_result(resultset);  // 释放结果集
	}


	UpdateData(false);
	//AfxMessageBox(result1);
}


void CMainInterface::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}





void CMainInterface::OnButtonDm()
{
	char sql_insert[200];
	// TODO:  在此添加控件通知处理程序代码
	int j = 0;//行标号
	UpdateData(true);
	m_list.DeleteAllItems();//删除listview控件中的所有项
	int nRow;//插入行
	while (m_list.DeleteColumn(0));//删除所有列
	m_list.InsertColumn(0, "学号", LVCFMT_LEFT, 125);//插入列
	m_list.InsertColumn(1, "姓名", LVCFMT_LEFT, 55);
	m_list.InsertColumn(2, "出勤", LVCFMT_LEFT, 42);
	m_list.InsertColumn(3, "总计", LVCFMT_LEFT, 40);
	m_list.InsertColumn(4, "请假", LVCFMT_LEFT, 40);
	m_list.InsertColumn(5, "假次", LVCFMT_LEFT, 40);
	sprintf_s(sql_insert, "select %s.no,zb.name,%s.att,%s.sum,%s.leav,%s.lea from %s,zb where %s.no = zb.no", result1, result1, result1, result1, result1, result1, result1);
	if (mysql_query(&mysql, sql_insert))
	{
		//AfxMessageBox(mysql_error(&mysql));
		MessageBox("数据库查询发生错误!", "Error", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);// 获得结果集         
		if (mysql_num_rows(resultset) != NULL)
		{
			int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
			int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
			while (row = mysql_fetch_row(resultset))
			{
				int i = 0;
				nRow = m_list.InsertItem(j, "0");
				for (i = 0; i < numFields; i++)
				{

					m_list.SetItemText(nRow, i, row[i]);//设置数据
				}
				j++;
				m_list.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
			}
		}
		else
		{
			MessageBox("没有数据!", "错误", MB_OK);
		}
		mysql_free_result(resultset);  // 释放结果集
	}
	UpdateData(false);
}



void CMainInterface::OnButtonTJ()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	int j = 0;
	int jj = 0;  //勾选的人数
	int jjj = 0;  //总记录数
	int jjjj = 0;  //记录请假数
	char sql_insert[200];
	for (int i = 0; i <m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_list.GetCheck(i)) //这个是某行选中  //这个是前面的checkbox被选中 
		{
			sprintf_s(sql_insert, "update %s,zb set %s.att = 1 where %s.no = zb.no and %s.id = '%d';", result1, result1, result1, result1, i + 1);
			mysql_query(&mysql, sql_insert);
			j++;
		}
	}
	//按钮bug修正
	sprintf_s(sql_insert, "select * from %s,zb where %s.no = zb.no;", result1, result1);  //总人数
	if (mysql_query(&mysql, sql_insert))
	{
		MessageBox("数据库查询错误", "统计失败", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(resultset))
		{
			jjj++;
		}
		sprintf_s(sql_insert, "select * from %s where leav = 1;", result1); //请假人数
		mysql_query(&mysql, sql_insert);
		resultset = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(resultset))
		{
			jjjj++;
		}
		sprintf_s(sql_insert, "select * from zb,%s where %s.no = zb.no and %s.att = 1;", result1, result1, result1);
		mysql_query(&mysql, sql_insert);
		resultset = mysql_store_result(&mysql);
		if ((mysql_num_rows(resultset) != NULL) && (j == 0))  //没有勾选并且att中有数据  //未到名单有问题
		{
			while (row = mysql_fetch_row(resultset))
			{
				jj++;
			}
			str.Format(_T("本节次共有 %d 人\n其中有 %d 同学未到\n有 %d 人请假\n出勤率为%.1lf%%"), jjj, jjj - jj, jjjj, double(jj) / double(jjj) * 100);

		}
		else
		{
			str.Format(_T("本节次共有 %d 人\n其中有 %d 同学未到\n有 %d 人请假\n出勤率为%.1lf%%"), jjj, jjj - j, jjjj, double(j) / double(jjj) * 100);
		}
		MessageBox(str, "统计信息", MB_OK);
	}
}


void CMainInterface::OnButtonGm()
{
	// TODO:  在此添加控件通知处理程序代码

	this->ShowWindow(SW_HIDE);//隐藏登入窗口
	CGM dlg;//定义主界面窗口类对象
	dlg.DoModal();//以模态形式显示一个窗口
	this->ShowWindow(SW_SHOW);
}



void CMainInterface::OnButtonYd()
{
	// TODO:  在此添加控件通知处理程序代码
	int j = 0;
//	int nRow ;//插入行
	int flag=0;
	CString info;
	char sql_insert[200];
	UpdateData(true);
	sprintf_s(sql_insert, "select %s.no,zb.name,%s.att from zb,%s where %s.no = zb.no", result1, result1, result1, result1);
	if (mysql_query(&mysql, sql_insert))
		{
			MessageBox("数据库查询发生错误!", "Error", MB_OK);
		}
	else
		{                           
           resultset = mysql_store_result(&mysql);// 获得结果集         
           if (mysql_num_rows(resultset) != NULL)
           {
				int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
				int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
                while (row = mysql_fetch_row(resultset))
                {
					int i = 0;
				//	nRow = m_list.InsertItem(j, "");
					CString TEMP = _T("\t");
					CString TEMP1 = _T("\t修改成功");
					for (i = 0; i< numFields; i++)
                    {
                        if((row[i]==m_xgData))//||(row[i]==m_edit_name)
						{
							flag=1;
							sprintf_s(sql_insert, "update %s set %s.att = 1 where %s.no = %s;", result1, result1, result1, m_xgData);
							mysql_query(&mysql, sql_insert);
							if (row[i] == m_xgData)
							{
								info = (CString)row[i] + TEMP + (CString)row[i + 1] + TEMP1;
							}
							else
							{
								info = (CString)row[i - 2] + TEMP + (CString)row[i - 1] + TEMP1;
							}
							MessageBox(info,"修改成功", MB_OK);
						}
                    }
                    j++;					
                 }
				if(flag==0)
					{
						MessageBox("未找到此学号!!","修改失败", MB_OK);
					}
			}
			else
			{
				 MessageBox("没有数据!", "错误", MB_OK);
			} 
			mysql_free_result(resultset);  // 释放结果集
		}
		UpdateData(false);
		OnButtonDm();   //点击显示名单
}


void CMainInterface::OnButtonWd()
{
	// TODO:  在此添加控件通知处理程序代码
	int j = 0;
	//	int nRow ;//插入行
	int flag = 0;
	CString info;
	char sql_insert[200];
	UpdateData(true);
	sprintf_s(sql_insert, "select %s.no,zb.name,%s.att from zb,%s where %s.no = zb.no", result1, result1, result1, result1);
	if (mysql_query(&mysql, sql_insert))
	{
		MessageBox("数据库查询发生错误!", "Error", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);// 获得结果集         
		if (mysql_num_rows(resultset) != NULL)
		{
			int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
			int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
			while (row = mysql_fetch_row(resultset))
			{
				int i = 0;
				//	nRow = m_list.InsertItem(j, "");
				CString TEMP = _T("\t");
				CString TEMP1 = _T("\t修改成功");
				for (i = 0; i< numFields; i++)
				{
					if ((row[i] == m_xgData))//||(row[i]==m_edit_name)
					{
						flag = 1;
						sprintf_s(sql_insert, "update %s set %s.att = 0 where %s.no = %s;", result1, result1, result1, m_xgData);
						mysql_query(&mysql, sql_insert);
						if (row[i] == m_xgData)
						{
							info = (CString)row[i] + TEMP + (CString)row[i + 1] + TEMP1;
						}
						else
						{
							info = (CString)row[i - 2] + TEMP + (CString)row[i - 1] + TEMP1;
						}
						MessageBox(info, "修改成功", MB_OK);
					}
				}
				j++;
			}
			if (flag == 0)
			{
				MessageBox("未找到此学号!!", "修改失败", MB_OK);
			}
		}
		else
		{
			MessageBox("没有数据!", "错误", MB_OK);
		}
		mysql_free_result(resultset);  // 释放结果集
	}
	UpdateData(false);
	OnButtonDm();   //点击显示名单
}


void CMainInterface::OnButtonQj()
{
	// TODO:  在此添加控件通知处理程序代码
	int j = 0;
	//	int nRow ;//插入行
	int flag = 0;
	CString info;
	char sql_insert[200];
	UpdateData(true);
	sprintf_s(sql_insert, "select %s.no,zb.name,%s.att from zb,%s where %s.no = zb.no", result1, result1, result1, result1);
	if (mysql_query(&mysql, sql_insert))
	{
		MessageBox("数据库查询发生错误!", "Error", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);// 获得结果集         
		if (mysql_num_rows(resultset) != NULL)
		{
			int numRows = (int)mysql_num_rows(resultset); // 获得结果集中的记录数
			int numFields = (int)mysql_num_fields(resultset);// 获得表中字段数
			while (row = mysql_fetch_row(resultset))
			{
				int i = 0;
				//	nRow = m_list.InsertItem(j, "");
				CString TEMP = _T("\t");
				CString TEMP1 = _T("\t修改成功");
				for (i = 0; i< numFields; i++)
				{
					if ((row[i] == m_xgData))//||(row[i]==m_edit_name)
					{
						flag = 1;
						sprintf_s(sql_insert, "update %s set %s.leav = 1 where %s.no = %s;", result1, result1, result1, m_xgData);
						mysql_query(&mysql, sql_insert);
						if (row[i] == m_xgData)
						{
							info = (CString)row[i] + TEMP + (CString)row[i + 1] + TEMP1;
						}
						else
						{
							info = (CString)row[i - 2] + TEMP + (CString)row[i - 1] + TEMP1;
						}
						MessageBox(info, "修改成功", MB_OK);
					}
				}
				j++;
			}
			if (flag == 0)
			{
				MessageBox("未找到此学号!!", "修改失败", MB_OK);
			}
		}
		else
		{
			MessageBox("没有数据!", "错误", MB_OK);
		}
		mysql_free_result(resultset);  // 释放结果集
	}
	UpdateData(false);
	OnButtonDm();   //点击显示名单
}



void CMainInterface::OnButtonCj()
{
	// TODO:  在此添加控件通知处理程序代码

	this->ShowWindow(SW_HIDE);//隐藏登入窗口
	CBZC dlg;//定义主界面窗口类对象
	dlg.DoModal();//以模态形式显示一个窗口
	this->ShowWindow(SW_SHOW);
}

