#pragma once


// CProjectDataDlg dialog

class CProjectDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CProjectDataDlg)

public:
	CProjectDataDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectDataDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PROJECTDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
