// DlgPicView.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPicView dialog


CDlgPicView::CDlgPicView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPicView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPicView)
		// NOTE: the ClassWizard will add member initialization here
	m_Width = NULL;
	m_Height = NULL;

	m_pPicView = NULL;
	//}}AFX_DATA_INIT
}


void CDlgPicView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPicView)
	DDX_Control(pDX, IDC_STATIC_INTERVAL, m_sInterval);
	DDX_Control(pDX, IDC_EDIT, m_edit);
	DDX_Control(pDX, IDC_BTN_AUTO, m_btnAuto);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BTN_PRE, m_btnPre);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPicView, CDialog)
	//{{AFX_MSG_MAP(CDlgPicView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPicView message handlers

BOOL CDlgPicView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnPre.ShowWindow(SW_HIDE);
	m_btnNext.ShowWindow(SW_HIDE);
	m_btnAuto.ShowWindow(SW_HIDE);
	m_edit.ShowWindow(SW_HIDE);
	m_sInterval.ShowWindow(SW_HIDE);
	
	//-----------------------------------------------------
	// 初始化 PicScrollView 实例
	//-----------------------------------------------------
	m_pPicView = (CPicScrollView *)RUNTIME_CLASS(CPicScrollView)->CreateObject();
	ASSERT(m_pPicView != NULL);
	  
	  //context 用于存放类上下文---
	CCreateContext context;
	context.m_pNewViewClass = RUNTIME_CLASS(CPicScrollView);
	
	  //按指定位置生成实例---
	CRect rc;
	GetClientRect(rc);	
	m_pPicView->Create(NULL, m_strFileName, AFX_WS_DEFAULT_VIEW, rc, this, 0, &context);

	  //加载图片---
	LoadPic();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


///===加载图片,重载一=================================================///
void CDlgPicView::LoadPic()
{
	if ( m_strFileName == "" )
	{
		return;
	}
    SetWindowText(m_strFileName);

	DWORD dwBegin = GetTickCount();
    CFile file;
	while (!file.Open(m_strFileName, CFile::modeRead | CFile::shareDenyWrite))
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (GetTickCount() - dwBegin > 10000)
		{
			MessageBox("打开图片文件失败！");
			return;
		}
		else
		{
			Sleep(100);
		}
	}
	m_pPicView->LoadPic(file);

}

void CDlgPicView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	if (m_pPicView == NULL)
	{
		return;
	}
	
	CRect rcClient;
	GetClientRect(rcClient);
	
// 	if (m_pList == NULL)
// 	{
// 		m_btnPre.ShowWindow(SW_HIDE);
// 		m_btnNext.ShowWindow(SW_HIDE);
// 		m_btnAuto.ShowWindow(SW_HIDE);
// 		m_sInterval.ShowWindow(SW_HIDE);
// 		m_edit.ShowWindow(SW_HIDE);
// 		m_pPicView->MoveWindow(rcClient);
// 		return;
// 	}
	
	CRect rcBtnPre;
	m_btnPre.GetWindowRect(rcBtnPre);
	
	CRect rcEdit;
	m_edit.GetWindowRect(rcEdit);
	
	CPoint offset = CPoint(rcClient.Width()/2, rcClient.bottom - BTN_DOWN_DIS) -
		CPoint((rcBtnPre.left+rcEdit.right)/2, rcBtnPre.bottom);
	
	CRect rcCtrl;
	m_btnPre.GetWindowRect(rcCtrl);
	rcCtrl.OffsetRect(offset);
	m_btnPre.MoveWindow(rcCtrl);
	m_btnPre.RedrawWindow();
	
	CRect rcPicView(rcClient);
	rcPicView.bottom = rcCtrl.top - BTN_UP_DIS;
	m_pPicView->MoveWindow(rcPicView);
	
	m_btnNext.GetWindowRect(rcCtrl);
	rcCtrl.OffsetRect(offset);
	m_btnNext.MoveWindow(rcCtrl);
	m_btnNext.RedrawWindow();
	
	m_btnAuto.GetWindowRect(rcCtrl);
	rcCtrl.OffsetRect(offset);
	m_btnAuto.MoveWindow(rcCtrl);
	m_btnAuto.RedrawWindow();
	
	m_sInterval.GetWindowRect(rcCtrl);
	rcCtrl.OffsetRect(offset);
	m_sInterval.MoveWindow(rcCtrl);
	m_sInterval.RedrawWindow();
	
	m_edit.GetWindowRect(rcCtrl);
	rcCtrl.OffsetRect(offset);
	m_edit.MoveWindow(rcCtrl);
	m_edit.RedrawWindow();
	
}

void CDlgPicView::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    lpMMI->ptMinTrackSize.x = min(750,GetSystemMetrics(SM_CXMAXIMIZED));
	lpMMI->ptMinTrackSize.y = min(680,GetSystemMetrics(SM_CYMAXIMIZED));
}

void CDlgPicView::GetFilePath(CString& str)
{
	str = m_strFileName;
}

void CDlgPicView::SetFilePath(CString value)
{
	m_strFileName = value;
}
