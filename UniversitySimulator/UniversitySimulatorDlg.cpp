
// UniversitySimulatorDlg.cpp: 实现文件
//

#include "pch.h"
#include <string>
int COHORT_SIZE = 10;
double inflation = 1;
int placesToAdd = 0;
#include "framework.h"
#include "UniversitySimulator.h"
#include "UniversitySimulatorDlg.h"
#include "University.h"
#include "afxdialogex.h"
#include "CHireStaff.h"
#include "CExpand.h"
#include "CFinances.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUniversitySimulatorDlg 对话框



CUniversitySimulatorDlg::CUniversitySimulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNIVERSITYSIMULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUniversitySimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RECENT_TRANSACTIONS, m_ctrlRecentTransactions);
	DDX_Control(pDX, IDC_STUDENT_LIST, m_ctrlStudentList);
	DDX_Control(pDX, IDC_STAFF_LIST, m_ctrlStaffList);
}

BEGIN_MESSAGE_MAP(CUniversitySimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HIRE_STAFF, &CUniversitySimulatorDlg::OnBnClickedHireStaff)
	ON_BN_CLICKED(IDC_WITHDRAW_STUDENT, &CUniversitySimulatorDlg::OnBnClickedWithdrawStudent)
	ON_BN_CLICKED(IDC_CONTINUE, &CUniversitySimulatorDlg::OnBnClickedContinue)
	ON_BN_CLICKED(IDC_FIRE_STAFF, &CUniversitySimulatorDlg::OnBnClickedFireStaff)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AUTO, &CUniversitySimulatorDlg::OnBnClickedAuto)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EXPAND, &CUniversitySimulatorDlg::OnBnClickedExpand)
	ON_BN_CLICKED(IDC_VIEW_FINANCES, &CUniversitySimulatorDlg::OnBnClickedViewFinances)
END_MESSAGE_MAP()

University univ;
extern vector<Staff> candidates;
extern Staff staffToBeHired;
bool automatic = false;
string moneyToString(long long money)
{
	return "￡" + fmt(money);
}
// CUniversitySimulatorDlg 消息处理程序

BOOL CUniversitySimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
//	srand(time(0));
	m_ctrlStudentList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ctrlStaffList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ctrlStudentList.InsertColumn(0, "Name", LVCFMT_LEFT, 180);
	m_ctrlStudentList.InsertColumn(1, "Year", LVCFMT_RIGHT, 50);
	m_ctrlStudentList.InsertColumn(2, "Enr", LVCFMT_RIGHT, 70);
	m_ctrlStudentList.InsertColumn(3, "Rep", LVCFMT_RIGHT, 50);
	m_ctrlStudentList.InsertColumn(4, "Grades/Projections", LVCFMT_LEFT, 400);

	m_ctrlStaffList.InsertColumn(0, "Name", LVCFMT_LEFT, 180);
	m_ctrlStaffList.InsertColumn(1, "DOB", LVCFMT_RIGHT, 120);
	m_ctrlStaffList.InsertColumn(2, "Age", LVCFMT_RIGHT, 50);
	m_ctrlStaffList.InsertColumn(3, "Rating", LVCFMT_RIGHT, 150);
	m_ctrlStaffList.InsertColumn(4, "Salary", LVCFMT_RIGHT, 120);
	m_ctrlStaffList.DeleteAllItems();

	static CFont m;
	m.CreatePointFont(400, "Trebuchet MS", 0);
	GetDlgItem(IDC_DATE)->SetFont(&m);

	UpdateAllData();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUniversitySimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUniversitySimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUniversitySimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUniversitySimulatorDlg::UpdateAllData()
{
	// TODO: 在此处添加实现代码.
	if(univ.getWeekNumber() == -1 && univ.getDate().getMonth() >= 5 && univ.getDate().getMonth() <= 8)
		SetDlgItemText(IDC_WEEK_NUMBER, "End of year");
	else if (univ.getWeekNumber() > 0)
		SetDlgItemText(IDC_WEEK_NUMBER, ("Week: " + to_string(univ.getWeekNumber())).c_str());
	else if (univ.getWeekNumber() == 0)
		SetDlgItemText(IDC_WEEK_NUMBER, "Welcome");
	else if (univ.getWeekNumber() == -1)
		SetDlgItemText(IDC_WEEK_NUMBER, "Vacation");
	else if (univ.getWeekNumber() == -2)
		SetDlgItemText(IDC_WEEK_NUMBER, "Exams");
	SetDlgItemText(IDC_MONEY, (moneyToString(univ.getUniversityFunds())).c_str());
	SetDlgItemText(IDC_DATE, to_string(univ.getDate().getDay()).c_str());
	static CString weekdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	static CString months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	SetDlgItemText(IDC_WEEKDAY, weekdays[univ.getDate().getDayOfWeek()]);
	SetDlgItemText(IDC_MONTHYEAR, (monthsShort[univ.getDate().getMonth() - 1] + " " + to_string(univ.getDate().getYear())).c_str());
	SetDlgItemText(IDC_FULL_DATE, univ.getDate().toFullString().c_str());
	SetDlgItemText(IDC_STUDENT_COUNT, (fmt(univ.getStudentCount()) + "/" + fmt(COHORT_SIZE)).c_str());
	SetDlgItemText(IDC_STAFF_COUNT, fmt(univ.getStaffCount()).c_str());
	SetDlgItemText(IDC_GRADUATE_COUNT, fmt(univ.getTotalGraduates()).c_str());
	SetDlgItemText(IDC_WITHDRAW_COUNT, fmt(univ.getTotalWithdrawals()).c_str());
	CString s;
	s.Format("1 : %.1f", univ.getStudentCount() / double(univ.getStaffCount()));
	SetDlgItemText(IDC_RATIO, s);

	m_ctrlStaffList.DeleteAllItems();
	m_ctrlStudentList.DeleteAllItems();
	vector<Staff> staff = univ.getStaffList();
	vector<Student> students = univ.getStudentList();
	for (Staff s : staff)
	{
		int nItem;
		nItem = m_ctrlStaffList.InsertItem(0, s.getName().c_str());
		m_ctrlStaffList.SetItemText(nItem, 1, s.dob().c_str());
		m_ctrlStaffList.SetItemText(nItem, 2, (to_string(s.getAge(univ.getDate())).c_str()));
		m_ctrlStaffList.SetItemText(nItem, 3, s.getRating().c_str());
		m_ctrlStaffList.SetItemText(nItem, 4, (moneyToString(s.getSalary())).c_str());
	}
	for (Student s : students)
	{
		int nItem;
		nItem = m_ctrlStudentList.InsertItem(0, s.getName().c_str());
		m_ctrlStudentList.SetItemText(nItem, 1, (to_string(s.getYear())).c_str());
		m_ctrlStudentList.SetItemText(nItem, 2, (to_string(s.getSince())).c_str());
		m_ctrlStudentList.SetItemText(nItem, 3, (s.isRepeatingYear() ? "Yes" : ""));
		m_ctrlStudentList.SetItemText(nItem, 4, s.getGradeStrings().c_str());
	}
}


