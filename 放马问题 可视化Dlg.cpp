
// 放马问题 可视化Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "放马问题 可视化.h"
#include "放马问题 可视化Dlg.h"
#include "afxdialogex.h"
#include "CDlgEXEC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C放马问题可视化Dlg 对话框



C放马问题可视化Dlg::C放马问题可视化Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD___DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);//图标
}

void C放马问题可视化Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbx);
	DDX_Control(pDX, IDC_EDITy, m_y);
	DDX_Control(pDX, IDC_EDITx, m_x);
	DDX_Control(pDX, IDC_TEXT, m_pic);
}

BEGIN_MESSAGE_MAP(C放马问题可视化Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_KEYDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, &C放马问题可视化Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &C放马问题可视化Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C放马问题可视化Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C放马问题可视化Dlg 消息处理程序

BOOL C放马问题可视化Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	// 主窗口初始化
	//-----------------------------------------------------------

	
	//图片加载
	//设置静态控件窗口风格为位图居中显示
	m_pic.ModifyStyle(0xf, SS_BITMAP/*显示为图片*/ | SS_CENTERIMAGE/*居中显示*/);

	//通过路径获取bitmap句柄
#define HBMP(filepath,width,height) (HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	//参数（地址，宽度，高度） 后面就是实现

	// 获取文本框的宽高
	CRect rect;
	m_pic.GetWindowRect(rect);
	//静态控件设置bitmap
	m_pic.SetBitmap(HBMP(TEXT("./1.bmp"), rect.Width(), rect.Height()));
	// ./ 的意思上一个文件，这两个值应该为文本框的大小



	//下拉框初始化
	m_cbx.AddString(TEXT("1 * n"));
	m_cbx.AddString(TEXT("m * 1"));
	m_cbx.AddString(TEXT("2 * n"));
	m_cbx.AddString(TEXT("m * 2"));
	m_cbx.AddString(TEXT("m * n"));
	m_cbx.SetCurSel(4);//设置默认选项

	
	
	//编辑框初始化
	m_x.SetWindowText(TEXT("8"));
	m_y.SetWindowText(TEXT("8"));

	//-----------------------------------------------------------
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C放马问题可视化Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C放马问题可视化Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C放马问题可视化Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//控件相关函数
//-----------------------------------------------------------

//左键显示鼠标位置，绘图时方便记录信息，完成作业后会注释掉
//void C放马问题可视化Dlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CString str;
//	str.Format(TEXT("x = % d, y = % d"), point.x, point.y);
//	MessageBox(str);
//	CDialogEx::OnLButtonDown(nFlags, point);
//}

void C放马问题可视化Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}

void C放马问题可视化Dlg::OnCbnSelchangeCombo1()
{
	//下拉框选项点击事件
	int index = m_cbx.GetCurSel();
	switch (index)
	{
	case 0:
		//设置编辑框内容
		m_x.SetWindowText(TEXT("0"));
		m_y.SetWindowText(TEXT("1"));
		//编辑框可写状态
		m_x.SetReadOnly(FALSE);//可写
		m_y.SetReadOnly(TRUE);//不可写
		break;
	case 1:
		m_x.SetWindowText(TEXT("1"));
		m_y.SetWindowText(TEXT("0"));
		m_x.SetReadOnly(TRUE);
		m_y.SetReadOnly(FALSE);
		break;
	case 2:
		m_x.SetWindowText(TEXT("0"));
		m_y.SetWindowText(TEXT("2"));
		m_x.SetReadOnly(FALSE);
		m_y.SetReadOnly(TRUE);
		break;
	case 3:
		m_x.SetWindowText(TEXT("2"));
		m_y.SetWindowText(TEXT("0"));
		m_x.SetReadOnly(TRUE);//不可写
		m_y.SetReadOnly(FALSE);//可写
		break;
	case 4:
		m_x.SetWindowText(TEXT("8"));
		m_y.SetWindowText(TEXT("8"));
		m_x.SetReadOnly(FALSE);
		m_y.SetReadOnly(FALSE);
		break;
	}
}

//CString转化为int 函数
int CString_int(CEdit* m_n)
{
	CString nn;
	m_n->GetWindowText(nn);
	return _ttoi(nn);
}

int getnum(int x, int y);

//显示结果按钮
void C放马问题可视化Dlg::OnBnClickedButton1()
{
	//CString转化为int类型
	int x = CString_int(&m_x);//列数
	int y = CString_int(&m_y);//行数
	if ( x < 1  || y < 1 || x > 8 || y > 8)
	{
		MessageBox(TEXT("输入错误！请输入1~8之间的整数。"),TEXT("错误"), MB_ICONHAND);
	}
	else
	{
		CDlgEXEC dlg;
		//初始化绘制棋盘所需要的参数
		dlg.bx = x;
		dlg.by = y;
		int num = getnum(x, y);
		dlg.horse_num = getnum(x, y);
		//打开显示结果子窗口
		dlg.DoModal();
	}
}

//退出按钮
void C放马问题可视化Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("确定要退出程序吗？"), _T("温馨提示"), MB_OKCANCEL) == IDOK)
		PostQuitMessage(0);
	//exit(0);//退出程序
}

int getnum(int x, int y)//三种情况
{
	//情况一：只有一行或只有一列
	if (x == 1 || y == 1)
	{
		return x * y;
	}
	//情况二：只有二行或只有二列
	else if (y == 2)
	{
		if (x == 2 && y == 2)
			return 4;
		else
		{
			if (x % 4 == 2 || x % 4 == 3) return 2 * 2 * (x / 4 + 1);
			else if (x % 4 == 0) return 2 * 2 * (x / 4);
			else return 2 * (2 * (x / 4) + 1);
		}
	}
	else if (x == 2)//轮换对称
	{
		return getnum(y, x);
	}
	//情况三：大于二行或大于二列
	else
	{
		int n = x * y;//格子总数
		return (n % 2 == 0) ? n / 2 : n / 2 + 1;
	}
}
