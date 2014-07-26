// MainPage.cpp : implementation file
//

#include "stdafx.h"
#include "CuOcx.h"
#include "MainPage.h"
#include "VideoInstance.h"
#include "DlgPicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// 
long CALLBACK dec_callback( long hHandle, dec_data_t* dec_data, DWORD dwUser)
{
	return 0;
}

void CALLBACK ProcessRecvData(long lHandle, void* lpBuf, long lSize, long lDecoderID )
{
	if (lpBuf == NULL)
	{
		return;
	}

	frame_head_t *pHead = (frame_head_t *)lpBuf;//获得帧头

	CMainPage* pDlg = (CMainPage*)lHandle;
	if (pDlg == NULL)
		return;	
	if( pDlg->m_play_id != 0)
	{
// 		frame_head_t *pHead = (frame_head_t *)lpBuf;
		player_inputNetFrame(pDlg->m_play_id, (char *)lpBuf, lSize);
// 		TRACE(_T("~~~~~~~~~~~~~~~~~~~lSize = %d------lDecoderID=%d\n"), lSize, lDecoderID);
		pDlg->m_nCountTest = pHead->frame_no;
	}

#ifdef _DEBUG
	switch(pHead->frame_type)
	{
	case A_FRAME_TYPE:
		TRACE("A_FRAME_TYPE...\n");
		break;
	case I_FRAME_TYPE:
		TRACE("I_FRAME_TYPE...\n");
		break;
	case P_FRAME_TYPE:
		TRACE("P_FRAME_TYPE...\n");
		break;
	case OSD_FRAME_TYPE:
		TRACE("OSD_FRAME_TYPE...\n");
		break;
	default:
		TRACE("TYPE:%d...\n", pHead->frame_type);
		break;
	}
#endif


	if (pDlg->m_bRecord && pHead->frame_type != A_FRAME_TYPE)
	{
		//只保存录像
		//A_FRAME_TYPE为声音
		if(!pDlg->m_bRecord)
			return;
		
		if (pDlg->m_bSwitchRecordFile)
		{
// 			frame_head_t *pHead = (frame_head_t *)lpBuf;
			if (pHead->frame_type == I_FRAME_TYPE)
				pDlg->CreateRecordFile();
		}	
		if (pDlg->m_Recordfile != NULL)
			fwrite((PBYTE)lpBuf + sizeof(frame_head_t), lSize - sizeof(frame_head_t), 1, pDlg->m_Recordfile);
		
		if (pDlg->m_hRecordFileRec != NULL)
			AVI_fwrite(pDlg->m_hRecordFileRec, lpBuf);
	}
	else if (pDlg->m_bSoundRecord && pHead->frame_type != P_FRAME_TYPE)
	{
		//保存声音文件
		if(!pDlg->m_bSoundRecord)
			return;
		
		if (pDlg->m_bSwitchSoundFile)
		{
// 			frame_head_t *pHead = (frame_head_t *)lpBuf;
			if (pHead->frame_type == I_FRAME_TYPE)
				pDlg->CreateRecordFile();
		}	
		if (pDlg->m_SoundFile != NULL)
			fwrite((PBYTE)lpBuf + sizeof(frame_head_t), lSize - sizeof(frame_head_t), 1, pDlg->m_SoundFile);
		
		if (pDlg->m_hSoundFileRec != NULL)
			AVI_fwrite(pDlg->m_hSoundFileRec, lpBuf);
	}
}

void RecAudioDataFunc(long lHandle, void* lpBuf, long lSize, long lDecoderID)
{
	player_inputNetFrame(g_dwAudioInstance, (char*)lpBuf, lSize);	
	return;
}

int CALLBACK DualDataFunc(int size, const char* data, DWORD dwUser)
{
	CU_NET_LIB::SendVoiceData(g_dwServerId, data, size);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainPage dialog


CMainPage::CMainPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMainPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strUserName.Empty();
	m_strPassWord.Empty();
	m_strServerIPAddr.Empty();
	m_nServerPort = 0;
	m_strWorkDir.Empty();
	m_strCameraID.Empty();

	m_pVideoIns = NULL;

	m_hRecordFileRec = NULL;
	m_Recordfile = NULL;
	m_bRecord = FALSE;//刚开始是没有开始录像的
	m_SoundFile = NULL;
	m_bSoundRecord = FALSE;//刚开始是没有录音的

	m_bStreamOpenFlag = FALSE;
	m_play_id = 0;
	m_lManufactType = 0;
	m_pDeviceNode = NULL;
	m_bLoginFlag = TRUE;
	ZeroMemory(&m_GuInfo, sizeof(CU_NET_LIB::GUINFO));
	m_bOpenVideo = FALSE;
	ZeroMemory(&m_DevInfo, sizeof(CU_NET_LIB::DEVICE_NODE));
	m_bVoice = FALSE;
	m_bSoundAllow = FALSE;
}


void CMainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainPage)
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_sliderSaturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sliderHue);
	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_sliderBright);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sliderContrast);
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_staticPreview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainPage, CDialog)
	//{{AFX_MSG_MAP(CMainPage)
	ON_MESSAGE(WM_LOGIN, OnLogin)
	ON_MESSAGE(WM_GETDEVICELIST, OnGetDeviceList)
	ON_MESSAGE(WM_CLEARDEVICELIST, OnClearDeviceList)
	ON_BN_CLICKED(IDC_BTN_OPEN_VIDEO, OnBtnOpenVideo)
	ON_BN_CLICKED(IDC_BTN_CLOSE_VIDEO, OnBtnCloseVideo)
	ON_BN_CLICKED(IDC_BTN_OPENSOUND, OnBtnOpensound)
	ON_BN_CLICKED(IDC_BTN_OPENVOICE, OnBtnOpenvoice)
	ON_BN_CLICKED(IDC_BTN_REPLAY, OnBtnReplay)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBtnRight)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBtnLeft)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_AUTO, OnBtnAuto)
	ON_BN_CLICKED(IDC_BTN_REMOTE_PIC, OnBtnRemotePic)
	ON_BN_CLICKED(IDC_BUTTON_FOCUS1, OnButtonFocus1)
	ON_BN_CLICKED(IDC_BUTTON_FOCUS2, OnButtonFocus2)
	ON_BN_CLICKED(IDC_BUTTON_LENS1, OnButtonLens1)
	ON_BN_CLICKED(IDC_BUTTON_LENS2, OnButtonLens2)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM1, OnButtonZoom1)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM2, OnButtonZoom2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BRIGHT, OnReleasedcaptureSliderBright)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CONTRAST, OnReleasedcaptureSliderContrast)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_HUE, OnReleasedcaptureSliderHue)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SATURATION, OnReleasedcaptureSliderSaturation)
	ON_BN_CLICKED(IDC_BTN_LOCALPIC, OnBtnLocalpic)
	ON_BN_CLICKED(IDC_BTN_LOCALRECORD, OnBtnLocalrecord)
	ON_MESSAGE(WM_SHOWCAPTUREPIC, OnShowCapturePic)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_LOCALSOUNDRECORD, OnBtnLocalsoundrecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainPage message handlers

