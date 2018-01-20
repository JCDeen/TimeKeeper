// TimeKeeperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeKeeper.h"
#include "TimeKeeperDlg.h"
#include "NewTaskDlg.h"
#include "ProjectDataDlg.h"
#include "StartupSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
// CTimeKeeperDlg dialog

CTimeKeeperDlg::CTimeKeeperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeKeeperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CTimeKeeperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ctrlList1);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_PROGRESS_TIMINGINDICATOR, m_ctrlTimingStatus);
}

BEGIN_MESSAGE_MAP(CTimeKeeperDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CTimeKeeperDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDOK, &CTimeKeeperDlg::OnClickedOk)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CTimeKeeperDlg::OnNMouseRightclickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CTimeKeeperDlg::OnNMouseLeftClickList2)
	ON_COMMAND(ID_OPTIONS_PROJECTDATA, &CTimeKeeperDlg::OnOptionsProjectdata)
	ON_COMMAND(ID_OPTIONS_STARTUPSETTINGS, &CTimeKeeperDlg::OnOptionsStartupSettings)
	ON_COMMAND(ID_HELP_ABOUTTIMEKEEPER, &CTimeKeeperDlg::OnHelpAbouttimekeeper)
	ON_COMMAND(ID_FILE_SAVE, &CTimeKeeperDlg::OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, &CTimeKeeperDlg::OnFileSaveas)
	ON_COMMAND(ID_FILE_NEW, &CTimeKeeperDlg::OnFileNew)
	ON_COMMAND(ID_FILEOPEN, &CTimeKeeperDlg::OnFileopen)
	ON_COMMAND(ID_FILE_EXIT, &CTimeKeeperDlg::OnFileExit)
END_MESSAGE_MAP()

// CTimeKeeperDlg message handlers

BOOL CTimeKeeperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ctrlList1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP); // Add grid lines
	m_ctrlList1.InsertColumn(COL_TASK, _T("Task"), LVCFMT_LEFT, 40);
	m_ctrlList1.InsertColumn(COL_START, _T("Start"), LVCFMT_LEFT, 105);
	m_ctrlList1.InsertColumn(COL_STOP, _T("Stop"), LVCFMT_LEFT, 105);
	m_ctrlList1.InsertColumn(COL_RATE, _T("Rate"), LVCFMT_LEFT, 40);
	m_ctrlList1.InsertColumn(COL_TIME, _T("Time"), LVCFMT_LEFT, 60);
	m_ctrlList1.InsertColumn(COL_COST, _T("$$ Cost"), LVCFMT_RIGHT, 55);
	
	m_ctrlList1.InsertColumn(COL_DESCRIP, _T("Task Description"), LVCFMT_LEFT, 350);

	m_bDataHasChanged = false;
	m_bIsTiming = false;

	m_ctrlTimingStatus.SetRange(0, 4); // Init the progress bar.
	m_ctrlTimingStatus.SetStep(1);

	ReadProfileData(); // See if there are any Startup mandates.
	if (!m_csFileName.IsEmpty())
		LoadFileData(m_csFileName);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimeKeeperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimeKeeperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimeKeeperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Bring up New Task Dialog.
void CTimeKeeperDlg::OnBnClickedButtonNew()
{
	int nItem = m_ctrlList1.GetItemCount();
	CNewTaskDlg *pDlg = new CNewTaskDlg();
	INT_PTR nRet = pDlg->DoModal();
	if (nRet == IDOK)
	{
		CString cs;
		cs.Format(_T("%2d"), nItem);
		m_ctrlList1.InsertItem(nItem, cs);

		GetNewTaskData(pDlg, nItem); // Inserts data from dialog into a new task item.

		m_ctrlList1.SetItemData(m_nCurrentItemIndex, 0); // We use the item data to hold number of seconds.
		m_bDataHasChanged = true; // Need to prompt to save data when closing.
	}
	delete pDlg;
}

void CTimeKeeperDlg::OnClickedOk()
{
	OnOK(); // When main app OK is clicked.
	if (m_bDataHasChanged)
	{
		//OnFileSave();
		if (AfxMessageBox(_T("TimeKeeper Data has changed - Save New Data ?"), MB_YESNOCANCEL) == IDYES)
		{
			if (m_csFileName.IsEmpty())
			{
				CFileDialog fileDlg(false); // False constructs it as SaveAs dialog.
				if (fileDlg.DoModal() == IDOK)
				{
					m_csFileName = fileDlg.GetFileName();
					SaveToFile(m_csFileName);
					m_bDataHasChanged = false; // No need to ask again unless data changes some more.
				}
			}
			else
			{
				SaveToFile(m_csFileName);
				m_bDataHasChanged = false; // No need to ask again unless data changes some more.
			}
		}
	}
}

