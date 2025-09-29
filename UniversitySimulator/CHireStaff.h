#pragma once


// CHireStaff 对话框

class CHireStaff : public CDialogEx
{
	DECLARE_DYNAMIC(CHireStaff)

public:
	CHireStaff(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHireStaff();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlCandidateList;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
