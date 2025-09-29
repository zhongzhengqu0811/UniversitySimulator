// CFinances.cpp: 实现文件
//

#include "pch.h"
#include "UniversitySimulator.h"
#include "CFinances.h"
#include "afxdialogex.h"
#include "University.h"
extern University univ;
string moneyToString(long long);

// CFinances 对话框

IMPLEMENT_DYNAMIC(CFinances, CDialogEx)

CFinances::CFinances(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CFinances::~CFinances()
{
}

void CFinances::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlFinances);
}


BEGIN_MESSAGE_MAP(CFinances, CDialogEx)
END_MESSAGE_MAP()


// CFinances 消息处理程序


BOOL CFinances::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrlFinances.InsertColumn(0, "Year", LVCFMT_LEFT, 90);
	m_ctrlFinances.InsertColumn(1, "Tuition", LVCFMT_RIGHT, 145);
	m_ctrlFinances.InsertColumn(2, "Salaries", LVCFMT_RIGHT, 145);
	m_ctrlFinances.InsertColumn(3, "Running costs", LVCFMT_RIGHT, 145);
	m_ctrlFinances.InsertColumn(4, "Balance at year end", LVCFMT_RIGHT, 145);
	m_ctrlFinances.InsertColumn(5, "Profit", LVCFMT_RIGHT, 145);
	long long totalTuition = 0, totalSalary = 0, totalCost = 0;

	vector<financialRecord> financialRecords = univ.getFinancialRecords();
	financialRecord currentYearRecord = univ.getCurrentYearFinancialRecord();
	for (financialRecord r : financialRecords)
	{
		int nItem;
		CString currentYear;
		currentYear.Format("%d/%.2d", r.year - 1, r.year % 100);
		nItem = m_ctrlFinances.InsertItem(0, currentYear);
		m_ctrlFinances.SetItemText(nItem, 1, ("+" + moneyToString(r.tuition)).c_str());
		m_ctrlFinances.SetItemText(nItem, 2, ("-" + moneyToString(r.salary)).c_str());
		m_ctrlFinances.SetItemText(nItem, 3, ("-" + moneyToString(r.runningCost)).c_str());
		m_ctrlFinances.SetItemText(nItem, 4, moneyToString(r.money).c_str());
		long long profit = r.tuition - r.salary - r.runningCost;
		m_ctrlFinances.SetItemText(nItem, 5, moneyToString(profit).c_str());
		totalTuition += r.tuition;
		totalSalary += r.salary;
		totalCost += r.runningCost;
	}
#define r currentYearRecord
	CString currentYear;
	currentYear.Format("%d/%.2d*", r.year - 1, r.year % 100);
	int nItem = m_ctrlFinances.InsertItem(0, currentYear);
	m_ctrlFinances.SetItemText(nItem, 1, ("+" + moneyToString(r.tuition)).c_str());
	m_ctrlFinances.SetItemText(nItem, 2, ("-" + moneyToString(r.salary)).c_str());
	m_ctrlFinances.SetItemText(nItem, 3, ("-" + moneyToString(r.runningCost)).c_str());
	m_ctrlFinances.SetItemText(nItem, 4, moneyToString(r.money).c_str());
	long long profit = r.tuition - r.salary - r.runningCost;
	m_ctrlFinances.SetItemText(nItem, 5, moneyToString(profit).c_str());
	totalTuition += r.tuition;
	totalSalary += r.salary;
	totalCost += r.runningCost;
#undef r
	long long totalProfit = totalTuition - totalSalary - totalCost;
	SetDlgItemText(IDC_TUITION, moneyToString(totalTuition).c_str());
	SetDlgItemText(IDC_SALARY, ("-" + moneyToString(totalSalary)).c_str());
	SetDlgItemText(IDC_RUNNING_COST, ("-" + moneyToString(totalCost)).c_str());
	SetDlgItemText(IDC_PROFIT, ((totalProfit >= 0 ? "+" : "-") + moneyToString(totalProfit)).c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
