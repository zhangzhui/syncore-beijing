// NetVodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CuOcx.h"
#include "NetVodDlg.h"
//#include "RecordPlayDlg.h"
#include "DlgPicView.h"
#include "DlgPlayList.h"
#include "MainPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CtopCUApp theApp;

#define MSG_PLAYBACK_NOTIFY  WM_USER + 0x100
#define POS_TIMER			100

ULONG RecvData_PlayBack(long lHandle, VOD_GUINFO* pGuInfo, char* lpBuf, int nLength, int nProgress)
{
	CNetVodDlg *pDlg = (CNetVodDlg *)lHandle;
	if(lpBuf != NULL)
	{
		player_inputNetFrame((long)pDlg->m_play_id, (char *)lpBuf, nLength);
	}

	::PostMessage(pDlg->m_hWnd, MSG_PLAYBACK_NOTIFY, (WPARAM)nProgress, (LPARAM)lpBuf);

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CNetVodDlg dialog

CNetVodDlg::CNetVodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetVodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetVodDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hSession = NULL;
	m_hVideo = NULL;
	m_play_id = 0;
	m_bPuase = FALSE;
	m_bLBtDownFlag = FALSE;
	m_nSliderFlag = 0;
	m_nPos = 0;
	m_bVodType = FALSE;
	m_bInit = FALSE;
}


void CNetVodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetVodDlg)
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_btnSnap);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_ctrlStop);
	DDX_Control(pDX, IDC_BUTTON_SLOW, m_ctrlSlow);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_ctrlPlay);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_ctrlPause);
	DDX_Control(pDX, IDC_BUTTON_FAST, m_ctrlFast);
	DDX_Control(pDX, IDC_STATIC_PIC, m_static_play);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetVodDlg, CDialog)
	//{{AFX_MSG_MAP(CNetVodDlg)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_FAST, OnButtonFast)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, OnButtonSlow)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_WM_CLOSE()
	ON_MESSAGE(MSG_PLAYBACK_NOTIFY, OnNitify_PlayBack)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetVodDlg message handlers
void CNetVodDlg::SetBaseInfo(bool bVodType, CU_NET_LIB::GUINFO *pGuInfo, CU_NET_LIB::VODSERVER_INFO *pVodInfo, CString strFileName)
{
	ZeroMemory(&m_guInfo, sizeof(CU_NET_LIB::GUINFO));
	ZeroMemory(&m_vod_info, sizeof(CU_NET_LIB::VODSERVER_INFO));
	memcpy(&m_guInfo, pGuInfo, sizeof(CU_NET_LIB::GUINFO));
	memcpy(&m_vod_info, pVodInfo, sizeof(CU_NET_LIB::VODSERVER_INFO));
	m_strFileName = strFileName;
	m_bVodType = bVodType;
}

