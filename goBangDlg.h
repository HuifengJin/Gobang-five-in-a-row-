
// goBangDlg.h : ͷ�ļ�
//

#pragma once


// CgoBangDlg �Ի���
class CgoBangDlg : public CDialogEx
{
// ����
public:
	CgoBangDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GOBANG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	CBitmap m_chessP;
	CBitmap m_chessB;
	CBitmap m_chessH;
	bool    m_odd;
	int map[15][15]; //0:��,1:��,2:��
	int chessnum;

	CPoint CrossOver(int b_or_H,CPoint point);
	int chesswin();

	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
