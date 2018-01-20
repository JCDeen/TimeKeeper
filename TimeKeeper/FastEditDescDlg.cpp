// FastEditDescDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeKeeper.h"
#include "FastEditDescDlg.h"


// CFastEditDescDlg dialog

IMPLEMENT_DYNAMIC(CFastEditDescDlg, CDialog)

CFastEditDescDlg::CFastEditDescDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFastEditDescDlg::IDD, pParent)
	, m_csTaskDesc(_T(""))
{

}

CFastEditDescDlg::~CFastEditDescDlg()
{
}

void CFastEditDescDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FASTNOTES, m_csTaskDesc);
}


BEGIN_MESSAGE_MAP(CFastEditDescDlg, CDialog)
END_MESSAGE_MAP()


// CFastEditDescDlg message handlers
