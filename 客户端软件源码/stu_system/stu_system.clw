; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainInterface
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "stu_system.h"

ClassCount=4
Class1=CStu_systemApp
Class2=CStu_systemDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_STU_SYSTEM_DIALOG
Class4=CMainInterface
Resource4=IDD_MAIN_INTERFACE

[CLS:CStu_systemApp]
Type=0
HeaderFile=stu_system.h
ImplementationFile=stu_system.cpp
Filter=N

[CLS:CStu_systemDlg]
Type=0
HeaderFile=stu_systemDlg.h
ImplementationFile=stu_systemDlg.cpp
Filter=D
LastObject=CStu_systemDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=stu_systemDlg.h
ImplementationFile=stu_systemDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_STU_SYSTEM_DIALOG]
Type=1
Class=CStu_systemDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308353
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_USERNAME,edit,1350631552
Control4=IDC_EDIT_PASSWORD,edit,1350631552
Control5=IDC_LOGIN,button,1342242816
Control6=IDC_EXIT,button,1342242816

[DLG:IDD_MAIN_INTERFACE]
Type=1
Class=CMainInterface
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_FIND_BUTTON,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_NUM,edit,1350631552
Control7=IDC_EDIT_NAME,edit,1350631552
Control8=IDC_DELETE_BUTTON,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_ADD_NUM,edit,1350631552
Control12=IDC_ADD_NAME,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_ADD_SEX,edit,1350631552
Control16=IDC_ADD_PHONE,edit,1350631552
Control17=IDC_ADD_BUTTON,button,1342242816
Control18=IDC_EXPORT,button,1342242816
Control19=IDC_DISPLAY,button,1342242816
Control20=IDC_EXIT_SYSTEM,button,1342242816
Control21=IDC_LIST_DISPLAY,SysListView32,1350631425

[CLS:CMainInterface]
Type=0
HeaderFile=MainInterface.h
ImplementationFile=MainInterface.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_NUM