// Right clicked mouse = edit existing task data.
void CTimeKeeperDlg::OnNMouseRightclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	int numSelections = m_ctrlList1.GetSelectedCount();
	int nItem = (reinterpret_cast<int> (m_ctrlList1.GetFirstSelectedItemPosition())) - 1;

	if (nItem >= 0) // We know which item it is from this var.
	{
		CNewTaskDlg *pDlg = new CNewTaskDlg();
		SetNewTaskData(pDlg, nItem);	// Copy the task data to the dialog.
		INT_PTR nRet = pDlg->DoModal(); // "Run" the dialog to allow data to be edited.
		GetNewTaskData(pDlg, nItem);	// Now copy data from dialog back to selected task item.
		delete pDlg;
	}
	*pResult = 0;
}

// Start timing on first click & stop timing on 2nd click for a given task.
void CTimeKeeperDlg::OnNMouseLeftClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nClicked_ItemIndex = pNMIA->iItem;	// The row that was just clicked.
	int numItems = m_ctrlList1.GetItemCount();

	// Process only legitimate ClistCtrl items, ignore clicks on blank rows.
	if ((nClicked_ItemIndex >= 0) && (nClicked_ItemIndex < numItems))
	{
		if (!m_bIsTiming) // Start the timing process for task at m_nCurrentItemIndex.
		{
			m_startTime = CTime::GetCurrentTime();
			m_bIsTiming = true;

			CWnd *ptrTimerStatus = GetDlgItem(IDC_STATIC_TIMERSTATUS);
			CString cs;
			cs.Format(_T("Timing Task %d"), nClicked_ItemIndex);
			ptrTimerStatus->SetWindowText(cs);
			m_nCurrentItemIndex = nClicked_ItemIndex;				// -1 if nothing selected.

			SetTimer(1, 250, 0);
		}
		else if (m_bIsTiming) // Stop the timing on 2nd click & update everything.
		{
			m_stopTime = CTime::GetCurrentTime();
			m_bIsTiming = false;
			m_elapsedTime = m_stopTime - m_startTime;

			KillTimer(1);   
			m_ctrlTimingStatus.SetPos(0);
			if (m_elapsedTime > 0)
				m_bDataHasChanged = true;

			CWnd *ptrTimerStatus = GetDlgItem(IDC_STATIC_TIMERSTATUS);
			ptrTimerStatus->SetWindowText(_T("Timer Off"));

			// Update the stop time in column COL_STOP of previously selected item.
			CString cs = m_stopTime.Format(_T("%m/%d/%y %H:%M:%S"));
			m_ctrlList1.SetItemText(m_nCurrentItemIndex, COL_STOP, cs);

			DWORD dwTotalSeconds = m_elapsedTime.GetTotalSeconds();

			// Make sure to get previous itemdata and add to it !!!
			DWORD dwPreviousTotalSeconds = m_ctrlList1.GetItemData(m_nCurrentItemIndex);

			// Update the elapsed time in COL_TIME.
			m_elapsedTime = m_elapsedTime + dwPreviousTotalSeconds;
			cs = m_elapsedTime.Format("%H:%M:%S");
			m_ctrlList1.SetItemText(m_nCurrentItemIndex, COL_TIME, cs);
			m_ctrlList1.SetItemData(m_nCurrentItemIndex, dwTotalSeconds + dwPreviousTotalSeconds);

			float fCost = (( float(dwTotalSeconds + dwPreviousTotalSeconds))/3600.0) * 
				atof(m_ctrlList1.GetItemText(m_nCurrentItemIndex, COL_RATE));

			cs.Format("%7.2f", fCost);
			m_ctrlList1.SetItemText(m_nCurrentItemIndex, COL_COST, cs);

			if (nClicked_ItemIndex + 1 <= numItems)
				m_nCurrentItemIndex = pNMIA->iItem;
		}
	}
	*pResult = 0;
}

void CTimeKeeperDlg::OnOptionsProjectdata()
{
	CProjectDataDlg *pDlg = new CProjectDataDlg();
	INT_PTR nRet = pDlg->DoModal();
	delete pDlg;
}

void CTimeKeeperDlg::OnTimer(UINT nIDEvent) 
{
	m_ctrlTimingStatus.StepIt();
	CDialog::OnTimer(nIDEvent);
}

void CTimeKeeperDlg::OnHelpAbouttimekeeper()
{
	CAboutDlg *pDlg = new CAboutDlg();
	pDlg->DoModal();
	delete pDlg;
}

