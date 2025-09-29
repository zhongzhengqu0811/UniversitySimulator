// CExpand.cpp: 实现文件
//

#include "pch.h"
#include "UniversitySimulator.h"
#include "CExpand.h"
#include "afxdialogex.h"
#include "University.h"
extern int placesToAdd;
string moneyToString(long long);
extern University univ;

// CExpand 对话框

IMPLEMENT_DYNAMIC(CExpand, CDialogEx)

CExpand::CExpand(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_intPlacesToAdd(0)
{

}

CExpand::~CExpand()
{
}

void CExpand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PLACES, m_intPlacesToAdd);
}


BEGIN_MESSAGE_MAP(CExpand, CDialogEx)
	ON_EN_CHANGE(IDC_PLACES, &CExpand::OnEnChangePlaces)
	ON_BN_CLICKED(IDOK, &CExpand::OnBnClickedOk)
END_MESSAGE_MAP()


// CExpand 消息处理程序


BOOL CExpand::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_intPlacesToAdd = 0;
	UpdateData(false);
	long long cost = placesToAdd * 100000.0 * inflation;
	SetDlgItemText(IDC_COST, moneyToString(cost).c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CExpand::OnEnChangePlaces()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString s;
	GetDlgItemText(IDC_COST, s);
	if (s.IsEmpty())
	{
		m_intPlacesToAdd = 0;
		UpdateData(false);
	}
	UpdateData();
	placesToAdd = m_intPlacesToAdd;
	long long cost = placesToAdd * 100000.0 * inflation;
	SetDlgItemText(IDC_COST, moneyToString(cost).c_str());
}


void CExpand::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	long long cost = placesToAdd * 100000.0 * inflation;
	if (placesToAdd == 0)
	{
		AfxMessageBox("Please add at least one place", MB_OK | MB_ICONSTOP);
		return;
	}
	if (univ.getUniversityFunds() < cost)
	{
		AfxMessageBox("Insufficient funds", MB_OK | MB_ICONSTOP);
		return;
	}
	CDialogEx::OnOK();
}