BOOL CMainPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InVisibleCtrls();

	if (InitSDK())
	{
		g_dwAudioInstance = player_createPlayInstance(TP_PLAY_SDK,
												PLAY_DUALTALK_TYPE,
												0);

		PostMessage(WM_LOGIN, NULL, NULL);
	}
	GetDlgItem(IDC_EDIT_DEVICE)->SetWindowText(m_strCameraID);

	CListCtrl *pList = (CListCtrl*)GetDlgItem(IDC_LIST_OP);
	if (pList && pList->GetSafeHwnd())
	{
		pList->SetExtendedStyle(LVS_EX_FULLROWSELECT);
		pList->InsertColumn(0, "时间", LVCFMT_LEFT, 70);
		pList->InsertColumn(1, "操作", LVCFMT_LEFT, 180);
	}

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainPage::SetPassWord(LPCTSTR strPassWord)
{
	m_strPassWord = strPassWord;
}

void CMainPage::SetUserName(LPCTSTR strUserName)
{
	m_strUserName = strUserName;
}

void CMainPage::SetServerIPAddr(LPCTSTR strIPAddr)
{
	m_strServerIPAddr = strIPAddr;
}

void CMainPage::SetServerPort(long nPort)
{
	m_nServerPort = nPort;
}

void CMainPage::SetWorkDir(LPCTSTR strWorkDir)
{
	m_strWorkDir = strWorkDir;
	if (!m_strWorkDir.IsEmpty())
	{
		if (m_strWorkDir.GetAt(m_strWorkDir.GetLength() - 1) == _T('\\'))
		{
			m_strWorkDir.Delete(m_strWorkDir.GetLength() - 1, 1);
		}
	}
}

void CMainPage::SetCameraID(LPCTSTR strCameraID)
{
	m_strCameraID = strCameraID;
}

void CMainPage::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_dlgPlayList.GetSafeHwnd())
	{
		m_dlgPlayList.SendMessage(WM_CLOSE, NULL, NULL);
	}

	if (m_bLoginFlag)
	{
		CU_NET_LIB::RequestLogout(g_dwServerId);
	}

	if(m_bClientStartUp == TRUE)
	{
		CU_NET_LIB::ClientCleanUp(g_dwServerId);
	}

	if (g_dwServerId != NULL)
	{
		CU_NET_LIB::DeleteLibInstance(g_dwServerId);
	}

	if (g_InitPlaySDK)
	{
		DestroyPlaySDKObject();
	}
	CDialog::PostNcDestroy();
	delete this;
}

BOOL CMainPage::InitSDK()
{
	if (!(g_InitPlaySDK = CreatePlaySDKObject()))
	{
		MessageBox(_T("初始化解码库失败！"));
		return FALSE;
	}

	g_dwServerId = CU_NET_LIB::InitilLibInstance();
	if (g_dwServerId == NULL)
	{
		MessageBox(_T("初始化通信库失败！"));
		return FALSE;
	}

	CU_NET_LIB::SetCmdTimeOut(g_dwServerId, NTIMEOUT);

	m_bClientStartUp = CU_NET_LIB::ClientStartUp(g_dwServerId, WM_CUNETLIB, this->GetSafeHwnd());
	if (m_bClientStartUp ==  FALSE)
	{
		MessageBox(_T("客户端启动失败！"));
		return FALSE;
	}
	return TRUE;
}

void CMainPage::OnLogin(WPARAM wParam, LPARAM lParam)
{
	CWaitCursor cursor;

	char szDomainID[32] = {0};
	char szRemoteIP[128] = {0};
	int nLoginedNum = 0;
	CU_NET_LIB::SetCmdTimeOut(g_dwServerId, NTIMEOUT);
	if (CU_NET_LIB::RequestLogin(g_dwServerId, 
								m_strServerIPAddr, 
								m_nServerPort,
								m_strUserName,
								m_strPassWord,
								(LPTSTR)szDomainID,
								(LPTSTR)szRemoteIP,
								nLoginedNum))
	{
		if(strcmp("NULL", szRemoteIP) != 0 && strlen(szRemoteIP) != 0)
		{
			CString szContent;
			szContent.Format(_T("是否确认抢占，对方IP为：%s"), szRemoteIP);
            if(IDCANCEL == MessageBox(szContent, _T("提示"), MB_ICONWARNING | MB_OKCANCEL))
			{
				CU_NET_LIB::RequestLogout(g_dwServerId);
				m_bLoginFlag = FALSE;
				return;
			}
			else
			{
				if(FALSE == CU_NET_LIB::GrabLogin(g_dwServerId))
				{
					MessageBox(_T("抢占失败！"));
					CU_NET_LIB::RequestLogout(g_dwServerId);
					m_bLoginFlag = FALSE;
					return;
				}
			}
		}
		else
		{
			this->PostMessage(WM_GETDEVICELIST, NULL, NULL);//获取设备列表
		}
	}
	else
	{
		MessageBox(_T("连接视频服务器失败！"));
		return;
	}
	m_bLoginFlag = TRUE;//用户登录成功
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_OPEN_VIDEO, BN_CLICKED), (LPARAM)GetDlgItem(IDC_BTN_OPEN_VIDEO)->GetSafeHwnd());
}

void CMainPage::OnGetDeviceList(WPARAM wParam, LPARAM lParam)
{
	CString strXml(_T("DeviceList.xml"));
	HRESULT hr = CU_NET_LIB::QueryDeviceList(g_dwServerId, strXml);
	if (hr == ST_OK)
	{
		USE_SYNCHRONIZE
		{
			CSingleLock sl(&g_GuInfoList);
			if (sl.Lock(NTIMEOUT))
			{
				SendMessage(WM_CLEARDEVICELIST, NULL, NULL);
				//查询设备信息，插入到list中
				InsertChildNode(NULL, 0);

				CU_NET_LIB::GetDomainInfo(g_dwServerId, (LPCTSTR)g_szDomainID, sizeof(g_szDomainID) - 1);
			}
		}
	}
	else
	{
		MessageBox(_T("查询设备列表失败！"));
	}
}

void CMainPage::InsertChildNode(LPCTSTR lpszQueryID, int iType)
{
	int iNodeCount = 0;
	int i=0;
	HRESULT hr;
	CString strName(_T(""));
	CU_NET_LIB::DEVICE_NODE dev_node[MAX_DEVICE_NODE_NUM];
	memset(dev_node, 0, sizeof(CU_NET_LIB::DEVICE_NODE)*MAX_DEVICE_NODE_NUM);
	hr = CU_NET_LIB::GetDeviceList(g_dwServerId, lpszQueryID, iType, dev_node, MAX_DEVICE_NODE_NUM, &iNodeCount);
	if (hr != ST_OK)
	{
		return;
	}
	if (lpszQueryID == NULL)
	{
		CU_NET_LIB::DEVICE_NODE *pInfo = new CU_NET_LIB::DEVICE_NODE;
		memset(pInfo, 0, sizeof(CU_NET_LIB::DEVICE_NODE));
		memcpy(pInfo, &dev_node[i], sizeof(CU_NET_LIB::DEVICE_NODE));
		
		g_DeviceNodeList.push_back(pInfo);
		i++;
	}

	for(i; i< iNodeCount; i++)
	{
		CU_NET_LIB::DEVICE_NODE *pInfo = new CU_NET_LIB::DEVICE_NODE;
		memset(pInfo, 0, sizeof(CU_NET_LIB::DEVICE_NODE));
		memcpy(pInfo, &dev_node[i], sizeof(CU_NET_LIB::DEVICE_NODE));
		
		g_DeviceNodeList.push_back(pInfo);
		switch(dev_node[i].nType)
		{
		case 0://域
			InsertChildNode((LPCTSTR)dev_node[i].DomainID, dev_node[i].nType);
			break;
		case 1://机构
			InsertChildNode((LPCTSTR)dev_node[i].AreaID, dev_node[i].nType);
			break;
		case 2://功能节点
			break;
		default:
			break;
		}
	}
}

