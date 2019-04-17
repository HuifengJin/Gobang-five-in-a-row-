
// goBangDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "goBang.h"
#include "goBangDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CgoBangDlg 对话框




CgoBangDlg::CgoBangDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgoBangDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_odd = true;
	chessnum = 0;

	for(int i = 0; i < 15;i++)
	{
		for(int j = 0;j < 15;j++)
		{
			map[i][j] = 0;
		}
	}
}

void CgoBangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgoBangDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EXIT, &CgoBangDlg::OnExit)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CgoBangDlg 消息处理程序

BOOL CgoBangDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_chessP.LoadBitmapW(IDB_CHESSPANEL);
	m_chessB.LoadBitmapW(IDB_CHESSB);
	m_chessH.LoadBitmapW(IDB_CHESSH);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CgoBangDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgoBangDlg::OnPaint()
{
	static bool first = true;
	CPaintDC dc(this); // 用于绘制的设备上下文

	CDC memChessP;
	RECT rect;

/*	if(first)
	{
		first = false;
		CSize m_size = m_chessP.GetBitmapDimension();

		//CRect rect;
		GetClientRect(&rect);
		MoveWindow(rect.left,rect.top,m_size.cx,m_size.cy,true);//调整大小
	} */

	GetClientRect(&rect);

	memChessP.CreateCompatibleDC(&dc);
	memChessP.SelectObject(m_chessP);

	dc.BitBlt(rect.left,rect.top,rect.right,rect.bottom,
		&memChessP,0,0,SRCCOPY);

	CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgoBangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgoBangDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	::PostQuitMessage(0);
}


void CgoBangDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	
}

CPoint CgoBangDlg::CrossOver(int b_or_H,CPoint point)
{
	CPoint tmp_point;
	int pos_x0 = 25;
	int pos_y0 = 25;
	int step = 26;
	int i,j;

	for(i=0;i<15;i++)
	{		
		if((point.x - pos_x0) <= 13)
		{
			break;
		}
		else
			pos_x0 += 26;
	}

		for(j=0;j<15;j++)
	{
		if((point.y - pos_y0) <= 13)
		{
			break;
		}
		else
			pos_y0 += 26;
	}

	tmp_point.x = pos_x0;
	tmp_point.y = pos_y0;
	
	map[j][i] = b_or_H;

	return tmp_point;
}

int CgoBangDlg::chesswin()
{
	for(int i = 0; i < 11;i++)
	{
		for(int j = 0;j < 11;j++)
		{
			if(map[i][j] == 0)
				continue;
			if(map[i][j] == 1)
			{
				if(map[i][j+1] == 1 && map[i][j+2] == 1 && map[i][j+3] == 1 && map[i][j+4] == 1)
					return 1;
			}
			if(map[i][j] == 2)
			{
				if(map[i][j+1] == 2 && map[i][j+2] == 2 && map[i][j+3] == 2 && map[i][j+4] == 2)
					return 2;
			}
		}
	}

	for(int i = 0; i < 11;i++)
	{
		for(int j = 0;j < 11;j++)
		{
			if(map[i][j] == 0)
				continue;
			if(map[i][j] == 1)
			{
				if(map[i+1][j] == 1 && map[i+2][j] == 1 && map[i+3][j] == 1 && map[i+4][j] == 1)
					return 1;
			}
			if(map[i][j] == 2)
			{
				if(map[i+1][j] == 2 && map[i+2][j] == 2 && map[i+3][j] == 2 && map[i+4][j] == 2)
					return 2;
			}
		}
	}

	for(int i = 0; i < 11;i++)
	{
		for(int j = 0;j < 11;j++)
		{
			if(map[i][j] == 0)
				continue;
			if(map[i][j] == 1)
			{
				if(map[i+1][j+1] == 1 && map[i+2][j+2] == 1 && map[i+3][j+3] == 1 && map[i+4][j+4] == 1)
					return 1;
			}
			if(map[i][j] == 2)
			{
				if(map[i+1][j+1] == 2 && map[i+2][j+2] == 2 && map[i+3][j+3] == 2 && map[i+4][j+4] == 2)
					return 2;
			}
		}
	}

	return 0;
}


void CgoBangDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_odd)
	{
		CClientDC dc(this); // 用于绘制的设备上下文
		CDC memChessH;

		RECT rect;

		CPoint m_point = CrossOver(1,point);

		GetClientRect(&rect);

		memChessH.CreateCompatibleDC(&dc);
		memChessH.SelectObject(m_chessH);

		dc.BitBlt(m_point.x-12,m_point.y-12,24,24,
			&memChessH,0,0,SRCCOPY);

	}
	else
	{
		CClientDC dc(this); // 用于绘制的设备上下文
		CDC memChessB;

		RECT rect;

		CPoint m_point = CrossOver(2,point);

		GetClientRect(&rect);

		memChessB.CreateCompatibleDC(&dc);
		memChessB.SelectObject(m_chessB);

		dc.BitBlt(m_point.x-12,m_point.y-12,24,24,
			&memChessB,0,0,SRCCOPY);

	}

	m_odd = !m_odd;

	chessnum += 1;

	if(chessnum >= 9)
	{
		int m_win = chesswin();

		switch(m_win)
		{
			case 0:
				break;
			case 1:
				MessageBox(_T("黑子赢得比赛！"));
				break;
			case 2:
				MessageBox(_T("白子赢得比赛！"));
				break;
			default:
				break;
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
