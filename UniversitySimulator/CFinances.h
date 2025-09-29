#pragma once


// CFinances 对话框

class CFinances : public CDialogEx
{
	DECLARE_DYNAMIC(CFinances)

public:
	CFinances(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFinances();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctrlFinances;
};