void CMainPage::OnClearDeviceList(WPARAM wParam, LPARAM lParam)
{
	CWaitCursor wait;

	USE_SYNCHRONIZE
	{
		CSingleLock sl(&g_GuInfoList);
		if (sl.Lock(NTIMEOUT))
		{
			GUINFO_OCX::iterator iter = g_GuInfoList.begin();
			while(iter != g_GuInfoList.end())
			{
				delete *iter;
				iter ++;
			}
			g_GuInfoList.clear();

			DEVICENODE_OCX::iterator iterDev = g_DeviceNodeList.begin();
			while(iterDev != g_DeviceNodeList.end())
			{
				delete *iterDev;
				iterDev++;
			}
			g_DeviceNodeList.clear();
		}
	}
}

void CMainPage::OnBtnOpenVideo() 
{
	// TODO: Add your control notification handler code here
	memset(&m_GuInfo, 0x00, sizeof(CU_NET_LIB::GUINFO));
	m_GuInfo.bState = TRUE;

	//查找设备
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
				if (strcmp(pNode->guInfo.GUName, (const char *)m_strCameraID.GetBuffer(m_strCameraID.GetLength())) == 0)
				{
					m_pDeviceNode = pNode;
					m_GuInfo = pNode->guInfo;
					break;
				}
			}
			iter++;
		}
	}

	if (m_pDeviceNode != NULL)
	{
		StartStream(*m_pDeviceNode);
		m_bOpenVideo = TRUE;
		GetDlgItem(IDC_BTN_OPEN_VIDEO)->EnableWindow(FALSE);
		CString str("打开视频");
		TextOutOperation(str);
	}
}

void CMainPage::StartStream(CU_NET_LIB::DEVICE_NODE devInfo)
{
	CWaitCursor wait;
	StopStream();
    CString strLoadText,strLoadText1;
	m_hNotiy.ResetEvent();
	
	CU_NET_LIB::GUINFO guInfo = devInfo.guInfo;	
	m_pVideoIns = g_VideoMng.CreateVideoInstance((LPCTSTR)guInfo.GUID);
	if(!CreatePlayInstance(guInfo))
	{
		MessageBox(_T("创建视频实例失败！"));
		return;
	}
	BOOL bRet = m_pVideoIns->Start(guInfo, (LONG)this, m_hNotiy, ProcessRecvData);
	if(bRet)
	{
		//正在请求视频...
		m_bStreamOpenFlag = TRUE;
		m_hEventQuit = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		ASSERT(m_hEventQuit!=NULL);
		m_pThread = AfxBeginThread(Thread_Status, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		if(m_pThread != NULL)
		{
			m_pThread->m_bAutoDelete = FALSE;
			m_pThread->ResumeThread();
		}
		else
		{
			strLoadText="创建线程异常";
			AfxMessageBox(strLoadText);
		}
		GetDlgItem(IDC_BTN_CLOSE_VIDEO)->EnableWindow(TRUE);   
	}
	else
	{
		StopStream();
		DestroyPlayInstance();
	}   
}

void CMainPage::StopStream()
{
	TRACE(_T("STOPSTREAM========================\n"));
	CString strLoadText,strLoadText1;
	if (!m_bStreamOpenFlag)
	{
		m_strNotiy.Empty();
		m_bStreamOpenFlag = FALSE;
		return;
	}	
	if (m_pVideoIns)                            
	{
		m_pVideoIns->Stop((LONG)this);
		m_pVideoIns = NULL;
	}
	WaitForThreadStatus();
	m_bStreamOpenFlag = FALSE;
//	CU_NET_LIB::RealVideoPreviewStop(g_dwServerId, m_hVideo)
	Invalidate();
	m_GuInfo.bState = FALSE;
}

void  CMainPage::WaitForThreadStatus()
{
	::SetEvent(m_hEventQuit);
	DWORD dwStart = GetTickCount();
	if(m_pThread)
	{
		HANDLE  hThread = m_pThread->m_hThread;
		DWORD dwCode = STILL_ACTIVE;
		while(1)
		{
			GetExitCodeThread(hThread, &dwCode);
            if(STILL_ACTIVE == dwCode)
			{
				Sleep(100);
			}
			else
			{
				break;
			}
		}
		SAFE_DELETE(m_pThread);
	}

	CloseHandle(m_hEventQuit);
	TRACE(_T("WaitForThreadStatus lost time: %d\n"), GetTickCount()-dwStart);
}

BOOL CMainPage::CreatePlayInstance(CU_NET_LIB::GUINFO guInfo)
{
	if(m_play_id == 0)
	{		
		m_play_id = player_createPlayInstance(guInfo.lManufactType, 2, 0);
		if (m_play_id == NULL)
		{
			return FALSE;
		}
		player_setPlayWnd(m_play_id, m_staticPreview.m_hWnd);
		player_startPlay(m_play_id);
		m_lManufactType = guInfo.lManufactType;
		
		player_registerDecCallback(m_play_id, dec_callback, 111);
	}
	else
	{
		if (m_lManufactType != guInfo.lManufactType)
		{
			DestroyPlayInstance();
			CreatePlayInstance(guInfo);
		}
	}
	return TRUE;
}

void CMainPage::DestroyPlayInstance()
{
	if (m_play_id > 0)
	{
		player_stopPlay(m_play_id);
		player_destroyPlayInstance(m_play_id);
	}		
	m_play_id = 0;
	m_lManufactType = 0;
}

UINT  CMainPage::Thread_Status(LPVOID lParam)
{
	CMainPage *pDlg = (CMainPage*)lParam;
    CString strLoadText,strLoadText1,strLoadText2,strLoadText3;
	if(!pDlg->m_pVideoIns)
		return FALSE;
	///////////////////////////////////////////////////////////////////////
	while (pDlg->m_hEventQuit)
	{
		//首先判断连接是否成功
		DWORD dwResult = ::WaitForSingleObject(pDlg->m_hNotiy.m_hObject, 0);
		if( WAIT_OBJECT_0 == dwResult)//( WAIT_OBJECT_0 == dwResult)
		{
			// 检查连接标志执行响应动作
			if (pDlg->m_pVideoIns)
			{
				DWORD dwFlag;
				dwFlag = pDlg->m_pVideoIns->GetFlag() ;
				if(ST_OK == dwFlag)
				{
					strLoadText="HTTP请求成功";
					TRACE(_T("-------------------------%s\n"), strLoadText);
					break;
				}
				else
				{
					CString strMsg;
					CString strDes;
					strDes.Format(_T("%s:"), pDlg->m_DevInfo.guInfo.GUName);					
					strDes += strMsg;
					pDlg->m_strNotiy.Format(_T("%s"), strDes);
					if (pDlg->m_pVideoIns)
					{
						pDlg->m_pVideoIns->Stop((LONG)pDlg);
					}	
					pDlg->m_pVideoIns = NULL;
					pDlg->m_bStreamOpenFlag = FALSE;
					if( pDlg->m_bSoundAllow)
						pDlg->m_bSoundAllow = FALSE;
//					pDlg->m_bPause = FALSE; // 取消暂停标志
					ZeroMemory(&pDlg->m_DevInfo, sizeof(CU_NET_LIB::DEVICE_NODE));
					return FALSE;
				}
			}			
		}
		else
		{
			if(WAIT_OBJECT_0 == ::WaitForSingleObject(pDlg->m_hEventQuit, 0))
			{
				return FALSE;
			}
			continue;
		}
	}
	
	////////////////////////////////////////////////////////	
	//如果连接成功，获取连接状态和实时信息
	char szStatus[64] = {0};
	char szText[128] = {0};
	int nWaitTime = 1000;
	while (pDlg->m_hEventQuit)
	{
		if(!pDlg->m_pVideoIns)
		{
			return FALSE;
		}
		
		BOOL bOnlineState =  CU_NET_LIB::GetMediaState(g_dwServerId, pDlg->m_pVideoIns->m_hVideo);
		if(bOnlineState)
		{			
			// 显示视频状态
			CU_NET_LIB::MEDIA_DATA_INFO mediaInfo;
			CU_NET_LIB::GetMediaInfo(g_dwServerId, pDlg->m_pVideoIns->m_hVideo, &mediaInfo);
			nWaitTime = 1000;
		}
		else
		{
			BOOL bRet = pDlg->m_pVideoIns->Reconnect();
			if(bRet)
			{
				strLoadText="[系统消息]正在重新请求视频";
                sprintf(szStatus, (const char *)strLoadText.GetBuffer(strLoadText.GetLength()));	
			}
			else
			{
				strLoadText="[系统消息]等待重新连接";
                sprintf(szStatus, (const char *)strLoadText.GetBuffer(strLoadText.GetLength()));	
			}
            TRACE(_T("-----------m_pVideoIns->Reconnect=-------%s\n"), szStatus);
			nWaitTime = 3000;

			pDlg->TextOutOperation(strLoadText);
		}
		pDlg->m_strNotiy.Format(_T("%s"), szText);
		if(WAIT_OBJECT_0 == ::WaitForSingleObject(pDlg->m_hEventQuit, nWaitTime))
			break;
	}
	return TRUE;
}

void CMainPage::OnBtnCloseVideo() 
{
	// TODO: Add your control notification handler code here
	if (m_bSoundAllow)
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_OPENSOUND, BN_CLICKED), (LPARAM)GetDlgItem(IDC_BTN_OPENSOUND)->GetSafeHwnd());
	}

	if (m_bRecord)
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_LOCALRECORD, BN_CLICKED), (LPARAM)GetDlgItem(IDC_BTN_LOCALRECORD)->GetSafeHwnd());
	}

	if (m_bSoundRecord)
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_LOCALSOUNDRECORD, BN_CLICKED), (LPARAM)GetDlgItem(IDC_BTN_LOCALSOUNDRECORD)->GetSafeHwnd());
	}

	if (m_bVoice)
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_OPENVOICE, BN_CLICKED), (LPARAM)GetDlgItem(IDC_BTN_OPENVOICE)->GetSafeHwnd());
	}

	StopStream();
	DestroyPlayInstance();

	m_bOpenVideo = FALSE;
	GetDlgItem(IDC_BTN_OPEN_VIDEO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CLOSE_VIDEO)->EnableWindow(FALSE);
	CString str("关闭视频");
	TextOutOperation(str);
}

