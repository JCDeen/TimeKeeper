// NewTaskDlg.cpp : implementation file
//
#include "stdafx.h"
#include "TimeKeeper.h"
#include "NewTaskDlg.h"

// CNewTaskDlg dialog

IMPLEMENT_DYNAMIC(CNewTaskDlg, CDialog)

CNewTaskDlg::CNewTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewTaskDlg::IDD, pParent)
	, m_StartDate(COleDateTime::GetCurrentTime())
	, m_StartTime(COleDateTime::GetCurrentTime())
	, m_StopDate(COleDateTime::GetCurrentTime())
	, m_StopTime(COleDateTime::GetCurrentTime())
	, m_csPayRateDollars(_T("50"))
	, m_csTaskDescription(_T(""))
	, m_csPayRateUnits(_T("hr"))
	, m_csTotalTime(_T(""))
	, m_ctrlTaskIsCompleted(FALSE)
{
	//AfxMessageBox(_T("hello"));
}

CNewTaskDlg::~CNewTaskDlg()
{
}

void CNewTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTDATE, m_StartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTTIME, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOPDATE, m_StopDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOPTIME, m_StopTime);
	DDX_Text(pDX, IDC_EDIT_PAYRATE_DOLLARS, m_csPayRateDollars);
	DDX_Text(pDX, IDC_EDIT_NT_DESCRIP, m_csTaskDescription);
	//DDX_Text(pDX, IDC_EDIT_NT_NOTES, m_csTaskNotes_Internal);
	DDX_CBString(pDX, IDC_COMBO_PAYRATE, m_csPayRateUnits);
	DDX_Control(pDX, IDC_EDIT_NT_DESCRIP, m_ceditTaskDesc);
	DDX_Text(pDX, IDC_EDIT_TOTAL_MINUTES, m_csTotalTime);
	DDX_Check(pDX, IDC_CHECK_MARKCOMPLETED, m_ctrlTaskIsCompleted);
	DDX_Control(pDX, IDC_COMBO_WORK_CATEGORY, m_comboWorkCategories);
}

BEGIN_MESSAGE_MAP(CNewTaskDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNewTaskDlg::OnBnClickedOk)
END_MESSAGE_MAP()
// CNewTaskDlg message handlers

BOOL CNewTaskDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// WHY is first item not bein shown by default ?
	m_comboWorkCategories.SetTopIndex(1);
	return false;   // return TRUE unless you set the focus to a control
}

/////////////
// Setters //
/////////////
void CNewTaskDlg::SetStartDate(int nYear, int nMonth, int nDay)
{
	m_StartDate.SetDate(nYear, nMonth, nDay);
}

void CNewTaskDlg::SetStartDateTime(CString cs)
{
	m_StartDate.ParseDateTime(cs, VAR_DATEVALUEONLY);
	m_StartTime.ParseDateTime(cs, VAR_TIMEVALUEONLY);
}

void CNewTaskDlg::SetStopDate(int nYear, int nMonth, int nDay)
{
	m_StopDate.SetDate(nYear, nMonth, nDay);
}

void CNewTaskDlg::SetStopDateTime(CString cs)
{
	m_StopDate.ParseDateTime(cs, VAR_DATEVALUEONLY);
	m_StopTime.ParseDateTime(cs, VAR_TIMEVALUEONLY);
}

void CNewTaskDlg::SetDescription(CString cs)
{
	m_csTaskDescription = cs;
}

void CNewTaskDlg::SetPayRate(CString cs) // Set both dollars and units.
{
	int nSlashPos = cs.Find("/");// find the slash.
	m_csPayRateUnits = cs.Right(cs.GetLength() - nSlashPos -1);// Get the units string.
	m_csPayRateDollars = cs.Left(nSlashPos);	// Get dollar amount. 
}

void CNewTaskDlg::SetTotalTime(CString cs)
{
	int nSeconds = atoi(cs.Right(2));
	int nMinutes = atoi(cs.Mid(3,2));
	int nHours = atoi(cs.Left(2));
	double dTotalTime = (nHours * 60) + nMinutes + ((double)nSeconds/60.0);
	m_csTotalTime = cs;
}

void CNewTaskDlg::SetCompletedStatus(bool bValue)
{
	m_ctrlTaskIsCompleted = bValue;
}


/////////////
// Getters //
/////////////
CString CNewTaskDlg::GetStartDateTime()
{
	CString	cs = m_StartDate.Format(_T("%m/%d/%y")) + _T(" ") + m_StartTime.Format(_T("%H:%M:%S"));
	return cs;
}

CString CNewTaskDlg::GetStopDateTime()
{
	CString cs = m_StopDate.Format(_T("%m/%d/%y")) + _T(" ") + m_StopTime.Format(_T("%H:%M:%S"));
	return cs;
}

CString CNewTaskDlg::GetDescription()
{
	return m_csTaskDescription;
}

CString CNewTaskDlg::GetPayRate() // Get both dollars and units.
{
	return (m_csPayRateDollars + _T("/") + m_csPayRateUnits);
}

bool CNewTaskDlg::GetCompletedStatus()
{
	return m_ctrlTaskIsCompleted;
}

CString CNewTaskDlg::GetTotalTime()
{
	return m_csTotalTime;
}
//			DWORD dwTotalSeconds = (m_elapsedTime.GetDays() * 24 * 60 * 60) + 
//				(m_elapsedTime.GetHours() * 60 * 60) + (m_elapsedTime.GetMinutes() * 60) + m_elapsedTime.GetSeconds();

void CNewTaskDlg::OnBnClickedOk()
{
	//UpdateData(false);
	OnOK();
}