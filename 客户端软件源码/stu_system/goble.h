//定义全局变量供多个窗口文件使用
MYSQL mysql;//定义一个数据库类对象
MYSQL_RES *resultset;//顶一个数据结果集类指针对象
MYSQL_ROW row;//数据库行数组

CString user;
CString pass;
CString result1;
CString ser1;
CListCtrl	m_list;
CComboBox m_mdData;