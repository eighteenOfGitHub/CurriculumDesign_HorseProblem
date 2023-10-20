#pragma once
#include "afxdialogex.h"


// CDlgEXEC 对话框

class CDlgEXEC : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEXEC)

public:
	CDlgEXEC(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgEXEC();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXEC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	int bx;//board_x
	int by;//board_y
	int horse_num;
private:
	CStatic m_text_num;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
