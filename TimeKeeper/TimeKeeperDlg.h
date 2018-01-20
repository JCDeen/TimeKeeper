// TimeKeeperDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "NewTaskDlg.h"
#include "TimeKeeperProjectData.h"

// CTimeKeeperDlg dialog

#define	COL_TASK	0
#define	COL_START	1
#define	COL_STOP	2
#define	COL_RATE	3 // dollars / hour
#define	COL_TIME	4 // minutes accumulated
#define	COL_COST	5 // dollar amount to bill customer
#define	COL_DESCRIP	6

class CTimeKeeperDlg : public CDialog
{
// Construction
public:
	CTimeKeeperDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIMEKEEPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	bool m_bDataHasChanged; // Flag to prompt for saving data.
	bool m_bIsTiming;		// True if timer is running.
	bool m_bLoadLastFile;
	CButton m_ctrlButtonNew;	// Invokes New Task Dlg when clicked.

	CTime m_startTime, m_stopTime;	// Start / Stop times of whatever task is being timed.
	CTimeSpan m_elapsedTime;
	int m_nCurrentItemIndex;		// Zero based index of task selected. (-1 if none)
	int m_nCurrentSubItemIndex;		// Zero based index of column selected.

	CString m_csFileName;			// Filename to save data to. May or may not be set.

	CListCtrl m_ctrlList1;			// Main control for the app.
	CProgressCtrl m_ctrlTimingStatus;	// Used to indicate a task is timing.

	CTimeKeeperProjectData m_projectData;
	bool ReadProfileData();		// Reads data common to all projects.
	bool WriteProfileData();	// Writes data common to all projects.

	afx_msg void OnBnClickedButtonNew();	// Invokes New Task Dlg.
	afx_msg void OnClickedOk();				// Terminate app & prompt to save data.
	afx_msg void OnNMouseRightclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMouseLeftClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOptionsProjectdata();
	afx_msg void OnOptionsStartupSettings();
	void OnTimer(UINT nIDEvent);
	afx_msg void OnHelpAbouttimekeeper();

	bool GetNewTaskData(CNewTaskDlg *ptrDlg, int nItem); // Gets data from New Task Dialog and inserts into current task item.
	bool SetNewTaskData(CNewTaskDlg *ptrDlg, int nItem); // Gets data from current task item and inserts into New Task Dialog .

	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	void SaveToFile(CString csFileName);
	bool LoadFileData(CString csFilename);

	CString ParseNextValue(CString &csInput, CString csToken="|");
	afx_msg void OnFileNew();
	afx_msg void OnFileopen();
	afx_msg void OnFileExit();
};
