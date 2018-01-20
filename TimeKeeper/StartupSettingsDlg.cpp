// StartupSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeKeeper.h"
#include "StartupSettingsDlg.h"


// CStartupSettingsDlg dialog

IMPLEMENT_DYNAMIC(CStartupSettingsDlg, CDialog)

CStartupSettingsDlg::CStartupSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartupSettingsDlg::IDD, pParent)
	, m_bStartupWithLastFile(FALSE)
{

}

CStartupSettingsDlg::~CStartupSettingsDlg()
{
}

void CStartupSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_STARTUP_W_LASTFILE, m_bStartupWithLastFile);
}


BEGIN_MESSAGE_MAP(CStartupSettingsDlg, CDialog)
END_MESSAGE_MAP()


// CStartupSettingsDlg message handlers

BOOL CStartupSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//UpdateData(false);
	return true;   // return TRUE unless you set the focus to a control
}

bool CStartupSettingsDlg::GetStartupLastFileOption()
{
	return m_bStartupWithLastFile;
}

void CStartupSettingsDlg::SetStartupLastFileOption(bool bChecked)
{
	m_bStartupWithLastFile = bChecked;
	//UpdateData(false);
}
