// CHireStaff.cpp: 实现文件
//

#include "pch.h"
#include "UniversitySimulator.h"
#include "CHireStaff.h"
#include "afxdialogex.h"
#include "University.h"

vector<Staff> candidates;
Staff staffToBeHired;
extern University univ;
string moneyToString(long long);


// CHireStaff 对话框

IMPLEMENT_DYNAMIC(CHireStaff, CDialogEx)

CHireStaff::CHireStaff(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CHireStaff::~CHireStaff()
{
}

void CHireStaff::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlCandidateList);
}


BEGIN_MESSAGE_MAP(CHireStaff, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHireStaff::OnBnClickedOk)
END_MESSAGE_MAP()


// CHireStaff 消息处理程序


void CHireStaff::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int choice = m_ctrlCandidateList.GetSelectionMark();
	if (choice < 0)
	{
		AfxMessageBox("Please first choose a candidate to hire", MB_OK | MB_ICONSTOP);
		return;
	}
	staffToBeHired = candidates[choice];
	CDialogEx::OnOK();
}

#define m_ctrlStaffList m_ctrlCandidateList
BOOL CHireStaff::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrlStaffList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ctrlStaffList.InsertColumn(0, "Name", LVCFMT_LEFT, 170);
	m_ctrlStaffList.InsertColumn(1, "DOB", LVCFMT_RIGHT, 150);
	m_ctrlStaffList.InsertColumn(2, "Age", LVCFMT_RIGHT, 50);
	m_ctrlStaffList.InsertColumn(3, "Rating", LVCFMT_RIGHT, 180);
	m_ctrlStaffList.InsertColumn(4, "Salary", LVCFMT_RIGHT, 120);
	m_ctrlStaffList.DeleteAllItems();
	candidates.clear();

	for (int i = 0; i < 8; i++)
	{
		Staff st(univ.getDate());
		candidates.push_back(st);
	}
	for (int i = 7; i >= 0; i--)
	{
		Staff s = candidates[i];
		int nItem;
		nItem = m_ctrlStaffList.InsertItem(0, s.getName().c_str());
		m_ctrlStaffList.SetItemText(nItem, 1, s.dob().c_str());
		m_ctrlStaffList.SetItemText(nItem, 2, (to_string(s.getAge(univ.getDate())).c_str()));
		m_ctrlStaffList.SetItemText(nItem, 3, s.getRating().c_str());
		m_ctrlStaffList.SetItemText(nItem, 4, (moneyToString(s.getSalary())).c_str());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
#undef m_ctrlStaffList
