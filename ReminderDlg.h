#pragma once


// CReminderDlg �Ի���

class CReminderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReminderDlg)

public:
	CReminderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReminderDlg();

// �Ի�������
	enum { IDD = IDD_REMINDER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