void CMainPage::OnBtnOpensound() 
{
	// TODO: Add your control notification handler code here
	if (!m_bStreamOpenFlag || m_play_id == 0)
	{
		return;
	}
	
	m_bSoundAllow = !m_bSoundAllow;
	
	if (m_bSoundAllow)
	{
		player_openSound(m_play_id);
		GetDlgItem(IDC_BTN_OPENSOUND)->SetWindowText(_T("关闭声音"));
		CString str("打开声音操作成功");
		TextOutOperation(str);
	}
	else
	{
		player_closeSound(m_play_id);
		GetDlgItem(IDC_BTN_OPENSOUND)->SetWindowText(_T("打开声音"));
		CString str("关闭声音操作成功");
		TextOutOperation(str);
	}
}

void CMainPage::OnBtnOpenvoice()
{
	if(!m_bStreamOpenFlag || m_play_id == 0)
	{
		return;
	}

	if (!m_bLoginFlag)
	{
		return;
	}
	if(0 == (m_GuInfo.right & RIGHT_AUDIOTALK))	
	{
		return;
	}
	
	
	if ( m_bVoice == FALSE )
	{
		m_bVoice = StartVoice();
		if ( this->m_bVoice == TRUE)
		{
			GetDlgItem(IDC_BTN_OPENVOICE)->SetWindowText(_T("停止语音对讲"));
			CString str("开始语音对讲");
			TextOutOperation(str);
		}
	}
	else
	{		
		StopChart();
		this->m_bVoice = FALSE;
		GetDlgItem(IDC_BTN_OPENVOICE)->SetWindowText(_T("开启语音对讲"));
		CString str("停止语音对讲");
		TextOutOperation(str);
		
	}
}

BOOL CMainPage::StartVoice()
{
	CString strLoadText,strLoadText1;
	
	// 先停止音频捕捉和发送
	StopChart();
	
	// 启动音频连接__阻塞调用
	CU_NET_LIB::CLIENTINFO client;
	client.lHandle = (long)this;
	client.lpFunc = RecAudioDataFunc;
	client.nProtocolType = 1;
	HRESULT hr = CU_NET_LIB::ChartWithOne(g_dwServerId, m_GuInfo, 1, client); 
	if(ST_OK != hr)
	{
		MessageBox(_T("语音呼叫失败！"), _T("错误"), MB_ICONSTOP|MB_OK);		
		return FALSE;
	}
	else
	{
		AudioTalkConfig_t mAudioTalk;
		ZeroMemory(&mAudioTalk, sizeof(AudioTalkConfig_t));
		mAudioTalk.iRate = 8000;
		mAudioTalk.iWidth = 16;
		mAudioTalk.iFormat = 1;
		mAudioTalk.iAmr_mode = 7;
		mAudioTalk.iAmr_format = 0;		
		
		if(player_startDualTalk(g_dwAudioInstance, &mAudioTalk) != 0)
		{
			g_dwAudioInstance = 0;
			CU_NET_LIB::StopChart(g_dwServerId);
			MessageBox(_T("语音呼叫失败, 音频设备初始化失败！"),  _T("提示"), MB_ICONSTOP|MB_OK);
			
			return FALSE;
		}
		player_registerSetDualCallback(g_dwAudioInstance, DualDataFunc, (DWORD)this);		
	}
	
	return TRUE;
}

void CMainPage::StopChart()
{
	if (!m_bLoginFlag)
	{
		return;
	}
	if(0 == (m_GuInfo.right & RIGHT_AUDIOTALK))	
	{
		return;
	}
	
	if ( m_bVoice == TRUE )
	{
		player_stopDualTalk(g_dwAudioInstance);
		CU_NET_LIB::StopChart(g_dwServerId);
		Sleep(100);
	}
}

