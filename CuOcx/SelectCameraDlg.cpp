// SelectCameraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cuocx.h"
#include "SelectCameraDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectCameraDlg dialog


CSelectCameraDlg::CSelectCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCameraDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectCameraDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectCameraDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectCameraDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectCameraDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectCameraDlg message handlers

void CSelectCameraDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
