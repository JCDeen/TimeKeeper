#pragma once


// CStartupSettingsDlg dialog

class CStartupSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CStartupSettingsDlg)

public:
	CStartupSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStartupSettingsDlg();
	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_STARTUPSETTINGS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bStartupWithLastFile;
	bool GetStartupLastFileOption();
	void SetStartupLastFileOption(bool bChecked);
};
