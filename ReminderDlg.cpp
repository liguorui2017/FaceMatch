// ReminderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FaceMatch.h"
#include "ReminderDlg.h"
#include "afxdialogex.h"


// CReminderDlg 对话框

IMPLEMENT_DYNAMIC(CReminderDlg, CDialogEx)

CReminderDlg::CReminderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReminderDlg::IDD, pParent)
{

}

CReminderDlg::~CReminderDlg()
{
}

void CReminderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReminderDlg, CDialogEx)
END_MESSAGE_MAP()


// CReminderDlg 消息处理程序
