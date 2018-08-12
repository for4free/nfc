// BZC.cpp : 实现文件
//

#include "stdafx.h"
#include "stu_system.h"
#include "BZC.h"
#include "afxdialogex.h"
#include "usersql.h" 
#include "goblextern.h"
#include <afxdb.h>
#include "MainInterface.h"
#include <Windowsx.h>
// CBZC 对话框

IMPLEMENT_DYNAMIC(CBZC, CDialogEx)

CBZC::CBZC(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBZC::IDD, pParent)
{

}

CBZC::~CBZC()
{
}

void CBZC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BM, m_mdData2);
}


BEGIN_MESSAGE_MAP(CBZC, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TCHU, &CBZC::OnButtonTchu)
	ON_BN_CLICKED(IDC_BUTTON_DCH, &CBZC::OnButtonDch)
	ON_BN_CLICKED(IDC_BUTTON_SCH, &CBZC::OnButtonSch)
	ON_BN_CLICKED(IDC_BUTTON_CHJ, &CBZC::OnButtonChj)
END_MESSAGE_MAP()


// CBZC 消息处理程序


void CBZC::OnButtonTchu()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}


void CBZC::OnButtonDch()
{
	// TODO:  在此添加控件通知处理程序代码
	//先列表 //
	CString m_bmData;
	
	m_mdData2.GetWindowText(m_bmData);   //获取值，有点不解
	char sql_insert[200];
	sprintf_s(sql_insert, "select * from dyb where bm = '%s' and id = '%s'", m_bmData, user);
	if (mysql_query(&mysql, sql_insert))
	{
		MessageBox("数据库查询发生错误!", "Error", MB_OK);
	}
	else
	{
		resultset = mysql_store_result(&mysql);// 获得结果集   
		if (mysql_num_rows(resultset) != NULL)
		{

			int j = 0;//行标号
			UpdateData(true);
			//char sql_insert[200];
			m_list.DeleteAllItems();//删除listview控件中的所有项
			int nRow;//插入行
			while (m_list.DeleteColumn(0));//删除所有列
			m_list.InsertColumn(0, "学号", LVCFMT_LEFT, 125);//插入列
			m_list.InsertColumn(1, "姓名", LVCFMT_LEFT, 55);
			m_list.InsertColumn(2, "请假次数", LVCFMT_LEFT, 85);
			m_list.InsertColumn(3, "出勤总计", LVCFMT_LEFT, 85);
			sprintf_s(sql_insert, "select %s.no,zb.name,%s.lea,%s.sum from %s,zb where %s.no = zb.no", m_bmData, m_bmData, m_bmData, m_bmData, m_bmData);
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
					mysql_free_result(resultset);  // 释放结果集
				}
				else
				{
					MessageBox("没有数据!", "错误", MB_OK);
				}
			}
			UpdateData(false);

			//首先判断列表框中是否有记录
			if (m_list.GetItemCount() <= 0)
			{
				AfxMessageBox("列表中没有记录需要保存！");
				return;
			}
			//打开另存为对话框 ，需要包含 #include <Afxdlgs.h>
			CFileDialog dlg(FALSE, "xls", "考勤信息统计表", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Excel 文件(*.xls)|*.xls||");
			dlg.m_ofn.lpstrTitle = "文件列表另存为";

			if (dlg.DoModal() != IDOK)
				return;
			CString strFilePath;
			//获得文件路径名
			strFilePath = dlg.GetPathName();
			//判断文件是否已经存在，存在则删除重建
			DWORD dwRe = GetFileAttributes(strFilePath);
			if (dwRe != (DWORD)-1)
			{
				DeleteFile(strFilePath);
			}

			CDatabase database;//数据库库需要包含头文件 #include <afxdb.h>
			CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel驱动
			CString sSql, strInsert;
			TRY
			{
				// 创建进行存取的字符串
				sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", sDriver, strFilePath, strFilePath);

				// 创建数据库 (既Excel表格文件)
				if (database.OpenEx(sSql, CDatabase::noOdbcDialog))
				{
					//获得列别框总列数
					int iColumnNum, iRowCount;
					LVCOLUMN lvCol;
					CString strColName; //用于保存列标题名称
					int i, j; //列、行循环参数

					iColumnNum = m_list.GetHeaderCtrl()->GetItemCount();
					iRowCount = m_list.GetItemCount();

					sSql = " CREATE TABLE DSO_DX ( ";
					strInsert = " INSERT INTO DSO_DX ( ";
					//获得列标题名称
					lvCol.mask = LVCF_TEXT; //必需设置，说明LVCOLUMN变量中pszText参数有效
					lvCol.cchTextMax = 32; //必设，pszText参数所指向的字符串的大小
					lvCol.pszText = strColName.GetBuffer(32); //必设，pszText 所指向的字符串的实际存储位置。
					//以上三个参数设置后才能通过 GetColumn()函数获得列标题的名称
					for (i = 0; i < iColumnNum; i++)
					{
						if (!(m_list.GetColumn(i, &lvCol)))
							return;
						if (i < iColumnNum - 1)
						{
							sSql = sSql + lvCol.pszText + " TEXT , ";
							strInsert = strInsert + lvCol.pszText + " , ";
						}
						else
						{
							sSql = sSql + lvCol.pszText + " TEXT ) ";
							strInsert = strInsert + lvCol.pszText + " )  VALUES ( ";
						}
					}
					//创建Excel表格文件
					database.ExecuteSQL(sSql);

					//循环提取记录并插入到EXCEL中
					sSql = strInsert;
					char chTemp[33];
					for (j = 0; j < iRowCount; j++)
					{
						memset(chTemp, 0, 33);
						for (i = 0; i < iColumnNum; i++)
						{
							m_list.GetItemText(j, i, chTemp, 33);
							if (i < (iColumnNum - 1))
							{
								sSql = sSql + "'" + chTemp + "' , ";
							}
							else
							{
								sSql = sSql + "'" + chTemp + "' ) ";
							}
						}
						//将记录插入到表格中
						database.ExecuteSQL(sSql);
						sSql = strInsert;
					}
				}

				// 关闭Excel表格文件
				database.Close();

				AfxMessageBox("保存查询结果为Excel文件成功！");
			}
				CATCH_ALL(e)
			{
				//错误类型很多，根据需要进行报错。
				AfxMessageBox("Excel文件保存失败。");
			}
			END_CATCH_ALL;
		}
		else
		{
			MessageBox("没有数据!", "错误", MB_OK);
		}
		

	}
}