void CNetVodDlg::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	CString strLoadText;
	if(m_hSession || m_play_id)
	{
		if(m_bPuase)
		{
			st_vod_play(m_hVideo);
			if (m_bFileType)
				player_setPlayMode(m_play_id, PLAY_MODE_NORMAL);
			m_bPuase = FALSE;
			GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(m_strPreSpeed);
		}
		else
		{
			player_setPlayMode(m_play_id, PLAY_MODE_NORMAL);
			GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(_T("正常速度"));
		}
		return;
	}
	
	HRESULT hr;
	UINT uPort = 0;           //端口
	char szMduIp[32] = {0};   //MDU的IP
	CU_NET_LIB::MDU_ROUTE_INFO mduInfo;
	memset(&mduInfo, 0, sizeof(CU_NET_LIB::MDU_ROUTE_INFO));
	hr = CU_NET_LIB::QueryPuRealRoute(g_dwServerId, m_guInfo, mduInfo);	
	if( ST_OK != hr)
	{
		AfxMessageBox(_T("查询PU路由失败！"));
		return;
	}
		
	CSrvAddrInfo srvAddrinfo;	//5
	memset(&srvAddrinfo, 0, sizeof(CSrvAddrInfo));
	char szServerIp[256]={0};

	CDlgPlayList* pDlgPlayList = (CDlgPlayList*) GetParent();
	CMainPage* pDlg = (CMainPage*)pDlgPlayList->GetParent();
	sprintf(szServerIp, (const char *)pDlg->m_strServerIPAddr.GetBuffer(pDlg->m_strServerIPAddr.GetLength()));
	pDlgPlayList->ParseDomain(szServerIp);
	

	srvAddrinfo.lLocalCsgAddr.S_un.S_addr = inet_addr(szServerIp);

	srvAddrinfo.usLocalCsgPort = htons(pDlg->m_nServerPort + PORT_CSG_INCREASE_NUM);
	srvAddrinfo.lLocalMduAddr.S_un.S_addr = inet_addr(mduInfo.szLocalMduIp);
	srvAddrinfo.usLocalMduPort = htons(mduInfo.uLocalPort+VOD_BASE_MDU_OFFSET);
	strncpy(srvAddrinfo.strLocalMduID, mduInfo.szLocalMduId, VOD_MAX_ID_LEN);
	strncpy(srvAddrinfo.strRemoteMduID, mduInfo.szRemoteMduId, VOD_MAX_ID_LEN);
	if (m_bVodType == TRUE)
	{
		strncpy(srvAddrinfo.strDevDomainID, m_vod_info.szDomainID, VOD_MAX_ID_LEN);
	}
	else
	{
		strncpy(srvAddrinfo.strDevDomainID, m_guInfo.DomainID, VOD_MAX_ID_LEN);
	}
	if(m_guInfo.DomainType != 0)
	{
		//还需要远程的CSGIP与端口，在查询路由时，需要得到。
		srvAddrinfo.lRemoteCsgAddr.S_un.S_addr = inet_addr(mduInfo.szRemoteCsgIp);
		srvAddrinfo.usRemoteCsgPort = htons(mduInfo.uRemoteCsgPort+PORT_CSG_INCREASE_NUM);
		srvAddrinfo.lRemoteMduAddr.S_un.S_addr = inet_addr(mduInfo.szRemoteMduIp);
		srvAddrinfo.usRemoteMduPort = htons(mduInfo.uRemoteMduPort+VOD_BASE_MDU_OFFSET);
	}
	
	m_hSession = st_vod_createSession(srvAddrinfo);
	if(m_hSession == NULL)
	{
		AfxMessageBox(_T("创建实例失败！"));
		return;
	}
	
	if (m_bVodType == TRUE)
	{
		m_hVideo = st_vod_openVideo(m_hSession, m_bVodType, m_vod_info.szVodID, LPCSTR(m_strFileName.GetBuffer(m_strFileName.GetLength())));
	}
	else
	{
		m_hVideo = st_vod_openVideo(m_hSession, FALSE, LPCSTR(m_guInfo.PUID), LPCSTR(m_strFileName.GetBuffer(m_strFileName.GetLength())));
	}

	if(m_hVideo == NULL)
	{
		AfxMessageBox(_T("创建实例失败，服务器忙！"));
		st_vod_destroySession(m_hVideo);
		return;
	}

	if (m_guInfo.lManufactType == TP_PLAY_SDK || m_guInfo.lManufactType == HB_PLAY_SDK)
	{
		m_play_id = player_createPlayInstance(m_guInfo.lManufactType, 2, 0);
		m_bFileType = FALSE;
	}
	else
	{
		m_play_id = player_createPlayInstance(m_guInfo.lManufactType, 1, 0);
		m_bFileType = TRUE;
	}

	if (m_play_id == NULL)
	{
		AfxMessageBox(_T("创建视频实例失败！"));
		return;
	}
	player_setPlayWnd(m_play_id, m_static_play.GetSafeHwnd());
	player_startPlay(m_play_id);
	player_openSound(m_play_id);

	VOD_CLIENTINFO  clientInfo;
	clientInfo.lHandle = (long)this;
	clientInfo.lpFunc  = (VOD_CALLBACKFUNC)RecvData_PlayBack;
	st_vod_registerCallback(m_hVideo, clientInfo);
	st_vod_play(m_hVideo);

	GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(_T("正常播放"));

	m_bInit = TRUE;
}

void CNetVodDlg::OnButtonPause() 
{
	// TODO: Add your control notification handler code here
	CString strLoadText;
	if(m_hSession != NULL)
	{
		if(m_hVideo != NULL)
		{
			st_vod_pause(m_hVideo);
			if (m_bFileType)
				player_setPlayMode(m_play_id, PLAY_MODE_PAUSE);
			m_bPuase = TRUE;
			GetDlgItemText(IDC_STATIC_SPEED, m_strPreSpeed);
			GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(_T("暂停"));
		}
	}
}

void CNetVodDlg::OnButtonFast() 
{
	CString strLoadText,strLoadText1;
	if(m_hSession != NULL)
	{
		if(m_hVideo != NULL)
		{
			int nSpeed = st_vod_speedUp(m_hVideo);
			if(nSpeed == 1 || nSpeed == -1)
			{
				GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(_T("正常速度"));
				if (m_bFileType)
					player_setPlayMode(m_play_id, PLAY_MODE_NORMAL);
			}
			else
			{
				if (m_bFileType)
				{
					if (player_setPlayMode(m_play_id, PLAY_MODE_FAST_FORWARD2) != S_OK)
						return;
				}
				char szSpeed[32] = {0};
				
				if(nSpeed > 1)
				{
					sprintf(szSpeed, "快放 %dX 倍速", nSpeed);
				}
				else if(nSpeed < -1)
				{
					sprintf(szSpeed, "慢放 1/%dX 倍速", -nSpeed);
				}
				
				GetDlgItem(IDC_STATIC_SPEED)->SetWindowText((const unsigned short *)szSpeed);
			}
		}
	}
}