// Gets data from NewTaskData dialog and inserts into the currently selected task item.
bool CTimeKeeperDlg::GetNewTaskData(CNewTaskDlg *pDlg, int nItem)
{
	if (pDlg != NULL)
	{
		m_ctrlList1.SetItemText(nItem, COL_START, pDlg->GetStartDateTime());
		m_ctrlList1.SetItemText(nItem, COL_STOP, pDlg->GetStopDateTime());
		m_ctrlList1.SetItemText(nItem, COL_RATE, pDlg->GetPayRate());
		m_ctrlList1.SetItemText(nItem, COL_TIME, pDlg->GetTotalTime());

		// If Description Field is empty, then add one as a 'placeholder'.
		if (pDlg->GetDescription().IsEmpty())
		{
			CString cs;
			cs.Format(_T("Task # %d"), nItem);
			m_ctrlList1.SetItemText(nItem, COL_DESCRIP, cs);
		}
		else
			m_ctrlList1.SetItemText(nItem, COL_DESCRIP, pDlg->GetDescription());

		// Cost = TotalTime in minutes x Hourly Rate in minutes.
		//m_ctrlList1.SetItemText(nItem, COL_COST, _T("0.0"));
		//m_ctrlList1.SetItemData(m_nCurrentItemIndex, 0);

		return true;
	}
	else
		return false; // False means couldn't get the data.
}

// Gets data from currently selected task item and puts it into the NewTaskData dialog.
bool CTimeKeeperDlg::SetNewTaskData(CNewTaskDlg *pDlg, int nItem)
{
	if (pDlg != NULL)
	{
		pDlg->SetStartDateTime(m_ctrlList1.GetItemText(nItem, COL_START));
		pDlg->SetStopDateTime(m_ctrlList1.GetItemText(nItem, COL_STOP));
		pDlg->SetPayRate(m_ctrlList1.GetItemText(nItem, COL_RATE));
		pDlg->SetTotalTime(m_ctrlList1.GetItemText(nItem, COL_TIME));
		pDlg->SetDescription(m_ctrlList1.GetItemText(nItem, COL_DESCRIP));
		return true;
	}
	else
		return false; // False means couldn't get the data.
}

void CTimeKeeperDlg::OnFileSave()
{
	if (m_csFileName) // If filename already present then just save the file.
		SaveToFile(m_csFileName);
	else	// Otherwise open the FileSave dialog.
	{
		CFileDialog fileDlg(false); // False constructs it as SaveAs dialog.
		if (fileDlg.DoModal() == IDOK)
		{
			m_csFileName = fileDlg.GetFileName();
			SaveToFile(m_csFileName);
		}
	}
}

void CTimeKeeperDlg::OnFileSaveas()
{
	CFileDialog fileDlg(false); // False constructs it as SaveAs dialog.
	if (fileDlg.DoModal() == IDOK)
	{
		m_csFileName = fileDlg.GetFileName();
		SaveToFile(m_csFileName);
	}
}

void CTimeKeeperDlg::OnOptionsStartupSettings()
{
	CWinApp* pApp = AfxGetApp();
	CStartupSettingsDlg *pDlg = new CStartupSettingsDlg();
	pDlg->SetStartupLastFileOption(m_bLoadLastFile);
	if ((pDlg->DoModal() == IDOK) && (pDlg->GetStartupLastFileOption())) // Save this in registry.
	{
		if (m_csFileName.IsEmpty())
			AfxMessageBox("No filename to save!");
		else
			pApp->WriteProfileString("STARTUP_DATA", "FILE_TO_LOAD", m_csFileName);
	}
	else
		pApp->WriteProfileString("STARTUP_DATA", "FILE_TO_LOAD", "");
	delete pDlg;
}

void CTimeKeeperDlg::SaveToFile(CString csFileName)
{
	int numItems = m_ctrlList1.GetItemCount();
	if (numItems > 0)
	{
		CFile myFile(csFileName, CFile::modeCreate | CFile::modeWrite);
		//CString cs("CD|more data goes here|and here|133|abc\n"); // Fake data for now ...
		//myFile.Write(cs.GetString(), cs.GetLength());
		CString cs;

		for (int n=0; n<numItems; n++)
		{
			cs.Format(_T("TD|%s|%s|%s|%s|%s|%s|%s\n"),
				m_ctrlList1.GetItemText(n, COL_TASK),
				m_ctrlList1.GetItemText(n, COL_START),
				m_ctrlList1.GetItemText(n, COL_STOP),
				m_ctrlList1.GetItemText(n, COL_TIME),
				m_ctrlList1.GetItemText(n, COL_RATE),
				m_ctrlList1.GetItemText(n, COL_COST),
				m_ctrlList1.GetItemText(n, COL_DESCRIP));

			// Need to add  Discounts ...
			// ie - use CTimeKeeperTaskData() !!!!
			myFile.Write(cs.GetString(), cs.GetLength());
		}
		myFile.Close();

		// CHECK STATUS of the data writing, and if OK rset this flag.
		m_bDataHasChanged = false; // No need to ask again unless data changes some more.
	}
	else
		AfxMessageBox("No Data to Save");
}