void CBZC::OnButtonSch()
{
	// TODO:  在此添加控件通知处理程序代码
	//MessageBox(m_bmData, "错误", MB_OK);
	char sql_insert[200];
	CString m_bmData;
	
	m_mdData2.GetWindowText(m_bmData);   //获取值，有点不解
	if (MessageBox("确定删除表？！", "确定", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
		return;
	else
	{
		sprintf_s(sql_insert, "select * from dyb where bm = '%s' and id = '%s'", m_bmData, user);
		if (mysql_query(&mysql, sql_insert))
		{
			MessageBox("数据库查询发生错误!", "Error", MB_OK);
		}
		else
		{
			resultset = mysql_store_result(&mysql);// 获得结果集   
			if (mysql_num_rows(resultset) != NULL)
			{
				sprintf_s(sql_insert, "drop table %s;", m_bmData);  //删除表 暂且不用
				mysql_query(&mysql, sql_insert);
				sprintf_s(sql_insert, "delete from dyb where bm = '%s' and id = '%s';", m_bmData, user);   //删除对应表数据
				mysql_query(&mysql, sql_insert);
				MessageBox("删除成功！", "成功", MB_OK);
			}
			else
			{
				MessageBox("没有数据!", "错误", MB_OK);
			}
			mysql_free_result(resultset);
		}
	}
	m_mdData.ResetContent(); //清空列表
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
	int selectedPos = m_mdData.GetCurSel();
	m_mdData.GetLBText(selectedPos, result1);
}



void CBZC::OnButtonChj()   //创建表
{
	CString m_bmData;
	
	m_mdData2.GetWindowText(m_bmData);   //获取值，有点不解
	if (m_bmData == "")
	{
		MessageBox("请先输入表名!", "Error", MB_OK);
	}
	else
	{
		CString strSQL;
		strSQL.Format("select * from dyb where bm = '%s';", m_bmData);//注意一定要写在一行，而且必须要有/'/'
		if (mysql_query(&mysql, strSQL))
		{
			MessageBox("数据库查询发生错误!", "Error", MB_OK);
		}
		else
		{
			resultset = mysql_store_result(&mysql);// 获得结果集  
			if (mysql_num_rows(resultset) != NULL)
			{
				MessageBox("表名已存在!", "Error", MB_OK);
			}
			else
			{
				// TODO:  在此添加控件通知处理程序代码
				CFileDialog dlg(TRUE, //TRUE或FALSE。TRUE为打开文件；FALSE为保存文件
					"xls", //为缺省的扩展名
					NULL, //为显示在文件名组合框的编辑框的文件名，一般可选NULL
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//为对话框风格，一般为OFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,即隐藏只读选项和覆盖已有文件前提示。
					"Excel 文件(*.xls)|*.xls||"//为下拉列表枢中显示文件类型
					);
				dlg.m_ofn.lpstrTitle = "导入数据";
				if (dlg.DoModal() != IDOK)  //感觉没起作用
					return;
				CString strFilePath;
				//获得文件路径名
				strFilePath = dlg.GetPathName();
				//判断文件是否已经存在，存在则打开文件
				DWORD dwRe = GetFileAttributes(strFilePath);
				if (dwRe != (DWORD)-1)
				{
					//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE);
				}
				else return;
				CDatabase db;//数据库库需要包含头文件 #include <afxdb.h>
				CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel驱动
				CString sSql, arr[2];
				sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", sDriver, strFilePath, strFilePath);
				if (!db.OpenEx(sSql, CDatabase::noOdbcDialog))//连接数据源DJB．xls
				{
					MessageBox("打开EXCEL文件失败!", "错误");
					return;
				}
				//打开EXCEL表
				CRecordset pset(&db);
				m_list.DeleteAllItems();
				//AfxMessageBox("OK");
				//if (MessageBox("确定创建表?!", "确定"))
				if (MessageBox("确定创建表？！", "确定", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
					return;
				else
				{
					/* sSql = "SELECT 学号,姓名,成绩 "
					"FROM EXCELDEMO";      */
					// "ORDER BY 姓名";
					sSql.Format("SELECT * FROM DSO_DX");
					pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
					int idz = 1; //id自增
					strSQL.Format("insert into dyb (bm,id) values('%s','%s') ", m_bmData, user);//注意一定要写在一行，而且必须要有/'/'
					mysql_query(&mysql, strSQL);
					strSQL.Format("create table %s (id varchar(20),no varchar(20),att varchar(20),sum varchar(20),lea varchar(20),leav varchar(20));", m_bmData);//注意一定要写在一行，而且必须要有/'/'
					mysql_query(&mysql, strSQL);
					int sb = 0;
					int cg = 0;
					//读取第一个单元格的值
					while (!pset.IsEOF())
					{
						arr[0];
						pset.GetFieldValue("no", arr[0]);//前面字段必须与表中的相同，否则出错。
						int count = m_list.GetItemCount();//插入到ListCtrl中
						strSQL.Format("insert into %s (id,no) values(%d,'%s')", m_bmData, idz, arr[0]);//注意一定要写在一行，而且必须要有/'/'
						//mysql_real_query(&mysql, (char*)(LPCTSTR)strSQL, (UINT)strSQL.GetLength());
						if (mysql_real_query(&mysql, (char*)(LPCTSTR)strSQL, (UINT)strSQL.GetLength()) != 0)
						{
							sb++;
						}
						else
						{
							cg++;
						}
						idz++;
						pset.MoveNext();
					}
					db.Close();
					strSQL.Format("update %s set att=0,sum=0,lea=0,leav=0;", m_bmData);//初始化为0
					mysql_query(&mysql, strSQL);
					CString temp;
					temp.Format("成功导入 %d 条数据\n失败 %d 条", cg, sb);
					MessageBox(temp, "导入成功");
					//刷新主页面列表
					m_mdData.AddString(_T(m_bmData));
					//自适应高度
					CRect rc;
					m_mdData.SetCurSel(0);
					m_mdData.GetDroppedControlRect(&rc);
					m_mdData.GetParent()->ScreenToClient(&rc);
					rc.bottom += 150;
					m_mdData.MoveWindow(&rc);
					mysql_free_result(resultset);
					int selectedPos = m_mdData.GetCurSel();
					m_mdData.GetLBText(selectedPos, result1);
				}
			}
		}
	}
}