void CNetVodDlg::OnButtonSlow() 
{
	// TODO: Add your control notification handler code here
    CString strLoadText,strLoadText1;
	if(m_hSession != NULL)
	{
		if(m_hVideo != NULL)
		{
			int nSpeed = st_vod_speedDown(m_hVideo);
			if(nSpeed == 1 || nSpeed == -1)
			{
				GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(_T("正常速度"));
				if (m_bFileType)
					player_setPlayMode(m_play_id, PLAY_MODE_NORMAL);
			}
			else
			{
				if (m_bFileType)
				{
					if (player_setPlayMode(m_play_id, PLAY_MODE_SLOW) != S_OK)
						return;
				}

				char szSpeed[32] = {0};
				
				if(nSpeed > 1)
				{
					sprintf(szSpeed, "快放 %dX 倍速", nSpeed);
				}
				else if(nSpeed < -1)
				{
					sprintf(szSpeed, "慢放 1/%dX 倍速", -nSpeed);
				}
				
				GetDlgItem(IDC_STATIC_SPEED)->SetWindowText((const unsigned short *)szSpeed);
			}
		}
	}
}

void CNetVodDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	try
	{
		if(m_hSession != NULL)
		{
			if(m_hVideo != NULL)
			{
				st_vod_stop(m_hVideo);
				st_vod_closeVideo(m_hSession, m_hVideo);
				m_hVideo = NULL;
			}
			st_vod_destroySession(m_hSession);
			m_hSession = NULL;
		}
	}
	catch(...)
	{
	}

	try
	{
		if(m_play_id)
		{
			player_stopPlay(m_play_id);
			player_destroyPlayInstance(m_play_id);
			m_play_id = 0;
		}
	}
	catch(...)
	{
		
	}

	Invalidate();
}

void CNetVodDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OnButtonStop();
	
	CDialog::OnClose();
}



///=== 初始化对话框 ===============================================///
//
BOOL CNetVodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(_T("网络点播"));
	m_Slider.SetRange(0, 10000, TRUE);

	OnButtonPlay();
	if (!m_bInit)
		CDialog::OnOK();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetVodDlg::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	int nPos = m_Slider.GetPos();
	if(m_hSession != NULL )
	{
		if(m_hVideo != NULL)
		{
			st_vod_setPlayPoint(m_hVideo, nPos);
			player_setCurPlayFilePos(m_play_id, 0);
		}
	}
	m_bLBtDownFlag = FALSE;
}

BOOL CNetVodDlg::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return Default();
	}
	BOOL bRet = CDialog::PreTranslateMessage(pMsg);
	if( pMsg->message == WM_LBUTTONDOWN)
	{
		if( pMsg->hwnd == m_Slider.m_hWnd)
		{
			CPoint point;
			point.x = LOWORD(pMsg->lParam);
			point.y = HIWORD(pMsg->lParam);
			
			CRect clientRect, channelRect;
			m_Slider.GetClientRect(&clientRect);
			m_Slider.GetChannelRect(&channelRect);
			
			int nPos = 10000.0*(point.x - channelRect.left)
				/(channelRect.right - channelRect.left);
			if( nPos >=0 && nPos <= 10000)
			{
				m_nSliderFlag = 20;
				m_Slider.SetPos(nPos);
				if(m_hSession != NULL )
				{
					if(m_hVideo != NULL)
					{
						m_bLBtDownFlag = TRUE;
					}
				}
			}
		}
		//双击视频全屏
		POINT cPoint;
		GetCursorPos(&cPoint);
		CRect IsInrc;	
		::GetWindowRect(::GetDlgItem(m_hWnd, IDC_STATIC_PIC), &IsInrc);
		
		if(IsInrc.PtInRect(cPoint))	
		{
			//			if (m_bPlay)
			//			{
			DoFullScreen();
			//			}
		} 
	}	
	return bRet;
}

LRESULT  CNetVodDlg::OnNitify_PlayBack(WPARAM wParam, LPARAM lParam)
{
	CString strLoadText;
	if (m_bLBtDownFlag)
	{
		return 0;
	}
	if(--m_nSliderFlag <= 0)
	{
		int nPos = (int)wParam;
		if( nPos > 10000)
		{
			m_Slider.SetPos(0);
			m_static_play.SetWindowText(_T("已播放完毕!"));
			OnButtonStop();
			
		}
		else if(nPos < 0)
		{
			m_Slider.SetPos(0);
			m_static_play.SetWindowText(_T("视频传送终止"));
			OnButtonStop();
		}
		else  // nPos-[0, 10000]
		{
			m_Slider.SetPos(nPos);
		}
	}
	
	return 0;
}