BOOL CMainPage::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CMainPage::GetYTControlCmd(int iMessage, char *szCmd, char *szParam)
{
	BOOL IsLeftBtnDown = FALSE;
	BOOL bSelFlag = FALSE;
	RECT rcBtn;

	POINT pt;
	GetCursorPos(&pt);

	//---------------------------------------
	// 如果是左键事件
	//---------------------------------------
	if( iMessage == WM_LBUTTONDOWN)
	{
		//------------------------------------------------
		// 运动部份
		//------------------------------------------------

		  //--向上--
		GetDlgItem(IDC_BTN_UP)->GetWindowRect(&rcBtn);
		if( ::PtInRect(&rcBtn,pt) )
		{
			sprintf(szCmd, (const char *)_T("TU"));
			sprintf(szParam, (const char *)_T("0"));
			bSelFlag = TRUE;
		}

		  //--向下--
		GetDlgItem(IDC_BTN_DOWN)->GetWindowRect(&rcBtn);
		if( PtInRect(&rcBtn,pt) )
		{
			sprintf(szCmd, (const char *)_T("TD"));
			sprintf(szParam, (const char *)_T("0"));
			bSelFlag = TRUE;
		
		}

		  //--向左--
	    GetDlgItem(IDC_BTN_LEFT)->GetWindowRect(&rcBtn);
	    if( PtInRect(&rcBtn, pt) )
		{
			sprintf(szCmd, (const char *)_T("PL"));
			sprintf(szParam, (const char *)_T("0"));
			bSelFlag = TRUE;
		
		}

          //--向右--
		GetDlgItem(IDC_BTN_RIGHT)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn, pt) )
		{
			sprintf(szCmd, (const char *)_T("PR"));
			sprintf(szParam, (const char *)_T("0"));
			bSelFlag = TRUE;

		}

		//--------------------------------------------------
		// 图像部份
		//--------------------------------------------------

		  //光圈+ 开始--
		GetDlgItem(IDC_BUTTON_LENS1)->GetWindowRect(&rcBtn);
		if( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"IC");
			sprintf(szParam,"0");
			bSelFlag = TRUE;
		}
		
		  //光圈- 开始--
		GetDlgItem(IDC_BUTTON_LENS2)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"IO");
			sprintf(szParam,"0");
			
			bSelFlag = TRUE;
		}
		
		  //聚焦+ 开始--
		GetDlgItem(IDC_BUTTON_FOCUS1)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"FN");
			sprintf(szParam,"0");
			
			bSelFlag = TRUE;
		}
		
		  //聚焦- 开始--
		GetDlgItem(IDC_BUTTON_FOCUS2)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"FR");
			sprintf(szParam,"0");
			
			bSelFlag = TRUE;
		}
		
		  //变倍+ 开始--
		GetDlgItem(IDC_BUTTON_ZOOM1)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"ZIN");
			sprintf(szParam,"0");
			
			bSelFlag = TRUE;
		}
		
		  //变倍- 开始--
		GetDlgItem(IDC_BUTTON_ZOOM2)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"ZOUT");
			sprintf(szParam,"0");
			
			bSelFlag = TRUE;
		}

	}
	else    //---非左键消息---//
	{
		//------------------------------------------------
		// 运动部份
		//------------------------------------------------

		  //--停止向上--
		GetDlgItem(IDC_BTN_UP)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn, pt))
		{
			sprintf(szCmd, (const char *)_T("STOP"));
			sprintf(szParam, (const char *)_T("TU"));
	        bSelFlag = TRUE;
		}


		  //--停止向下--
		GetDlgItem(IDC_BTN_DOWN)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn, pt))
		{
			sprintf(szCmd, (const char *)_T("STOP"));
			sprintf(szParam, (const char *)_T("TD"));
			bSelFlag = TRUE;

		}


	      //--停止向左--
		GetDlgItem(IDC_BTN_LEFT)->GetWindowRect(&rcBtn);
		if( PtInRect(&rcBtn,pt) )
		{
			sprintf(szCmd, (const char *)_T("STOP"));
			sprintf(szParam, (const char *)_T("PL"));
			bSelFlag = TRUE;
			
		}

		  //--停止向右--
		GetDlgItem(IDC_BTN_RIGHT)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt) )
		{
			sprintf(szCmd, (const char *)_T("STOP"));
			sprintf(szParam, (const char *)_T("PR"));
			bSelFlag = TRUE;
			
		}


		//--------------------------------------------------
		// 图像部份
		//--------------------------------------------------

          //光圈+ 开始--
		GetDlgItem(IDC_BUTTON_LENS1)->GetWindowRect(&rcBtn);
		if( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"STOP");
			sprintf(szParam,"IC");
			bSelFlag = TRUE;
		}

          //光圈- 开始--
		GetDlgItem(IDC_BUTTON_LENS2)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"STOP");
			sprintf(szParam,"IO");

			bSelFlag = TRUE;
		}

          //聚焦+ 开始--
		GetDlgItem(IDC_BUTTON_FOCUS1)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"STOP");
			sprintf(szParam,"FN");

			bSelFlag = TRUE;
		}

          //聚焦- 开始--
		GetDlgItem(IDC_BUTTON_FOCUS2)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"STOP");
			sprintf(szParam,"FR");

			bSelFlag = TRUE;
		}

          //变倍+ 开始--
		GetDlgItem(IDC_BUTTON_ZOOM1)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"STOP");
			sprintf(szParam,"ZIN");

			bSelFlag = TRUE;
		}

          //变倍- 开始--
		GetDlgItem(IDC_BUTTON_ZOOM2)->GetWindowRect(&rcBtn);
		if ( PtInRect(&rcBtn,pt))
		{
			sprintf(szCmd,"STOP");
			sprintf(szParam,"ZOUT");

			bSelFlag = TRUE;
		}

	}
	return bSelFlag;
}

void CMainPage::OnBtnReplay() 
{
	// TODO: Add your control notification handler code here
	if (m_dlgPlayList.GetSafeHwnd() == NULL)
    {
		m_dlgPlayList.Create(CDlgPlayList::IDD, this);
    }
	
	m_dlgPlayList.SetMainPage(this);
	m_dlgPlayList.SetGuInfo(&m_GuInfo);
	m_dlgPlayList.InitCmbCtrls();
	m_dlgPlayList.ShowWindow(SW_SHOW);
}

BOOL CMainPage::MakeDir(char* filePath)
{  
	if ( filePath == '\0')
	{
		return FALSE;
	}
	
	int m = 0, n = 0;   
	char   temp[255];  
	
	while(1)   
	{   
		//字符串结束---
		if(filePath[n] == '\0')
		{   
			break;   
		}  
		
		//逐个获取文件夹的名称---
		temp[m] = filePath[n]; 
		
		//当得到一个完整的文件夹名---
		if(temp[m]=='\\' && temp[m-1] != '.')
		{
			temp[m]   =   '\0'; 
			
			//先检查当前要创建的文件夹是否存在---
			if ( _access(temp,00) != 0 )
			{
				//不存在则生成---
				int result = _mkdir(temp);
				if ( result != 0)
				{
					return FALSE;
				}
			}
			
			//继续生成子目录---
			temp[m]   =   '\\';   
			temp[++m]   =   '\0';   
			n++;   
		}   
		else
		{   
			n++;   
			m++;   
		}   
	}   
	
	return TRUE;
}

void CMainPage::OnDestroy() 
{
	CDialog::OnDestroy();
	Sleep(300);
	// TODO: Add your message handler code here
	if (m_bOpenVideo == TRUE)
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_CLOSE_VIDEO, BN_CLICKED), (LPARAM)GetDlgItem(IDC_BTN_CLOSE_VIDEO)->GetSafeHwnd()); 
	}

	SendMessage(WM_CLEARDEVICELIST, NULL, NULL);//清除动态申请的内存
}

