#pragma once


// CExpand 对话框

class CExpand : public CDialogEx
{
	DECLARE_DYNAMIC(CExpand)

public:
	CExpand(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CExpand();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_intPlacesToAdd;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangePlaces();
	afx_msg void OnBnClickedOk();
};