///=== 截图,按钮事件 ============================================================///
//
void CNetVodDlg::OnButtonSnap() 
{
	CString strLoadText;
	if(m_hSession != NULL && m_hVideo != NULL && m_play_id != 0)
	{
		if(0 == (m_guInfo.right & RIGHT_LOCALRECORD))
			return;
		
		char  szPath[1024] = {0};
		CString strPath;
		_bstr_t bstrFile;
		
		//sprintf(szPath, "%s", (LPCTSTR)theApp.m_path_info.szSnapPath);
		
		// 根据GUID和日期时间确定文件名称		
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		
		try
		{
			SYSTEMTIME systime;
			::GetLocalTime(&systime);
			// 检查路径, 修正路径
			char szFilePath[1024] = {0};
			int nLen = (int)strlen(szPath);
			if(nLen <=0)
			{
				
				//strPath.Format("%s%s\\Picture\\%04d%02d%02d\\", theApp.m_path_info.szSnapPath, m_guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
				sprintf(szFilePath, "%s", (LPCTSTR)strPath);
			}
			else
			{
				if(szPath[nLen-1] != '\\')
					strcat(szPath, "\\");
				strPath.Format(_T("%s%s\\Picture\\%04d%02d%02d\\"), szPath, m_guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
				sprintf(szFilePath, "%s", strPath);
			}			
			
			if(_access(szFilePath,0)!=0)
			{
				CDlgPlayList *pDlgPlayList = (CDlgPlayList *) GetParent();
				
				CMainPage* pDlg = (CMainPage*) pDlgPlayList->GetParent();
				
				pDlg->MakeDir(szFilePath);
			}
			
			CString strFile;
			strFile.Format(_T("%s%02d_%02d_%02d.bmp"), (LPCTSTR)strPath, systime.wHour,systime.wMinute,systime.wSecond);
			bstrFile = _bstr_t((LPCTSTR)strFile);
			
			player_capturePicture(m_play_id, bstrFile);

			Sleep(300);
			
			CDlgPicView dlg;
			dlg.SetFilePath((LPCTSTR)bstrFile);
		    dlg.DoModal();
			
		}
		catch(...)
		{
			AfxMessageBox(_T("异常错误，请检查快照保存路径的设置项！"));
			return;
		}

	}	
}

void CNetVodDlg::DoFullScreen()
{
/*	static WINDOWPLACEMENT	s_bOldWndpl;	
	if(!m_bFullScreen)	//做全屏
	{
		RECT rectDesktop;
		WINDOWPLACEMENT wpNew;
		
		GetWindowPlacement(&m_wpPrev);
		m_wpPrev.length = sizeof(m_wpPrev);
		//保存播放窗口
		m_wndVideo1.GetWindowPlacement(&m_wndPlay);
		::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
		::AdjustWindowRectEx(&rectDesktop, GetStyle(), TRUE, GetExStyle());
		
		LONG style=::GetWindowLong(this->GetSafeHwnd(),GWL_STYLE);
		m_type = style;
		style &= ~WS_CAPTION;
		::SetWindowLong(this->GetSafeHwnd(),GWL_STYLE,style);		
		int screenx=GetSystemMetrics(SM_CXSCREEN);
		int screeny=GetSystemMetrics(SM_CYSCREEN);
		//重新改变大小
		SetWindowPos(NULL, 0, 0, screenx, screeny, SWP_NOZORDER);
		
		wpNew = m_wpPrev;
		wpNew.showCmd =  SW_SHOWNORMAL;
		wpNew.rcNormalPosition = rectDesktop;
		
		RECT rc;
		GetClientRect(&rc);
		m_wndVideo1.MoveWindow(&rc,TRUE);
		//隐藏界面控件,播放、停等
		HideAllButton(FALSE);
		m_bFullScreen = TRUE;
	}
	else		//恢复
	{
		//显示界面控件
		LONG style = m_type;
		::SetWindowLong(this->GetSafeHwnd(),GWL_STYLE,style);
		
		HideAllButton(TRUE);
		SetWindowPlacement(&m_wpPrev);
		m_wndVideo1.SetWindowPlacement(&m_wndPlay);
		m_bFullScreen = FALSE;
	}	
	
	Invalidate();
	*/
}

BOOL CNetVodDlg::HideAllButton(BOOL bFlag)
{
	return false;
}