bool CTimeKeeperDlg::LoadFileData(CString csFileName)
{
	int nItem = 0;
	int nCustData = 0;
	CString cs;
	CStdioFile myFile(csFileName, CFile::modeRead | CFile::typeText );

	while (myFile.ReadString(cs))
	{
		if (cs.Left(3) == "CD|") // Customer Data begins with "CD|"
		{
			nCustData++;
			// Put code here to populate the Customer Data structure.
		}
		else if (cs.Left(3) == "TD|") // Task Data begins with "TD|"
		{
			ParseNextValue(cs);	// Read & discard the Data Identification token
			ParseNextValue(cs);	// Read & discard the Task Number field

			CString csItem;
			csItem.Format(_T("%2d"), nItem);	
			m_ctrlList1.InsertItem(nItem, csItem); // Use fresh item number instead of one from data file.

			m_ctrlList1.SetItemText(nItem, COL_START, ParseNextValue(cs));
			m_ctrlList1.SetItemText(nItem, COL_STOP, ParseNextValue(cs));

			CString csTotalTime = ParseNextValue(cs);
			m_ctrlList1.SetItemText(nItem, COL_TIME, csTotalTime);
			m_ctrlList1.SetItemText(nItem, COL_RATE, ParseNextValue(cs));
			m_ctrlList1.SetItemText(nItem, COL_COST, ParseNextValue(cs));
			m_ctrlList1.SetItemText(nItem, COL_DESCRIP, ParseNextValue(cs));

			DWORD dwTotalSeconds = (atoi(ParseNextValue(csTotalTime, ":")) * 60 * 60) + // hours
				(atoi(ParseNextValue(csTotalTime, ":")) * 60) + // minutes
				atoi(ParseNextValue(csTotalTime, ":")); // seconds

			m_ctrlList1.SetItemData(nItem, dwTotalSeconds); // Store total time in item's data area.

			nItem++;
		}
	}
	UpdateData(true);
	myFile.Close();
	return true;
}

CString CTimeKeeperDlg::ParseNextValue(CString &csInput, CString csToken)
{	
	CString csRetVal;

	if (csInput.GetLength() > 0)
	{
		int nTokenPos = csInput.Find(csToken);
		csRetVal = csInput.Left(nTokenPos);	// Get dollar amount.
		if (nTokenPos > 0)
			csInput = csInput.Right(csInput.GetLength() - nTokenPos -1);// Get the units string.
		else if (csInput.GetLength() > 0) // Last data string not ended with "|".
		{
			csRetVal = csInput;
		}
		else
			csRetVal = "NO DESCRIP";
	}
	return csRetVal;
}

void CTimeKeeperDlg::OnFileNew()
{
	int nResponse = 0;
	if (m_bDataHasChanged)
	{
		//OnFileSave();
		if ((nResponse = AfxMessageBox(_T("TimeKeeper Data has changed - Save New Data ?"), MB_YESNOCANCEL)) == IDYES)
		{
			if (m_csFileName.IsEmpty())
			{
				CFileDialog fileDlg(false); // False constructs it as SaveAs dialog.
				if (fileDlg.DoModal() == IDOK)
				{
					m_csFileName = fileDlg.GetFileName();
					SaveToFile(m_csFileName);
					m_bDataHasChanged = false; // No need to ask again unless data changes some more.
				}
			}
			else
			{
				SaveToFile(m_csFileName);
				m_bDataHasChanged = false; // No need to ask again unless data changes some more.
			}
		}
		else if(nResponse == IDNO)
			m_ctrlList1.DeleteAllItems();
	}
	else
		m_ctrlList1.DeleteAllItems();
}

void CTimeKeeperDlg::OnFileopen()
{
	CFileDialog fileDlg(true); // If bFileSave == true open CFileDialog as Open dialog.
	if (fileDlg.DoModal() == IDOK)
	{
		m_csFileName = fileDlg.GetFileName();
		LoadFileData(m_csFileName);
	}
}

void CTimeKeeperDlg::OnFileExit()
{
	// TODO: Add your command handler code here
}

bool CTimeKeeperDlg::ReadProfileData()
{
	CString cs;
	CWinApp* pApp = AfxGetApp();
	cs = pApp->GetProfileString("STARTUP_DATA", "FILE_TO_LOAD");
	if (cs.IsEmpty())
		m_bLoadLastFile = false;
	else
	{
		m_csFileName = cs;
		m_bLoadLastFile = true;
	}

	//int nValue = pApp->GetProfileInt("strSection", "strIntItem", 0);
	return true;
}

bool CTimeKeeperDlg::WriteProfileData()
{
	CWinApp* pApp = AfxGetApp();
	if(m_bLoadLastFile)
		pApp->WriteProfileString("STARTUP_DATA", "FILE_TO_LOAD", m_csFileName);
	//pApp->WriteProfileInt(strSection, strIntItem, 1234);
	return true;
}