void CMainPage::OnBtnUp() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnBtnRight() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnBtnLeft() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnBtnDown() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnBtnAuto() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::ProcessCameraDirection()
{
	BOOL bRet;
	char szCmd[24] = {0};
	char szParam[24] = {0};
	
	if (m_GuInfo.nptzlevel == 0)
	{
		return;
	}
	
	
	bRet = GetYTControlCmd(WM_LBUTTONDOWN, szCmd, szParam);
	if ( bRet )
	{
		ptz_control_t *ptz_control = new ptz_control_t; 
		
		ptz_control->guInfo = m_GuInfo;
		memset(ptz_control->param,0,sizeof(ptz_control->param));
		memset(ptz_control->cmd,0,sizeof(ptz_control->cmd));
		
		strncpy(ptz_control->cmd, szCmd, sizeof(ptz_control->cmd));
		strncpy(ptz_control->param, szParam, sizeof(ptz_control->param));
// 		ptz_control->speed = m_ctrlSpeed.GetPos() / 10; 
		
		strncpy(ptz_control->csgIp, (const char *)m_strServerIPAddr.GetBuffer(m_strServerIPAddr.GetLength()), sizeof(ptz_control->csgIp));
		ptz_control->csgport =  m_nServerPort + PORT_CSG_INCREASE_NUM;
		
		sprintf(ptz_control->msgtype,"ControlPTZ");
		
		m_CameraCtrl.PushBack(ptz_control);
		Sleep(1);
	}
}

void CMainPage::OnBtnRemotePic() 
{
	// TODO: Add your control notification handler code here
	if(!m_bStreamOpenFlag)
	{
		return;
	}
	
    CString strLoadText;
	CU_NET_LIB::GUINFO guInfo = m_GuInfo;
	
	//前端抓拍接口---
	HRESULT hr = CU_NET_LIB::RemoteCapturePic(g_dwServerId, guInfo);
	if(ST_OK == hr)
	{
		CString str("远端拍照操作成功");
		TextOutOperation(str);
		AfxMessageBox("操作成功!",MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		AfxMessageBox("操作失败!");
	}
}

void CMainPage::OnButtonFocus1() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnButtonFocus2() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnButtonLens1() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnButtonLens2() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnButtonZoom1() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnButtonZoom2() 
{
	// TODO: Add your control notification handler code here
	ProcessCameraDirection();
}

void CMainPage::OnReleasedcaptureSliderBright(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetVideoParam();
	*pResult = 0;
}

void CMainPage::OnReleasedcaptureSliderContrast(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetVideoParam();
	*pResult = 0;
}

void CMainPage::OnReleasedcaptureSliderHue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetVideoParam();
	*pResult = 0;
}

void CMainPage::OnReleasedcaptureSliderSaturation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetVideoParam();
	*pResult = 0;
}

void CMainPage::SetVideoParam()
{
	CU_NET_LIB::GUINFO *pGuInfo = &m_GuInfo;
	if(pGuInfo == NULL)
		return;
	
	int contrast, bright, hue, saturation;
	contrast = m_sliderContrast.GetPos();
	bright = m_sliderBright.GetPos();
	hue = m_sliderHue.GetPos();
	saturation = m_sliderSaturation.GetPos();
	
	HRESULT hr;
	hr = CU_NET_LIB::SetPuImageDisplayPara(g_dwServerId, *pGuInfo, contrast, bright, hue, saturation);
	if(hr != ST_OK )
	{
		//PromptSetFailed;
		return;
	}
	//PromptSetSucceeded;
}