void CUniversitySimulatorDlg::OnBnClickedHireStaff()
{
	// TODO: 在此添加控件通知处理程序代码
	/*Staff s(univ.getDate());
	univ.hireStaff(s);*/
	CHireStaff dlg;
	if (dlg.DoModal() == IDOK)
		univ.hireStaff(staffToBeHired);
	UpdateAllData();
}


void CUniversitySimulatorDlg::OnBnClickedWithdrawStudent()
{
	// TODO: 在此添加控件通知处理程序代码
	int choice = m_ctrlStudentList.GetSelectionMark();
	if (choice < 0)
	{
		AfxMessageBox("Please first select a student to withdraw", MB_OK | MB_ICONSTOP);
		return;
	}
	if (univ.getStudentCount() == 1)
	{
		AfxMessageBox("Cannot withdraw the last student", MB_OK | MB_ICONSTOP);
		return;
	}
	string name = m_ctrlStudentList.GetItemText(choice, 0);
	//	SetWindowText(name);
	int answer = AfxMessageBox(("Are you sure you want to withdraw " + name + "?").c_str(), MB_YESNO | MB_ICONEXCLAMATION);
	if (answer == IDYES) { univ.withdrawStudent(name); UpdateAllData(); }
	
}


void CUniversitySimulatorDlg::OnBnClickedContinue()
{
	// TODO: 在此添加控件通知处理程序代码
	if (univ.getStaffCount() == 0)
	{
		AfxMessageBox("You don't have staff in your university yet. Hire staff before continuing.", MB_OK | MB_ICONSTOP);
		return;
	}
	univ.advanceDate();
	UpdateAllData();
}


void CUniversitySimulatorDlg::OnBnClickedFireStaff()
{
	// TODO: 在此添加控件通知处理程序代码
	int choice = m_ctrlStaffList.GetSelectionMark();
	if (choice < 0)
	{
		AfxMessageBox("Please first select a staff member to fire", MB_OK | MB_ICONSTOP);
		return;
	}

	string name = m_ctrlStaffList.GetItemText(choice, 0);
	//	SetWindowText(name.c_str());
	int answer = AfxMessageBox(("Are you sure you want to fire " + name + "?").c_str(), MB_YESNO | MB_ICONEXCLAMATION);
	if (answer == IDYES) univ.fireStaff(name);
	UpdateAllData();
}


void CUniversitySimulatorDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	univ.save("university.dat");
	CDialogEx::OnClose();
}


void CUniversitySimulatorDlg::OnBnClickedAuto()
{
	// TODO: 在此添加控件通知处理程序代码
	if (univ.getStaffCount() == 0)
	{
		AfxMessageBox("You don't have staff in your university yet. Hire staff before continuing.", MB_OK | MB_ICONSTOP);
		return;
	}
	if (!automatic)
	{
		automatic = true;
		SetTimer(1, 2000, 0);
	}
	else
	{
		automatic = false;
		KillTimer(1);
	}
}


void CUniversitySimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		univ.advanceDate();
		UpdateAllData();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CUniversitySimulatorDlg::OnBnClickedExpand()
{
	// TODO: 在此添加控件通知处理程序代码
	CExpand dlg;
	if (dlg.DoModal() == IDOK)
	{
		univ.expand(placesToAdd);
		UpdateAllData();
	}
}


void CUniversitySimulatorDlg::OnBnClickedViewFinances()
{
	// TODO: 在此添加控件通知处理程序代码
	CFinances dlg;
	dlg.DoModal();
}
