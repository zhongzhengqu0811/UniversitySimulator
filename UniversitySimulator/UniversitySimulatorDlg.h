
// UniversitySimulatorDlg.h: 头文件
//

#pragma once


// CUniversitySimulatorDlg 对话框
class CUniversitySimulatorDlg : public CDialogEx
{
// 构造
public:
	CUniversitySimulatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNIVERSITYSIMULATOR_DIALOG };
#endif

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
	void UpdateAllData();
	CListBox m_ctrlRecentTransactions;
	CListCtrl m_ctrlStudentList;
	CListCtrl m_ctrlStaffList;
	afx_msg void OnBnClickedHireStaff();
	afx_msg void OnBnClickedWithdrawStudent();
	afx_msg void OnBnClickedContinue();
	afx_msg void OnBnClickedFireStaff();
	afx_msg void OnClose();
	afx_msg void OnBnClickedAuto();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedExpand();
	afx_msg void OnBnClickedViewFinances();
};
