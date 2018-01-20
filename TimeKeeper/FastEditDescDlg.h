#pragma once


// CFastEditDescDlg dialog

class CFastEditDescDlg : public CDialog
{
	DECLARE_DYNAMIC(CFastEditDescDlg)

public:
	CFastEditDescDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFastEditDescDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_csTaskDesc;
};