void CMainPage::OnBtnLocalpic() 
{
	// TODO: Add your control notification handler code here
	CString strLoadText;
	if(m_bStreamOpenFlag && m_play_id != 0)
	{
		if(0 == (m_GuInfo.right & RIGHT_LOCALRECORD))
		{
			return;
		}
		
		char  szPath[1024] = {0};
		CString strPath;
		_bstr_t bstrFile;
		
		if (!m_strWorkDir.IsEmpty())
		{
			sprintf(szPath, "%s", m_strWorkDir.GetBuffer(m_strWorkDir.GetLength()));
		}
		else
		{
			sprintf(szPath, "%s", (LPCTSTR)"");
		}
		
		// 根据GUID和日期时间确定文件名称
		CU_NET_LIB::GUINFO guInfo;
		guInfo = m_GuInfo;
		
		try
		{
			SYSTEMTIME systime;
			::GetLocalTime(&systime);
			// 检查路径, 修正路径
			char szFilePath[1024] = {0};
			int nLen = (int)strlen(szPath);
			if(nLen <=0)
			{
				//当前文件夹'.\'也要写上---
				strPath.Format("\\%s%s\\Picture\\%04d%02d%02d\\", "", guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
				sprintf(szFilePath, "%s", (LPCTSTR)strPath);
			}
			else
			{
				if(szPath[nLen-1] != '\\')
				{
					strcat(szPath, "\\");
				}
				strPath.Format("%s%s\\Picture\\%04d%02d%02d\\", szPath, guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
				sprintf(szFilePath, "%s", strPath);
			}			
			
			if(_access(szFilePath, 00) !=0 )
			{
				BOOL bResult = MakeDir(szFilePath);
				if( bResult == FALSE )
				{
					AfxMessageBox(_T("创建文件夹失败，请重新操作！"), MB_OK | MB_ICONERROR);
					return;
				}
			}
			
			CString strFile;
			strFile.Format(_T("%s%02d_%02d_%02d.bmp"), (LPCTSTR)strPath, systime.wHour,systime.wMinute,systime.wSecond);
			bstrFile = _bstr_t((LPCTSTR)strFile);
			
			// 抓拍接口----
			player_capturePicture(m_play_id, bstrFile);
		}
		catch(...)
		{
			AfxMessageBox("异常错误, 请检查快照保存路径的设置项");
			return;
		}
		
		CString str("本地拍照操作成功");
		TextOutOperation(str);
		//---------------------------------------
		// 显示图片
		//---------------------------------------
		char *pPath = new char[1024];
		memset(pPath, 0x00, 1024);
		memcpy(pPath, LPCTSTR(bstrFile), strlen((LPCTSTR)bstrFile));
		PostMessage(WM_SHOWCAPTUREPIC, WPARAM(pPath), NULL);
	}
}

void CMainPage::OnBtnLocalrecord() 
{
	// TODO: Add your control notification handler code here
	if(!m_bStreamOpenFlag || m_play_id == 0)
	{
		return;
	}

	if (m_bRecord == FALSE)
	{
		DoRecord();
		GetDlgItem(IDC_BTN_LOCALRECORD)->SetWindowText(_T("停止本地录像"));
		m_bRecord = TRUE;
		CString str("开始本地录像");
		TextOutOperation(str);
	}
	else
	{
		m_bRecord = FALSE;
		Sleep(20);
		CloseRecordFile();
		GetDlgItem(IDC_BTN_LOCALRECORD)->SetWindowText(_T("本地录像"));
		CString str("停止本地录像");
		TextOutOperation(str);
	}
}

void CMainPage::DoRecord()
{
	CString strLoadText,strLoadText1;
	// 根据设定路径和其他要素创建录象文件
	CString strPath = _T("");
	CString strFile = _T("");
	CString strDir = _T("");
	char  szFilePath[1024] = {0};
	CU_NET_LIB::GUINFO guInfo;
	guInfo = m_GuInfo;
	m_bSwitchRecordFile = FALSE;
	
	if (!m_strWorkDir.IsEmpty())
	{
		strDir = m_strWorkDir;
	}
	else
	{
		strDir = _T(".");
	}
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	strPath.Format("%s\\%s\\Record\\%04d%02d%02d\\", strDir, guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
	strFile.Format("%s%02d_%02d_%02d%s", strPath, systime.wHour,systime.wMinute,systime.wSecond,
		(LPCTSTR)GetRecFileExt(guInfo.lManufactType));
	
	sprintf(szFilePath, "%s", (LPCTSTR)strPath);
	
	CString strMsg = _T("");
	try
	{
		int nPos = -1;
		int nStart = 0;
		
		if(_access(szFilePath,0)!=0)   
			MakeDir(szFilePath);
		
		sprintf(szFilePath, "%s", strFile);
		
		if (m_lManufactType == HK8016_PLAY_SDK)
		{
			m_Recordfile = fopen(szFilePath, _T("wb"));
			if(!m_Recordfile)
				return;
			
			if (fwrite(&g_HK8016_HeadBuf, 40, 1, (FILE*)m_Recordfile) < 0)
			{
				fclose((FILE*)m_Recordfile);
				m_Recordfile = NULL;
				return;
			}
		}
		else if (m_lManufactType == HK8116_PLAY_SDK)
		{
			m_Recordfile = fopen(szFilePath, _T("wb"));
			if(!m_Recordfile)
				return;
			
			if (fwrite(&g_HK8116_HeadBuf, 40, 1, (FILE*)m_Recordfile) < 0)
			{
				fclose((FILE*)m_Recordfile);
				m_Recordfile = NULL;
				return;
			}
		}
		else
		{
			m_hRecordFileRec = AVI_fopen(szFilePath, AVI_WRITE);
			if(m_hRecordFileRec == NULL)
			{
				m_hRecordFileRec = NULL;
				strMsg.Format(_T("创建录象文件失败！\nErrCode:%d"), ::GetLastError());
				AfxMessageBox(strMsg);
				return;
			}
			
		}
	}
	catch(...)
	{
		m_hRecordFileRec = NULL;
		AfxMessageBox(_T("创建录象文件失败！"));
		return;
	}
	TRACE("Command: Start Record!!!!\n");
	m_bRecord = !m_bRecord;//切换录像状态
}

CString CMainPage::GetRecFileExt(long lCompanyCode)
{
	CString strRecFileExt = _T(".avi");
	if (lCompanyCode == HK8016_PLAY_SDK || lCompanyCode == HK8116_PLAY_SDK)
		strRecFileExt = _T(".hk");
	else if (lCompanyCode == HB_PLAY_SDK)
		strRecFileExt = _T(".hb");
	else if (lCompanyCode == DH_PLAY_SDK)
		strRecFileExt = _T(".dh");
	return strRecFileExt;
}

void CMainPage::CloseRecordFile()
{
	m_bSwitchRecordFile = FALSE;
	Sleep(200);

	if(m_hRecordFileRec != NULL)
	{ 
		AVI_fclose(m_hRecordFileRec);
		m_hRecordFileRec = NULL;
	}
	if (m_Recordfile != NULL)
	{
		fclose((FILE*)m_Recordfile);
		m_Recordfile = NULL;
	}
}

BOOL CMainPage::CreateRecordFile()
{
	CloseRecordFile();
    CString strLoadText;
	CString  strPath = _T("");
	CString  strFile = _T("");
	char szFilePath[510] = {0};
	
	CU_NET_LIB::GUINFO guInfo = m_DevInfo.guInfo;
	
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	strPath.Format(".\\%s\\Record\\%04d%02d%02d\\", guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
	strFile.Format("%s%02d_%02d_%02d%s", strPath, systime.wHour,systime.wMinute,systime.wSecond,
		(LPCTSTR)GetRecFileExt(guInfo.lManufactType));
	sprintf(szFilePath, "%s", (LPCTSTR)strPath);
	
	CString strMsg = _T("");
	try
	{
		if(_access(szFilePath,0)!=0)   
			MakeDir(szFilePath);
		
		sprintf(szFilePath, "%s", strFile);
		m_hRecordFileRec = AVI_fopen(szFilePath, AVI_WRITE);
		if(m_hRecordFileRec == NULL)
		{
			m_hRecordFileRec = NULL;
			return FALSE;
		}
		
		if (m_lManufactType == HK8016_PLAY_SDK)
		{
			m_Recordfile = fopen(szFilePath, "wb");
			if(!m_Recordfile)
				return FALSE;
			
			if (fwrite(&g_HK8016_HeadBuf, 40, 1, (FILE*)m_Recordfile) < 0)
			{
				fclose((FILE*)m_Recordfile);
				m_Recordfile = NULL;
				return FALSE;
			}
		}
		else if (m_lManufactType == HK8116_PLAY_SDK)
		{
			m_Recordfile = fopen(szFilePath, "wb");
			if(!m_Recordfile)
				return FALSE;
			
			if (fwrite(&g_HK8116_HeadBuf, 40, 1, (FILE*)m_Recordfile) < 0)
			{
				fclose((FILE*)m_Recordfile);
				m_Recordfile = NULL;
				return FALSE;
			}
		}
		else
		{
			m_hRecordFileRec = AVI_fopen(szFilePath, AVI_WRITE);
			if(m_hRecordFileRec == NULL)
			{
				m_hRecordFileRec = NULL;
				strMsg.Format("创建录象文件失败! ErrCode:%d\n", ::GetLastError());
				TRACE("CVideoButton::CreateRecordFile() --- %s\n", strMsg);
				return FALSE;
			}
			
		}		
	}
	catch(...)
	{
		m_hRecordFileRec = NULL;
		return FALSE;
	}
	return TRUE;
}

void CMainPage::OnShowCapturePic(WPARAM wParam, LPARAM lParam)
{
	char *pPath = (char *)wParam;
	CString strPath;
	strPath.Format(_T("%s"), pPath);
	delete []pPath;

	CDlgPicView dlg;
	dlg.SetFilePath(strPath);
	dlg.DoModal();
}

void CMainPage::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (cx < 600 || cy < 450)
	{
		return;
	}
	//一种简单的控件onsize的方法

	//请参照资源IDD_PROPPAGE_MAIN

	int i = 0;
	int iCnt = 0;
	int iOffset = 0;
	int iPix = 17;
	CRect rc;
	//与右边框距离恒为7像素的控件
	UINT ui_7pixToRight[] = {IDC_STATIC_DEVICE, IDC_EDIT_DEVICE, IDC_BTN_REPLAY,
						IDC_BTN_REMOTE_PIC, IDC_BTN_LOCALSOUNDRECORD, IDC_LIST_OP};
	iCnt = sizeof(ui_7pixToRight) / sizeof(UINT);
	for (i = 0; i < iCnt; i++)
	{
		CWnd *pWnd = GetDlgItem(ui_7pixToRight[i]);
		if (pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			iOffset = cx - iPix - rc.right;
			rc.OffsetRect(iOffset, 0);
			pWnd->MoveWindow(rc);
		}
	}


	//与右边框距离恒为100像素的控件
	iPix = 105;
	UINT ui_100pixToRight[] = {IDC_BTN_CLOSE_VIDEO, IDC_BTN_OPENVOICE, IDC_BTN_LOCALRECORD};
	iCnt = sizeof(ui_100pixToRight) / sizeof(UINT);
	for (i = 0; i < iCnt; i++)
	{
		CWnd *pWnd = GetDlgItem(ui_100pixToRight[i]);
		if (pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			iOffset = cx - iPix - rc.right;
			rc.OffsetRect(iOffset, 0);
			pWnd->MoveWindow(rc);
		}
	}


	//与右边框距离恒为187像素的控件
	iPix = 195;
	UINT ui_187pixToRight[] = {IDC_BTN_OPEN_VIDEO, IDC_BTN_OPENSOUND, IDC_BTN_LOCALPIC};
	iCnt = sizeof(ui_187pixToRight) / sizeof(UINT);
	for (i = 0; i < iCnt; i++)
	{
		CWnd *pWnd = GetDlgItem(ui_187pixToRight[i]);
		if (pWnd && pWnd->GetSafeHwnd())
		{
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			iOffset = cx - iPix - rc.right;
			rc.OffsetRect(iOffset, 0);
			pWnd->MoveWindow(rc);
		}
	}

	iOffset = cx - 293;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_PREVIEW);
	if (pWnd && pWnd->GetSafeHwnd())
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.right = iOffset;
		rc.bottom = cy - 27;
		pWnd->MoveWindow(rc);
	}


	//操作editbox
	pWnd = GetDlgItem(IDC_LIST_OP);
	if (pWnd && pWnd->GetSafeHwnd())
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.bottom = cy - 27;
		pWnd->MoveWindow(rc);
	}
}

