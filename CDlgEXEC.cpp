// CDlgEXEC.cpp: 实现文件
//

#include "pch.h"
#include "放马问题 可视化.h"
#include "afxdialogex.h"
#include "CDlgEXEC.h"


// CDlgEXEC 对话框

IMPLEMENT_DYNAMIC(CDlgEXEC, CDialogEx)

CDlgEXEC::CDlgEXEC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXEC, pParent)
{
	by = 1;
	bx = 1;
	horse_num = 1;
}

CDlgEXEC::~CDlgEXEC()
{
}

void CDlgEXEC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT, m_text_num);
}


BEGIN_MESSAGE_MAP(CDlgEXEC, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CDlgEXEC::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgEXEC 消息处理程序

BOOL CDlgEXEC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString csnum;
	csnum.Format(TEXT("可以放置马的最大数量为 %d"), horse_num);
	m_text_num.SetWindowTextW(csnum);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgEXEC::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()


	
	
	//准备画笔以及参数
	//画棋盘
	CDC* pdc;
	pdc = GetDC();
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldpen = pdc->SelectObject(&pen);//获取指针
	//强调棋盘
	CDC* pdc1;
	pdc1 = GetDC();
	CPen pen1(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* pOldpen1 = pdc1->SelectObject(&pen1);//获取指针
	int Ox = 50;
	int Oy = 80;
	int numx = 8;//行数
	int numy = 8;//列数 
	


	//棋盘外放框
	for (int i = 0; i < 2; i++)
	{
		pdc->MoveTo(Ox - 25 + numx * 55 * i, Oy - 30);
		pdc->LineTo(Ox - 25 + numx * 55 * i, Oy + 10 + 50 * numy);
		pdc->MoveTo(Ox - 25 , Oy - 30 + numx * 55 * i);
		pdc->LineTo(Ox + 15 + 50 * numx, Oy - 30 + numx * 55 * i);
	}



	//棋盘坐标参数
	dc.TextOutW(Ox + 20 + 0 * 50, Oy - 25, TEXT("A"));
	dc.TextOutW(Ox + 20 + 1 * 50, Oy - 25, TEXT("B"));
	dc.TextOutW(Ox + 20 + 2 * 50, Oy - 25, TEXT("C"));
	dc.TextOutW(Ox + 20 + 3 * 50, Oy - 25, TEXT("D"));
	dc.TextOutW(Ox + 20 + 4 * 50, Oy - 25, TEXT("E"));
	dc.TextOutW(Ox + 20 + 5 * 50, Oy - 25, TEXT("F"));
	dc.TextOutW(Ox + 20 + 6 * 50, Oy - 25, TEXT("G"));
	dc.TextOutW(Ox + 20 + 7 * 50, Oy - 25, TEXT("H"));

	dc.TextOutW(Ox - 20, Oy + 15 + 0 * 50, TEXT("1"));
	dc.TextOutW(Ox - 20, Oy + 15 + 1 * 50, TEXT("2"));
	dc.TextOutW(Ox - 20, Oy + 15 + 2 * 50, TEXT("3"));
	dc.TextOutW(Ox - 20, Oy + 15 + 3 * 50, TEXT("4"));
	dc.TextOutW(Ox - 20, Oy + 15 + 4 * 50, TEXT("5"));
	dc.TextOutW(Ox - 20, Oy + 15 + 5 * 50, TEXT("6"));
	dc.TextOutW(Ox - 20, Oy + 15 + 6 * 50, TEXT("7"));
	dc.TextOutW(Ox - 20, Oy + 15 + 7 * 50, TEXT("8"));

	
	
	//颜色填充
	CBrush brush1(RGB(119, 162, 109));
	for (int n = 0; n < numy; n += 1)
	{
		for (int m = (n % 2 == 0) ? 0 : 1; m < numx; m += 2)
		{
			CRect rc(Ox + 50 * m, Oy + n * 50, Ox + 50 + 50 * m, Oy + 50 + n * 50);
			pdc->FillRect(rc, &brush1);
		}
	}
	CBrush brush2(RGB(200, 196, 109));
	for (int n = 0; n < numy; n += 1)
	{
		for (int m = (n % 2 == 0) ? 1 : 0; m < numx; m += 2)
		{
			CRect rc(Ox + 50 * m, Oy + n * 50, Ox + 50 + 50 * m, Oy + 50 + n * 50);
			pdc->FillRect(rc, &brush2);
		}
	}



	//绘制棋盘
	for (int i = 0; i <= numx; i++)//画列线
	{
		pdc->MoveTo(Ox + 50 * i, Oy);
		pdc->LineTo(Ox + 50 * i, Oy + 50 * numy);
	}
	for (int j = 0; j <= numy; j++)//画行线
	{
		pdc->MoveTo(Ox, Oy + 50 * j);
		pdc->LineTo(Ox + 50 * numx, Oy + 50 * j);
	}


	
	//绘制马的准备
	CDC   dcBmp1;             //定义并创建一个内存设备环境
	dcBmp1.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   horse1;
	horse1.LoadBitmap(IDB_BITMAP3);    //载入资源中图片
	BITMAP   m_bitmap1;                         //图片变量               
	horse1.GetBitmap(&m_bitmap1);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap* pbmpOld1 = dcBmp1.SelectObject(&horse1);

	CDC   dcBmp2;             //定义并创建一个内存设备环境
	dcBmp2.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);    //载入资源中图片
	BITMAP   m_bitmap2;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap2);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp2.SelectObject(&bmpBackground);

	
	
	//绘制马
	if (bx == 1)
	{
		for (int i = 0; i < by; i++)
		{
			//调用函数显示图片StretchBlt显示形状可变
			if (i % 2 == 0)
				dc.StretchBlt(Ox + 10, Oy + 10 + i * 50, 30, 30, &dcBmp1, 0, 0, m_bitmap1.bmWidth, m_bitmap1.bmHeight, SRCCOPY);
			else 
				dc.StretchBlt(Ox + 10, Oy + 10 + i * 50, 30, 30, &dcBmp2, 0, 0, m_bitmap2.bmWidth, m_bitmap2.bmHeight, SRCCOPY);
		}
	}
	else if (by == 1)
	{
		for (int i = 0; i < bx; i++)
		{
			if (i % 2 == 0)
				dc.StretchBlt(Ox + 10 + i * 50, Oy + 10 , 30, 30, &dcBmp1, 0, 0, m_bitmap1.bmWidth, m_bitmap1.bmHeight, SRCCOPY);
			else
				dc.StretchBlt(Ox + 10 + i * 50, Oy + 10 , 30, 30, &dcBmp2, 0, 0, m_bitmap2.bmWidth, m_bitmap2.bmHeight, SRCCOPY);
		}
	}
	else if (bx == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < by; j++)
			{
				if (j % 4 == 0 || j % 4 == 1)
				{
					if ((i + j) % 2 == 0)
						dc.StretchBlt(Ox + 10 + i * 50, Oy + 10 + j * 50, 30, 30, &dcBmp1, 0, 0, m_bitmap1.bmWidth, m_bitmap1.bmHeight, SRCCOPY);
					else
						dc.StretchBlt(Ox + 10 + i * 50, Oy + 10 + j * 50, 30, 30, &dcBmp2, 0, 0, m_bitmap2.bmWidth, m_bitmap2.bmHeight, SRCCOPY);
				}
			}

		}
	}
	else if (by == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < bx; j++)
			{
				if (j % 4 == 0 || j % 4 == 1)
				{
					if ((i + j) % 2 == 0)
						dc.StretchBlt(Ox + 10 + j * 50, Oy + 10 + i * 50, 30, 30, &dcBmp1, 0, 0, m_bitmap1.bmWidth, m_bitmap1.bmHeight, SRCCOPY);
					else
						dc.StretchBlt(Ox + 10 + j * 50, Oy + 10 + i * 50, 30, 30, &dcBmp2, 0, 0, m_bitmap2.bmWidth, m_bitmap2.bmHeight, SRCCOPY);
				}
			}

		}
	}
	else
	{
		for (int i = 0; i < by; i++)
		{
			for (int j = 0; j < bx; j++)
			{
				if ((i + j) % 2 == 0)
					dc.StretchBlt(Ox + 10 + j * 50, Oy + 10 + i * 50, 30, 30, &dcBmp1, 0, 0, m_bitmap1.bmWidth, m_bitmap1.bmHeight, SRCCOPY);
			}

		}
	}

	//强调线
	pdc1->MoveTo(Ox + 50 * (bx), Oy);
	pdc1->LineTo(Ox + 50 * (bx), Oy + 50 * (by));
	pdc1->MoveTo(Ox, Oy + 50 * (by));
	pdc1->LineTo(Ox + 50 * (bx), Oy + 50 * (by));

	ReleaseDC(pdc);
	ReleaseDC(pdc1);
}

void CDlgEXEC::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

