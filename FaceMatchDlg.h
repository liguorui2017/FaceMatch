
// FaceMatchDlg.h : 头文件
//

#pragma once
#include "opencv2\core\core.hpp"  
#include "opencv2\highgui\highgui.hpp"  
#include "opencv2\imgproc\imgproc.hpp"  
#include "opencv2\contrib\contrib.hpp"  
#include <fstream>  
#include <cstring>  
#include <cstdlib>  
#include <cmath>  
#include <algorithm> 
#include <cstdio>  
#include <vector>  
#include <iostream> 

#include "ReminderDlg.h"


// CFaceMatchDlg 对话框
class CFaceMatchDlg : public CDialogEx
{
// 构造
public:
	CFaceMatchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FACEMATCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenButton();
	afx_msg void OnBnClickedMatchButton();
};