void CMainPage::InVisibleCtrls()
{
	UINT uiCtrlsID[] = {IDC_BTN_UP, IDC_BTN_DOWN, IDC_BTN_LEFT,
					IDC_BTN_RIGHT, IDC_BTN_AUTO, IDC_BUTTON_LENS1,
					IDC_BUTTON_LENS2, IDC_BUTTON_FOCUS1, IDC_BUTTON_FOCUS2,
					IDC_BUTTON_ZOOM1, IDC_BUTTON_ZOOM2, IDC_SLIDER_BRIGHT,
					IDC_SLIDER_CONTRAST, IDC_SLIDER_HUE, IDC_SLIDER_SATURATION,
					IDC_STATIC_OPARATION, IDC_STATIC_LENS, IDC_STATIC_FOCUS,
					IDC_STATIC_ZOOM, IDC_STATIC_BRIGHT, IDC_STATIC_CONTRAST,
					IDC_STATIC_HUE, IDC_STATIC_SATURATION};

	int iCnt = sizeof(uiCtrlsID) / sizeof(UINT);
	for (int i = 0; i < iCnt; i++)
	{
		GetDlgItem(uiCtrlsID[i])->ShowWindow(SW_HIDE);
	}
}

void CMainPage::OnBtnLocalsoundrecord() 
{
	// TODO: Add your control notification handler code here
	if(!m_bStreamOpenFlag || m_play_id == 0)
	{
		return;
	}
	
	if (m_bSoundRecord == FALSE)
	{
		DoSoundRecord();
		GetDlgItem(IDC_BTN_LOCALSOUNDRECORD)->SetWindowText(_T("停止本地录音"));
		m_bSoundRecord = TRUE;
		CString str("开始本地录音");
		TextOutOperation(str);
	}
	else
	{
		m_bSoundRecord = FALSE;
		Sleep(20);
		CloseSoundRecordFile();
		GetDlgItem(IDC_BTN_LOCALSOUNDRECORD)->SetWindowText(_T("本地录音"));
		CString str("停止本地录音");
		TextOutOperation(str);
	}
}

void CMainPage::DoSoundRecord()
{
	CString strLoadText,strLoadText1;
	// 根据设定路径和其他要素创建录音文件
	CString strPath = _T("");
	CString strFile = _T("");
	CString strDir = _T("");
	char  szFilePath[1024] = {0};
	CU_NET_LIB::GUINFO guInfo;
	guInfo = m_GuInfo;
	m_bSwitchSoundFile = FALSE;
	
	if (!m_strWorkDir.IsEmpty())
	{
		strDir = m_strWorkDir;
	}
	else
	{
		strDir = _T(".");
	}
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	strPath.Format("%s\\%s\\SoundRecord\\%04d%02d%02d\\", strDir, guInfo.GUName, systime.wYear, systime.wMonth,systime.wDay);
	strFile.Format("%s%02d_%02d_%02d%s", strPath, systime.wHour,systime.wMinute,systime.wSecond,
		(LPCTSTR)GetRecFileExt(guInfo.lManufactType));
	
	sprintf(szFilePath, "%s", (LPCTSTR)strPath);
	
	CString strMsg = _T("");
	try
	{
		int nPos = -1;
		int nStart = 0;
		
		if(_access(szFilePath,0)!=0)   
			MakeDir(szFilePath);
		
		sprintf(szFilePath, "%s", strFile);
		
		if (m_lManufactType == HK8016_PLAY_SDK)
		{
			m_SoundFile = fopen(szFilePath, _T("wb"));
			if(!m_SoundFile)
				return;
			
			if (fwrite(&g_HK8016_HeadBuf, 40, 1, (FILE*)m_SoundFile) < 0)
			{
				fclose((FILE*)m_SoundFile);
				m_SoundFile = NULL;
				return;
			}
		}
		else if (m_lManufactType == HK8116_PLAY_SDK)
		{
			m_SoundFile = fopen(szFilePath, _T("wb"));
			if(!m_Recordfile)
				return;
			
			if (fwrite(&g_HK8116_HeadBuf, 40, 1, (FILE*)m_SoundFile) < 0)
			{
				fclose((FILE*)m_SoundFile);
				m_SoundFile = NULL;
				return;
			}
		}
		else
		{
			m_hSoundFileRec = AVI_fopen(szFilePath, AVI_WRITE);
			if(m_hSoundFileRec == NULL)
			{
				m_hSoundFileRec = NULL;
				strMsg.Format(_T("创建录音文件失败！\nErrCode:%d"), ::GetLastError());
				AfxMessageBox(strMsg);
				return;
			}
		}
	}
	catch(...)
	{
		m_hSoundFileRec = NULL;
		AfxMessageBox(_T("创建录音文件失败！"));
		return;
	}
	TRACE("Command: Start Sound Record!!!!\n");
	m_bSoundRecord = !m_bSoundRecord;//切换录音状态
}

void CMainPage::CloseSoundRecordFile()
{
	m_bSwitchSoundFile = FALSE;
	Sleep(200);
	
	if(m_hSoundFileRec != NULL)
	{ 
		AVI_fclose(m_hSoundFileRec);
		m_hSoundFileRec = NULL;
	}
	if (m_SoundFile != NULL)
	{
		fclose((FILE*)m_SoundFile);
		m_SoundFile = NULL;
	}
}

void CMainPage::TextOutOperation(CString &str)
{
	CListCtrl *pList = (CListCtrl*)GetDlgItem(IDC_LIST_OP);
	if (pList && pList->GetSafeHwnd())
	{
		CTime t = CTime::GetCurrentTime();
		int iIndex = pList->InsertItem(pList->GetItemCount(), (LPCTSTR)t.Format(_T("%H:%M:%S")));
		pList->SetItemText(iIndex, 1, (LPCTSTR)str);

		if (pList->GetItemCount() > 0)
		{
			pList->EnsureVisible(pList->GetItemCount() - 1, FALSE);
		}
	}
}