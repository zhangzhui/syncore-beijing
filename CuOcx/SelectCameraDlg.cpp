// SelectCameraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cuocx.h"
#include "SelectCameraDlg.h"
#include "MainPage.h"

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
	DDX_Control(pDX, IDC_LIST_RESULT, m_DeviceList);
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
	
	int iCnt = m_DeviceList.GetItemCount();
	int iPos = 0;
	for (; iPos < iCnt; iPos++)
	{
		if (m_DeviceList.GetItemState(iPos, LVIS_SELECTED) == LVIS_SELECTED)
		{
			::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_BEGIN_MONITOR, (WPARAM)m_DeviceList.GetItemData(iPos), NULL);
			break;
		}
	}

	if (iPos == m_DeviceList.GetItemCount())
	{
		AfxMessageBox(_T("请先选择要监视的对象！"));
		return;
	}
	CDialog::OnOK();
}

void CSelectCameraDlg::Init()
{
	//将摄像头列表显示出来
	m_DeviceList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_DeviceList.InsertColumn(0, "摄像头业务名称", LVCFMT_LEFT, 260);
	
	USE_SYNCHRONIZE
	{
		CSingleLock sl(&g_GuInfoList);
		if (!sl.Lock(NTIMEOUT))
			return;
		
		DEVICENODE_OCX::iterator iter = g_DeviceNodeList.begin();
		DEVICENODE_OCX::iterator iterEnd = g_DeviceNodeList.end();
		while(iter != iterEnd)
		{
			CU_NET_LIB::DEVICE_NODE *pNode = *iter;
			if (pNode->guInfo.GUType == GU_TYPE_AV_MASTER
				|| pNode->guInfo.GUType == GU_TYPE_AV_SLAVE)
			{
				//音视频
				CString strDeviceName(pNode->guInfo.GUName);
				if (!pNode->guInfo.bState)
				{
					strDeviceName += _T("(离线)");
				}
				int iItemPos = m_DeviceList.InsertItem(m_DeviceList.GetItemCount(), strDeviceName);
				m_DeviceList.SetItemData(iItemPos, (DWORD)pNode);
			}
			iter++;
		}
	}

	m_DeviceList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	m_DeviceList.SetFocus();
}

BOOL CSelectCameraDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
