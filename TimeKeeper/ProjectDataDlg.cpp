// ProjectDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeKeeper.h"
#include "ProjectDataDlg.h"


// CProjectDataDlg dialog

IMPLEMENT_DYNAMIC(CProjectDataDlg, CDialog)

CProjectDataDlg::CProjectDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDataDlg::IDD, pParent)
{

}

CProjectDataDlg::~CProjectDataDlg()
{
}

void CProjectDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProjectDataDlg, CDialog)
END_MESSAGE_MAP()


// CProjectDataDlg message handlers
