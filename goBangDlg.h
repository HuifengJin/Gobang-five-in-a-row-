
// goBangDlg.h : 头文件
//

#pragma once


// CgoBangDlg 对话框
class CgoBangDlg : public CDialogEx
{
// 构造
public:
	CgoBangDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GOBANG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	CBitmap m_chessP;
	CBitmap m_chessB;
	CBitmap m_chessH;
	bool    m_odd;
	int map[15][15]; //0:空,1:黑,2:白
	int chessnum;

	CPoint CrossOver(int b_or_H,CPoint point);
	int chesswin();

	

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
	afx_msg void OnExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
