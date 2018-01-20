#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
// CNewTaskDlg dialog

class CNewTaskDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewTaskDlg)

public:
	CNewTaskDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewTaskDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_NEWTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_StartDate;
	COleDateTime m_StartTime;
	COleDateTime m_StopDate;
	COleDateTime m_StopTime;
	CString m_csPayRateDollars;
	CString m_csPayRateUnits;
	CString m_csTaskDescription;
	CString m_csTotalTime;
	BOOL m_ctrlTaskIsCompleted;
	CComboBox m_comboWorkCategories;

	void SetStartDate(int nDay, int nMonth, int nYear);
	void SetStartDateTime(CString cs);
	void SetStopDate(int nDay, int nMonth, int nYear);
	void SetStopDateTime(CString cs);
	void SetPayRate(CString cs);
	void SetTotalTime(CString cs);
	void SetDescription(CString cs);

	CString GetStartDateTime();
	CString GetStopDateTime();
	CString GetDescription();
	CString GetPayRate();
	CString GetTotalTime();

	void SetCompletedStatus(bool bValue);
	bool GetCompletedStatus();

	BOOL OnInitDialog(); 
	CEdit m_ceditTaskDesc;
	afx_msg void OnBnClickedOk();
};
