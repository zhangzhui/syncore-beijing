// TimeRecRuntime.cpp: implementation of the CTimeRecRuntime class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TimeRecRuntime.h"
#include "VideoInstance.h"
#include "VideoManage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVideoManage   g_VideoMng;
void CheckDiskThread(void * param);

CTimeRecRuntime::CTimeRecRuntime()
{
	m_bRefreshState = FALSE;
	m_hCheckThread = NULL;
	m_nDriverIndex = 0;
	m_bAutoFlag = FALSE;
}


CTimeRecRuntime::~CTimeRecRuntime()
{
	DelRuntimeInfo();
}

//加载全局配置文件
BOOL CTimeRecRuntime::LoadRuntimeInfo()
{
	char szFileName[MAX_PATH] = {0};
	char szTemp[128] = {0};
	char buf[128];
	//CString strDrive[128];
	int iCount=0;
	
	
	CString strFileName;
	strFileName.Format(_T("\\TimeRec_Cfg.ini"));
	GetModuleFileName(NULL, /*(unsigned short *)*/szFileName, MAX_PATH);
	*strrchr(szFileName,_T('\\')) = '\0';
	strcat(szFileName, (const char *)strFileName.GetBuffer(strFileName.GetLength()));

	if((_access(szFileName,0)) ==  -1)//中间文件不存在   
	{   
		FILE *fp = fopen(szFileName, "wb+");
		fclose(fp);   
	}   
	
	memset(buf,0,sizeof(buf));
	GetPrivateProfileString(_T("DISKCONFIG"), _T("RESSIZE"), _T(""), /*(unsigned short *)*/buf, sizeof(buf), /*(unsigned short *)*/szFileName);
	if(strlen(buf)==0)
	{
		CString strSec, strKey, strValue, strDiskLst;
		
		strSec = "DISKCONFIG";
		strKey = "RESSIZE";
		strValue.Format(_T("%d"), 256);
		::WritePrivateProfileString(strSec, strKey, strValue, /*(unsigned short *)*/szFileName);
		
		strKey = "SWITCHTIME";
		strValue.Format(_T("%d"), 5);
		::WritePrivateProfileString(strSec, strKey, strValue, /*(unsigned short *)*/szFileName);
		
		strKey = "COVERFLAG";
		strValue.Format(_T("%d"), 1);
		::WritePrivateProfileString(strSec, strKey, strValue, /*(unsigned short *)*/szFileName);

		strKey = "AUTOFLAG";
		strValue.Format(_T("%d"), 0);
		::WritePrivateProfileString(strSec, strKey, strValue, /*(unsigned short *)*/szFileName);
		
		char szSystemDir[256];
		GetSystemDirectory(/*(unsigned short *)*/szSystemDir, 256);
		strDiskLst.Format(_T("%C:"),szSystemDir[0]);
		
		//strDiskLst = "C:";
		strKey = "NAME";
		::WritePrivateProfileString(strSec, strKey, strDiskLst, /*(unsigned short *)*/szFileName);
	}
	
	
	
	memset(buf,0,sizeof(buf));
	GetPrivateProfileString(_T("DISKCONFIG"), _T("RESSIZE"), _T(""), /*(unsigned short *)*/buf, sizeof(buf), /*(unsigned short *)*/szFileName);
	if(strlen(buf)==0)
		return FALSE;
	m_iResSize = atoi(buf);
	
	memset(buf,0,sizeof(buf));
	GetPrivateProfileString(_T("DISKCONFIG"), _T("COVERFLAG"), _T(""), /*(unsigned short *)*/buf, sizeof(buf), /*(unsigned short *)*/szFileName);
	if(strlen(buf)==0)
		return FALSE;
	m_bCoverFlag = atoi(buf);

	memset(buf,0,sizeof(buf));
	GetPrivateProfileString(_T("DISKCONFIG"), _T("AUTOFLAG"), _T(""), /*(unsigned short *)*/buf, sizeof(buf), /*(unsigned short *)*/szFileName);
	if(strlen(buf)==0)
		return FALSE;
	m_bAutoFlag = atoi(buf);
	
	memset(buf,0,sizeof(buf));
    GetPrivateProfileString(_T("DISKCONFIG"), _T("SWITCHTIME"), _T(""), /*(unsigned short *)*/buf, sizeof(buf), /*(unsigned short *)*/szFileName);
	if(strlen(buf)==0)
		return FALSE;
	m_iSwitchTime = atoi(buf);
	
	
	memset(buf,0,sizeof(buf));
	GetPrivateProfileString(_T("DISKCONFIG"), _T("NAME"), _T(""), /*(unsigned short *)*/buf, sizeof(buf), /*(unsigned short *)*/szFileName);
	if(strlen(buf)==0)
		return FALSE;
	
	int iNum = strlen(buf)/2;
	CString str;
	str.Format(_T("%s"),buf);
	for(int i=0;i<iNum;i++)
	{
		CString strTemp = str.Mid(i*2,2);
		strDrive[i] = strTemp;
	}
	m_iDiskNum = iNum;
	
	return TRUE;
}


void CTimeRecRuntime::RefreshState()
{
	m_bRefreshState = TRUE;
	//更新g_timerecInfoList链表DEVICE_NODE，bFind信息，通过与设备列表的guid对比以及状态
	USE_SYNCHRONIZE
	{
		CSingleLock sl(&g_GuInfoList);
		if (!sl.Lock(NTIMEOUT))
		{
			return;
		}
		DEVICENODE_OCX::iterator iter = g_DeviceNodeList.begin();
		DEVICENODE_OCX::iterator iterEnd = g_DeviceNodeList.end();
		while(iter != iterEnd)
		{
			CU_NET_LIB::DEVICE_NODE *pInfo = *iter;
			POSITION PosTemp = g_timerecInfoList.GetHeadPosition();
			while(PosTemp!=NULL)
			{
				_timerec_runtime_info_t * p = g_timerecInfoList.GetNext(PosTemp);
				if (strcmp(pInfo->guInfo.GUID,p->szGuid) == 0)
				{
					p->bFind = TRUE;
					p->guInfo = &pInfo->guInfo;
					break;
				}
			}
			iter++;
		}
	}
	m_bRefreshState =FALSE;
}
//初始化录像链表数据
int CTimeRecRuntime::IniRuntimeInfo()
{
	//加载磁盘配置等
	if (!LoadRuntimeInfo())
	{
		return -1;
	}
	
	char szFileName[MAX_PATH] = {0};
	CString strFileName;
	//strFileName.Format("%s%s_%s_Cfg.dat", theApp.m_szAppPath, theApp.m_szServerIP, theApp.m_szLoginUserName);
	strFileName.Format(_T(".\\%s_%s_Cfg.dat"),m_szServerIP, m_szLoginUserName);
// 	GetModuleFileName(NULL,szFileName,MAX_PATH);
// 	*strrchr(szFileName,'\\') = '\0';
// 	strcat(szFileName,strFileName);

	CFile file;
	//打开配置文件
	BOOL bret = file.Open(strFileName,CFile::modeReadWrite);
	if (!bret)
	{
		bret = file.Open(strFileName,CFile::modeCreate);
		if (!bret)
		{
			AfxMessageBox(_T("CFile::modeCreate Error!"));
			return -1;
		}
	}
	
	//查询文件信息
	cs.Lock();
	UINT Num = 0;
	do 
	{
		_timerec_runtime_info_t * pInfo = new _timerec_runtime_info_t;
		memset(pInfo,0,sizeof(_timerec_runtime_info_t));
		Num = file.Read((char *)pInfo,sizeof(_timerec_runtime_info_t));
		if (Num != sizeof(_timerec_runtime_info_t))//说明到文件尾部了
		{
			delete pInfo;
		}
		else
		{
			pInfo->bStart = FALSE;
			pInfo->bFind = FALSE;
			pInfo->pthis = this;
			POSITION pos = g_timerecInfoList.AddTail(pInfo);
		}
	} while (Num==sizeof(_timerec_runtime_info_t));
	cs.Unlock();
	file.Close();
	
	//更新g_timerecInfoList链表DEVICE_NODE，bFind信息，通过与设备列表的guid对比以及状态
	RefreshState();
	
	return 0;
}


//自动运行
void CTimeRecRuntime::AotuRunAllRec()
{
	if (!m_bAutoFlag)
		return;

	cs.Lock();
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		_timerec_runtime_info_t * pInfo = g_timerecInfoList.GetNext(pos);
		if (pInfo->bFind && pInfo->bAotuStart)
		{
			StartRec(pInfo);
		}
	}	
	cs.Unlock();
}

UINT CTimeRecRuntime::StopRunThread(LPVOID lPvoid)
{
	_timerec_runtime_info_t *pInfo = (_timerec_runtime_info_t *)lPvoid;
	CTimeRecRuntime *pRec = (CTimeRecRuntime *)pInfo->pthis;

	pRec->StopRec(pInfo);
	TRACE(_T("======================>>>>>> StopRec :%s\n"), pInfo->guInfo->GUName);
	return 0;
}

void CTimeRecRuntime::DelRuntimeInfo()
{
	//停止所有录像线程，释放空间
// 	cs.Lock();
// 	_timerec_runtime_info_t * pInfo = NULL;
// 	POSITION pos = g_timerecInfoList.GetHeadPosition();
// 	while(pos!=NULL)
// 	{
// 		POSITION posTemp = pos;
// 		pInfo = g_timerecInfoList.GetNext(pos);
// 		StopRec(pInfo);
// 		g_timerecInfoList.RemoveAt(posTemp);
// 		delete pInfo;
// 	}
// 	cs.Unlock();

	m_bExit = TRUE;
	if (m_hCheckThread)
	{
		if (WaitForSingleObject(m_hCheckEvent,2000) != WAIT_OBJECT_0)
		{
			TerminateThread(m_hCheckThread,0);
		}
		CloseHandle(m_hCheckEvent);
		CloseHandle(m_hCheckThread);
		m_hCheckEvent = NULL;
		m_hCheckThread =NULL;
	}
	
	CTypedPtrList<CPtrList, CWinThread*> pThreadList;
	_timerec_runtime_info_t * pInfo = NULL;
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		POSITION posTemp = pos;
		pInfo = g_timerecInfoList.GetNext(pos);
		if (pInfo->bStart)
		{
			CWinThread* pThread = AfxBeginThread((AFX_THREADPROC)StopRunThread, pInfo);
			ASSERT(pThread != NULL);
			pThread->m_bAutoDelete = FALSE;
			pThreadList.AddTail(pThread);
			Sleep(10);
		}
	}
	pos = pThreadList.GetHeadPosition();
	while(pos)
	{
		DWORD dwCode = STILL_ACTIVE;
		CWinThread* pThread = pThreadList.GetAt(pos);		
		while(STILL_ACTIVE == dwCode)
		{
			Sleep(10);  // 释放CPU
			::GetExitCodeThread(pThread->m_hThread, &dwCode);			
		}
		delete pThread;
		pThreadList.GetNext(pos);
	}
	pThreadList.RemoveAll();

	cs.Lock();
	if (!g_timerecInfoList.IsEmpty())
	{
		while(g_timerecInfoList.GetHeadPosition())
		{
			delete g_timerecInfoList.RemoveHead();
		}
	}
	cs.Unlock();
}


//保存录像列表配置信息
void CTimeRecRuntime::SaveRuntimeInfo()
{
	char szFileName[MAX_PATH] = {0};
	CString strFileName;
	strFileName.Format(_T(".\\%s_%s_Cfg.dat"),m_szServerIP,m_szLoginUserName);
// 	GetModuleFileName(NULL,szFileName,MAX_PATH);
// 	*strrchr(szFileName,'\\') = '\0';
// 	strcat(szFileName,strFileName);

	CFile file;
	//打开配置文件
	BOOL bret = file.Open(strFileName,CFile::modeReadWrite|CFile::modeCreate);
	
	//xie文件
	cs.Lock();
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		_timerec_runtime_info_t * pInfo = g_timerecInfoList.GetNext(pos);
		file.Write((char *)pInfo,sizeof(_timerec_runtime_info_t));
	}
	cs.Unlock();
	file.Close();	
}

//添加新项
void CTimeRecRuntime::AddRuntimeInfo(_timerec_runtime_info_t *Info)
{
	_timerec_runtime_info_t * pInfo = new _timerec_runtime_info_t;
	memset(pInfo,0,sizeof(_timerec_runtime_info_t));
	memset(pInfo,0,sizeof(_timerec_runtime_info_t));
	memcpy(pInfo,Info,sizeof(_timerec_runtime_info_t));
	cs.Lock();
	pInfo->pthis = this;
	g_timerecInfoList.AddTail(pInfo);
	cs.Unlock();
	
	//StartRec(pInfo);
	SaveRuntimeInfo();
}
//删除一项
void CTimeRecRuntime::DelRuntimeInfo(int nIndex)
{
	cs.Lock();
	int n=0;
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		POSITION posTemp = pos;
		_timerec_runtime_info_t * pInfo = g_timerecInfoList.GetNext(pos);
		if (n == nIndex)
		{
			StopRec(pInfo);
			g_timerecInfoList.RemoveAt(posTemp);
			delete pInfo;
			pos = NULL;
			break;
		}
		n++;
	}
	cs.Unlock();
	SaveRuntimeInfo();
	
}
//获取某项
_timerec_runtime_info_t *CTimeRecRuntime::GetOneRuntimeInfo(int nIndex)
{
	cs.Lock();
	int n=0;
	_timerec_runtime_info_t * pInfo = NULL;
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		POSITION posTemp = pos;
		pInfo = g_timerecInfoList.GetNext(pos);
		if (n == nIndex)
		{
			return pInfo;
		}
		n++;
	}
	cs.Unlock();
	//SaveRuntimeInfo();
	
	return NULL;
}


//录像回调线程
void CALLBACK timerec_ProcessRecvData(long lHandle,  void* lpBuf, long lSize, long lDecoderID );
void CALLBACK timerec_ProcessRecvData(long lHandle,  void* lpBuf, long lSize, long lDecoderID )
{
	if (lSize<=0)
	{
		return;
	}
	_timerec_runtime_info_t *  pInfo = (_timerec_runtime_info_t *)lHandle;
	if (pInfo->guInfo == NULL)
	{
		return;
	}
	if (pInfo->runState != 0)
	{
		return;
	}
	
	
	EnterCriticalSection(&pInfo->g_cs);
	if (pInfo->hRecFile != NULL)
	{
		AVI_fwrite(pInfo->hRecFile, lpBuf);
	}	
	LeaveCriticalSection(&pInfo->g_cs);

	// 录象还涉及到按日期或大小切分文件. 如果文件还未创建则需要等待文件创建完毕	
// 	if (pInfo->hRecFile != NULL)
// 	{
// 		SYSTEMTIME systime;
// 		::GetLocalTime(&systime);
// 		CTime   time1(systime);   
// 		CTime   time2(pInfo->sysCreateTime); 
// 		CMainFrame *prf = (CMainFrame *)pInfo->prf;
// 		CTimeSpan ts = time1 - time2;
// 		//TRACE("%d\n",ts.GetSeconds());
// 		
// 		if (ts > (prf->runtime.m_iSwitchTime*60))  //按时间分割
// 		{
// 			prf->runtime.CreateNewFile(pInfo);
// 		}
// 		else if (pInfo->runState == 2)//切盘
// 		{
// 			prf->runtime.CreateNewFile(pInfo);
// 			pInfo->runState = 0;
// 		}
// 		else if (pInfo->m_hFileRec == NULL)
// 		{
// 			prf->runtime.CreateNewFile(pInfo);
// 		}
// 		else if (pInfo->bReConn)
// 		{
// 			pInfo->bReConn = FALSE;
// 			prf->runtime.CreateNewFile(pInfo);
// 		}
// 		else
// 		{
// 			AVI_fwrite(pInfo->m_hFileRec, lpBuf);
// 		}
// 	}
	
}

//创建文件
void CTimeRecRuntime::CreateNewFile(_timerec_runtime_info_t *pInfo)
{
	pInfo->runState = 5;
	// 根据设定路径和其他要素创建录象文件
	CString  strPath = _T("");
	CString  strFile = _T("");
	char szContent[TEXT_MAXLEN] = {0};
	char szHint[TEXT_MAXLEN] = {0};
	
	//theApp.LoadPathConfig();
	
	//配置文件内的定时录像目录
	strPath = strDrive[m_nDriverIndex];//theApp.m_strPath_02;
	//TRACE(".............strPath=%s\n",strPath);
	
	if(strPath.GetLength() <= 0) 
		return;
	
	//创建文件路径
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	strFile.Format(_T("%s\\TIME_RECORD\\%04d%02d%02d\\%s\\%02d_%02d_%02d.AVI"), 
		strPath, systime.wYear, systime.wMonth,systime.wDay, pInfo->szGuname,
		systime.wHour,systime.wMinute,systime.wSecond);
	//TRACE(".............File:%s\n",strFile);
	
	//strFile.Format("%s%02d_%02d_%02d.AVI", strPath, systime.wHour,systime.wMinute,systime.wSecond);
	//TRACE(".............Drive=%s, File:%s\n",strDrive[m_nDriverIndex],strFile);
	
	//创建文件
	CString pathTemp;
	int nPos = -1;
	int nStart = 0;
	while(1)
	{
		nPos = strFile.Find('\\', nStart);
		if(nPos == -1)
			break;
		pathTemp = strFile.Left(nPos+1);
		BOOL bRet = ::CreateDirectory(strFile.Left(nPos+1), NULL);
		/*
		if(!bRet)
		{
		::LoadStringFromID(AfxGetInstanceHandle(), ID_FIXEDSTRING_106100, szContent, sizeof(szContent)-1);
		CString strMsg;
		strMsg.Format("%s:%s! ErrCode:%d\n", szContent, strPath, ::GetLastError());
		TRACE(strMsg);
		}
		*/
		nStart = nPos + 1;
	}
	
	//打开文件
	::GetLocalTime(&pInfo->sysCreateTime);
	
	
	EnterCriticalSection(&pInfo->g_cs);
	if (pInfo->hRecFile != NULL)
	{
		AVI_fclose((char*)pInfo->hRecFile);
		pInfo->hRecFile = NULL;
	}
	pInfo->hRecFile = (HANDLE)AVI_fopen((LPSTR)(LPCSTR)strFile.GetBuffer(strFile.GetLength()), AVI_WRITE);
	LeaveCriticalSection(&pInfo->g_cs);
	pInfo->runState = 0;
	TRACE(_T(".............CreateFile:%s\n"),strFile);
}

//录像线程
void timerecThread(void * param);
void timerecThread(void * param)
{
	_timerec_runtime_info_t *  pInfo = (_timerec_runtime_info_t *)param;
	//CMainFrame *prf = NULL;//(CMainFrame *)AfxGetMainWnd();
	//do 
	//{
	//	prf = (CMainFrame *)AfxGetMainWnd();
	//} while (prf == NULL);

	//pInfo->prf = prf;
	CVideoInstance* m_pVideoIns = NULL;
	int nWait = 0;

	while(pInfo->bStart)
	{
		SYSTEMTIME sTime;
		GetLocalTime(&sTime);
		if (!pInfo->time_seg[sTime.wDayOfWeek].bFlag)
		{
			Sleep(100);
			continue;
		}

		//判断时间
		long timeNow,timeStart,timeEnd;
		timeNow = sTime.wHour*3600 + sTime.wMinute*60 + sTime.wSecond;
		timeStart = pInfo->time_seg[sTime.wDayOfWeek].start_hour*3600 +pInfo->time_seg[sTime.wDayOfWeek].start_minute*60+pInfo->time_seg[sTime.wDayOfWeek].start_second;
		timeEnd = pInfo->time_seg[sTime.wDayOfWeek].end_hour*3600 +pInfo->time_seg[sTime.wDayOfWeek].end_minute*60+pInfo->time_seg[sTime.wDayOfWeek].end_second;
		if ((timeNow < timeStart) || (timeNow > timeEnd))
		{
			pInfo->runState = 3;
			if (m_pVideoIns != NULL)
			{
				m_pVideoIns->Stop((LONG)pInfo);
				m_pVideoIns = NULL;
				pInfo->pVideoIns = NULL;
			}	
			EnterCriticalSection(&pInfo->g_cs);
			if (pInfo->hRecFile != NULL)
			{
				AVI_fclose((char*)pInfo->hRecFile);
				pInfo->hRecFile = NULL;
			}
			LeaveCriticalSection(&pInfo->g_cs);
			Sleep(100);
			continue;
		}


		//状态判断
		switch (pInfo->runState)
		{
		case 0://正常
			{
				SYSTEMTIME systime;
				::GetLocalTime(&systime);
				CTime   time1(systime);   
				CTime   time2(pInfo->sysCreateTime); 
				CTimeSpan ts = time1 - time2;
				//if (ts > (prf->m_pTimeRec->m_iSwitchTime*60))  //按时间分割
				//{
				//	prf->m_pTimeRec->CreateNewFile(pInfo);
				//}
				//if (pInfo->hRecFile == NULL)
				//	prf->m_pTimeRec->CreateNewFile(pInfo);
			}
			break;
		case 1://挂起
			{
				//if ((m_pVideoIns != NULL)&& (!prf->m_pTimeRec->m_bCoverFlag))
				if ((m_pVideoIns != NULL))
				{
					m_pVideoIns->Stop((LONG)pInfo);
					m_pVideoIns = NULL;
					pInfo->pVideoIns = NULL;

				}
				EnterCriticalSection(&pInfo->g_cs);
				if (pInfo->hRecFile != NULL)
				{
					AVI_fclose((char*)pInfo->hRecFile);
					pInfo->hRecFile = NULL;
				}
				LeaveCriticalSection(&pInfo->g_cs);
				Sleep(30);

				continue;
			}
			break;
		case 2://切盘
			{
				//prf->m_pTimeRec->CreateNewFile(pInfo);
				pInfo->runState = 0;
			}
			break;
		case 3://录像时间到
			{
				pInfo->runState = 0;
			}
			break;
		case 4://重连成功
			{
				//prf->runtime.CreateNewFile(pInfo);
				//pInfo->runState = 0;	
			}
			break;
		case 5:
			{
				Sleep(100);
				continue;
			}
			break;
		}


		//重连
		if ((m_pVideoIns != NULL) && (++nWait >= 100))
		{
			BOOL bState = CU_NET_LIB::GetMediaState(g_dwServerId, m_pVideoIns->m_hVideo);
			if (!bState)
			{
				TRACE(_T("................Reconnect\n"));
				pInfo->runState = 4;
				m_pVideoIns->Reconnect();
//				CU_NET_LIB::Reconnect(g_dwServerId, m_pVideoIns->m_hVideo);
				Sleep(1000);
// 				int i = 100;
// 				while (i--)
// 				{
// 					if (pInfo->bStart)
// 					{
// 						Sleep(10);
// 					}
// 					else
// 						break;
// 				}
			}
			else
			{
				if (pInfo->runState == 4)
				{
					pInfo->runState = 0;
				}
			}
			nWait = 0;
			continue;
		}


		if (m_pVideoIns == NULL)
		{
			TRACE(_T(".......CreateVideoInstance\n"));
			m_pVideoIns = g_VideoMng.CreateVideoInstance(/*(unsigned short *)*/pInfo->guInfo->GUID);
			if(m_pVideoIns)
			{
				if (pInfo->hRecFile == NULL)
				{
				    //prf->m_pTimeRec->CreateNewFile(pInfo);
				}

				pInfo->pVideoIns = (void *)m_pVideoIns;
				if(!m_pVideoIns->Start(*(pInfo->guInfo), (LONG)pInfo, pInfo->hNotify, timerec_ProcessRecvData))
				{
					m_pVideoIns->Stop((LONG)pInfo);
					m_pVideoIns = NULL;
					pInfo->pVideoIns = NULL;
				}
			}
		}
		
		Sleep(30);
	}

	SetEvent(pInfo->hExitEvent);
}

//开始录像
void CTimeRecRuntime::StartRec(_timerec_runtime_info_t *  pInfo)
{
	if (pInfo->bStart)
		return;
	
	
	
	pInfo->bStart = TRUE;
	pInfo->runState = 0;
	pInfo->hRecFile = NULL;
	InitializeCriticalSection(&pInfo->g_cs);
	pInfo->hNotify = CreateEvent(NULL,TRUE,FALSE,NULL);
	pInfo->hExitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	pInfo->hExitThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)timerecThread,(void *)pInfo,NULL,NULL);
	pInfo->pthis = this;
	
	TRACE(_T("......CTimeRecRuntime::StartRec\n"));
	
	if (m_hCheckThread == NULL)
	{
		//开启磁盘检测线程
		m_bExit = FALSE;
		m_hCheckEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
		m_hCheckThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)CheckDiskThread,this,NULL,NULL);
	}
	//return;
}
//停止录像
void CTimeRecRuntime::StopRec(_timerec_runtime_info_t *  pInfo)
{
	if (!pInfo->bStart)
		return;
	pInfo->bStart = FALSE;
	
	//////////////////////////////////////////////////////////////////////////
	if (m_bExit)
	{
		BOOL bStopCheckThread = TRUE;
		cs.Lock();
		_timerec_runtime_info_t * p = NULL;
		POSITION pos = g_timerecInfoList.GetHeadPosition();
		while(pos!=NULL)
		{
			p = g_timerecInfoList.GetNext(pos);
			if (p->bStart)
			{
				bStopCheckThread = FALSE;
				break;
			}
		}
		cs.Unlock();
		if (bStopCheckThread)
		{
			//停止磁盘检测线程
			m_bExit = TRUE;
			if (m_hCheckThread)
			{
				if (WaitForSingleObject(m_hCheckEvent,2000) != WAIT_OBJECT_0)
				{
					TerminateThread(m_hCheckThread,0);
				}
				CloseHandle(m_hCheckEvent);
				CloseHandle(m_hCheckThread);
				m_hCheckEvent = NULL;
				m_hCheckThread =NULL;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	
	TRACE(_T("......CTimeRecRuntime::StopRec\n"));
	//return;
	
	if (pInfo->hExitThread)
	{
		DWORD dwStart = GetTickCount();
		if (WaitForSingleObject(pInfo->hExitEvent,INFINITE) != WAIT_OBJECT_0)
		{
			TerminateThread(pInfo->hExitThread,0);
		}
		TRACE(_T("=============================================== wait time =%d\n"),GetTickCount()-dwStart);
		CloseHandle(pInfo->hExitEvent);
		CloseHandle(pInfo->hExitThread);
		pInfo->hExitEvent = NULL;
		pInfo->hExitThread = NULL;
	}
		
	CVideoInstance* m_pVideoIns = NULL;
	m_pVideoIns = (CVideoInstance*)pInfo->pVideoIns;
	if (m_pVideoIns != NULL)
	{
		m_pVideoIns->Stop((LONG)pInfo);
		m_pVideoIns = NULL;
		pInfo->pVideoIns = NULL;
		CloseHandle(pInfo->hNotify);
		pInfo->hNotify = NULL;
	}
	
	EnterCriticalSection(&pInfo->g_cs);
	if (pInfo->hRecFile != NULL)
	{
		if (AVI_fclose((char*)pInfo->hRecFile) !=0)
		{
			AfxMessageBox(_T("AVI_fclose error"));
		}
		//AVI_fclose((char*)pInfo->m_hFileRec);
		pInfo->hRecFile = NULL;
	}
	LeaveCriticalSection(&pInfo->g_cs);
	
	DeleteCriticalSection(&pInfo->g_cs);
}

void CTimeRecRuntime::StartRecByIndex(int nIndex)
{
	int n=0;
	_timerec_runtime_info_t * pInfo = NULL;
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		POSITION posTemp = pos;
		pInfo = g_timerecInfoList.GetNext(pos);
		if (n == nIndex)
		{
			pInfo->bAotuStart = TRUE;
			StartRec(pInfo);
			break;
		}
		n++;
	}
	
	SaveRuntimeInfo();
	
}
void CTimeRecRuntime::StopRecByIndex(int nIndex)
{
	int n=0;
	_timerec_runtime_info_t * pInfo = NULL;
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		POSITION posTemp = pos;
		pInfo = g_timerecInfoList.GetNext(pos);
		if (n == nIndex)
		{
			pInfo->bAotuStart = FALSE;
			StopRec(pInfo);
			break;
		}
		n++;
	}
	
	SaveRuntimeInfo();
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
BOOL CTimeRecRuntime::CheckCurDisk(int n)
{
	//检测当前磁盘空间p->m_nDriverIndex
	ULARGE_INTEGER bytesUsed, bytesTotal, bytesFree;
	BOOL bRet = GetDiskFreeSpaceEx (strDrive[n],
		(PULARGE_INTEGER)&bytesUsed,
		(PULARGE_INTEGER)&bytesTotal,	
		(PULARGE_INTEGER)&bytesFree);
	
	//得到以MB计算的磁盘剩余空间
	DWORD dwSpace = bytesFree.QuadPart >> 20;
	
	//当前磁盘空间不足,删除相关文件
	if((int)dwSpace < m_iResSize)
		return FALSE;
	
	return TRUE;
	
}

void CTimeRecRuntime::ModifyThreadState(int nState)
{
	cs.Lock();
	_timerec_runtime_info_t * pInfo = NULL;
	POSITION pos = g_timerecInfoList.GetHeadPosition();
	while(pos!=NULL)
	{
		pInfo = g_timerecInfoList.GetNext(pos);
		pInfo->runState = nState;//线程运行状态0正常，1挂起，2切盘
		// 		if (nState == 1)
		// 		{
		// 			if (pInfo->hRecFile != NULL)
		// 			{
		// 				if (AVI_fclose((char*)pInfo->hRecFile) !=0)
		// 				{
		// 					AfxMessageBox("AVI_fclose error");
		// 				}
		// 				//AVI_fclose((char*)pInfo->m_hFileRec);
		// 				pInfo->hRecFile = NULL;
		// 			}
		// 		}
	}
	cs.Unlock();
}

void CheckDiskThread(void * param)
{
	///CMainFrame *prf = NULL;
	//do 
	//{
	//	prf = (CMainFrame *)AfxGetMainWnd();
//	} while (prf == NULL);
	CTimeRecRuntime *p = (CTimeRecRuntime *)param;
	while(!p->m_bExit)
	{
		if (!p->CheckCurDisk(p->m_nDriverIndex))//当前磁盘空间不足
		{
			BOOL bNoSpace = TRUE;
			//查找下一个可用磁盘
			for (int n = 0;n<p->m_iDiskNum;n++)
			{
				if (p->CheckCurDisk(n))
				{
					//找到可用磁盘
					p->m_nDriverIndex = n;
					//通知录像线程切换磁盘
					p->ModifyThreadState(2);
					
					
					bNoSpace = FALSE;
					break;
				}
			}
			
			//所有磁盘空间不足
			if (bNoSpace && p->m_bCoverFlag)
			{
				//删除旧的备份文件,
				p->ModifyThreadState(1);//通知录像线程挂起
				
				//循环等所有的文件句柄关闭
				BOOL bDel = TRUE;
				do 
				{
					bDel = TRUE;
					_timerec_runtime_info_t * pInfo = NULL;
				//	POSITION pos = prf->m_pTimeRec->g_timerecInfoList.GetHeadPosition();
// 					while(pos!=NULL)
// 					{
// 						pInfo = prf->m_pTimeRec->g_timerecInfoList.GetNext(pos);
// 						if (pInfo->hRecFile != NULL)
// 						{
// 							pInfo->runState = 1;
// 							bDel = FALSE;
// 							break;
// 						}
// 					}
					//Sleep(500);
					int i = 50;
					while(i--)
					{
						if (p->m_bExit)
						{
							break;
						}
						else
						{
							Sleep(10);
						}
					}
				} while (!bDel);
				
				p->FindDelDir();
				p->ModifyThreadState(0);
			}
			else if (bNoSpace && (!p->m_bCoverFlag))
			{
				//通知线程磁盘满,通知录像线程挂起
				p->ModifyThreadState(1);
			}
		}
		
		
		int i = 50;
		while(i--)
		{
			if (p->m_bExit)
			{
				break;
			}
			else
			{
				Sleep(10);
			}
		}
	}
	SetEvent(p->m_hCheckEvent);
}


BOOL  CTimeRecRuntime::FindDelDir()   
{   
	
	int i = 0;
	FILETIME DelFilesTemp[1024];
	int count = m_iDiskNum;
	for(int k = 0; k< count; k++)//所有的磁盘查找
	{  
		CString strPath;
		strPath.Format(_T("%s\\TIME_RECORD"),strDrive[k]);
		
		char   tempFileFind[MAX_PATH];
		sprintf(tempFileFind,"%s\\*.*",strPath);
		
		CFileFind   tempFind;   
		BOOL   IsFinded=(BOOL)tempFind.FindFile(/*(unsigned short *)*/tempFileFind);
		
		while(IsFinded) //查找所有文件，不查找该文件夹下的其他文件夹内的文件  
		{   
			IsFinded=(BOOL)tempFind.FindNextFile();   
			if(!tempFind.IsDots())//过滤掉 '.'和'..' 目录   
			{   
				char   foundFileName[MAX_PATH];   
				strcpy(foundFileName, (const char *)tempFind.GetFileName().GetBuffer(MAX_PATH));   
				if(tempFind.IsDirectory())   
				{   
					sprintf(DelFiles[i].FileName,"%s\\%s",strPath,foundFileName);
					
					HANDLE hDir = CreateFile (/*(unsigned short *)*/DelFiles[i].FileName, GENERIC_READ,
						FILE_SHARE_READ|FILE_SHARE_DELETE,
						NULL, OPEN_EXISTING,
						FILE_FLAG_BACKUP_SEMANTICS, NULL);
					FILETIME lpCreationTime; // 文件夹的创建时间
					FILETIME lpLastAccessTime; // 对文件夹的最近访问时间
					FILETIME lpLastWriteTime; // 文件夹的最近修改时间
					// 获取文件夹时间属性信息
					if (GetFileTime(hDir, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime))
					{
						DelFiles[i].CreateFileTime =  lpCreationTime;
						DelFilesTemp[i] = lpCreationTime;
						i++;
					}
					CloseHandle(hDir); // 关闭打开过的文件夹
				}   
			}   
		}	   
	}
	
	//排序
	FILETIME iTemp;
	for(int t=0;t<i-1;t++)
	{
		for(int j=t+1;j<i;j++)
		{
			if(CompareFileTime(&DelFilesTemp[j],&DelFilesTemp[t]) == -1)//返回值为0日期相等，-1前者较早，1后者较早。
			{
				iTemp = DelFilesTemp[t];
				DelFilesTemp[t] = DelFilesTemp[j];
				DelFilesTemp[j] = iTemp;
			}
		}
	}
	
	//删除最早的目录
	for (t = 0 ; t < i ; t ++)
	{
		if (CompareFileTime(&DelFiles[t].CreateFileTime,&DelFilesTemp[0])==0)
		{
			DeleteDirectory(DelFiles[t].FileName);
			TRACE(_T(" ######################----------------------->  DeleteDirectory:%s\n"),DelFiles[t].FileName);
		}
	}
	
	return   TRUE;   
}   


//************************************
// Method:    DeleteDirectory
// FullName:  CRecordServerDlg::DeleteDirectory
// Access:    public 
// Returns:   bool
// Qualifier: 递归删除文件夹以及其下所有的文件以及文件夹
// Parameter: char * sDirName
//************************************
bool CTimeRecRuntime::DeleteDirectory(char* sDirName)  
{  
	char buf[512] = {'\0'};
	
	CFileFind tempFind;  
	char sTempFileFind[512] ; 
	
	sprintf(sTempFileFind,"%s\\*.*",sDirName);  
	BOOL IsFinded = tempFind.FindFile(/*(const unsigned short *)*/sTempFileFind);  
	while (IsFinded)  
	{  
		IsFinded = tempFind.FindNextFile();  
		
		if (!tempFind.IsDots())  
		{  
			char sFoundFileName[512];  
			strcpy(sFoundFileName, (const char *)tempFind.GetFileName().GetBuffer(200));  
			
			if (tempFind.IsDirectory())  
			{  
				char sTempDir[512];  
				sprintf(sTempDir,"%s\\%s",sDirName,sFoundFileName);  
				DeleteDirectory(sTempDir);  
			}  
			else  
			{  
				char sTempFileName[512];  
				sprintf((char *)sTempFileName, (const char *)_T("%s\\%s"),sDirName,sFoundFileName);  
				if (!DeleteFile(/*(const unsigned short *)*/sTempFileName))//打印错误信息
				{
					memset(buf,0,sizeof(buf));
					sprintf(buf, (const char *)_T("DeleteFile\t%s************ERROR\n"), sTempFileName);
					TRACE(/*(const unsigned short *)*/buf);
					//WriteLogFile(buf,strlen(buf));
				}
			}  
		}  
	}  
	tempFind.Close();  
	if(!RemoveDirectory(/*(const unsigned short *)*/sDirName))//打印错误信息
	{  
		memset(buf,0,sizeof(buf));
		sprintf(buf,(const char *)_T("RemoveDirectory\t%s##############ERROR\n"),sDirName);
		TRACE(/*(const unsigned short *)*/buf);
		//WriteLogFile(buf,strlen(buf));
		return FALSE;  
	}
   return TRUE;  
} 

void CTimeRecRuntime::FindFile(char *guName,
							   TimeRec_Day_t yymmdd,
							   TimeRec_Time_t startTime,TimeRec_Time_t endTime,
							   TimeRec_FileInfo_t *pfile,int *fileNum)
{
#if 1
	int i = 0;
	//FILETIME FilesTemp[1024];
	Find_file_t findFile[1024];
	DWORD LogicalDrive = GetLogicalDrives();
	//  	int count = LogicalDrive;
	*fileNum = 0;
	
	for(int k = 0; k < 32; k++)//所有的磁盘查找
	{  
		char driveName[256];
		sprintf(driveName, "%c:", 'A' + k);
		if ((LogicalDrive&(1<<k)) != 0 && (GetDriveType(/*(const unsigned short *)*/driveName) == DRIVE_FIXED))
		{
			CString strPath;
			strPath.Format(_T("%s\\TIME_RECORD\\%04d%02d%02d\\%s\\"),
				driveName,
				yymmdd.year,yymmdd.month,yymmdd.day,
				guName);
			char   tempFileFind[MAX_PATH];
			sprintf(tempFileFind,"%s\\*.*",strPath);
			
			CFileFind   tempFind;   
			BOOL   IsFinded=(BOOL)tempFind.FindFile(/*(const unsigned short *)*/tempFileFind);
			
			while(IsFinded) //查找所有文件，不查找该文件夹下的其他文件夹内的文件  
			{   
				IsFinded=(BOOL)tempFind.FindNextFile();   
				if(!tempFind.IsDots())//过滤掉 '.'和'..' 目录   
				{   
					char   foundFileName[MAX_PATH];   
					strcpy(foundFileName, (const char *)tempFind.GetFileName().GetBuffer(MAX_PATH));   
					if(!tempFind.IsDirectory())   
					{   
						sprintf(findFile[i].FileName,"%s\\%s",strPath,foundFileName);
						
						HANDLE hDir = CreateFile(/*(const unsigned short *)*/findFile[i].FileName, GENERIC_READ,
							FILE_SHARE_READ,
							NULL, OPEN_EXISTING,
							FILE_FLAG_BACKUP_SEMANTICS, NULL);
						FILETIME lpCreationTime; // 创建时间
						FILETIME lpLastAccessTime; // 最近访问时间
						FILETIME lpLastWriteTime; // 最近修改时间
						ZeroMemory(&lpCreationTime, sizeof(FILETIME));
						ZeroMemory(&lpLastAccessTime, sizeof(FILETIME));
						ZeroMemory(&lpLastWriteTime, sizeof(FILETIME));
						// 获取文件夹时间属性信息
						BOOL bRet = GetFileTime(hDir, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
						//if (bRet)
						{
							findFile[i].CreateFileTime =  lpCreationTime;
							findFile[i].LastWriteTime =  lpLastWriteTime;
							DWORD dwSize = GetFileSize(hDir, NULL);
							if (dwSize == 0xFFFFFFFF)
								findFile[i].dwFileSize = 0;
							else
								findFile[i].dwFileSize = dwSize;
							i++;
						}
						
						CloseHandle(hDir); // 关闭打开过的文件
					}   
				}   
			}
		}
	}

	//排序
	Find_file_t iTemp;
	for(int t=0;t<i-1;t++)
	{
		for(int j=t+1;j<i;j++)
		{
			if(CompareFileTime(&findFile[j].CreateFileTime,&findFile[t].CreateFileTime) == -1)//返回值为0日期相等，-1前者较早，1后者较早。
			{
				iTemp = findFile[t];
				findFile[t] = findFile[j];
				findFile[j] = iTemp;
			}
		}
	}
	
	
	int nstart = startTime.hour*3600+startTime.minute*60+startTime.second;
	int nend = endTime.hour*3600+endTime.minute*60+endTime.second;
	int j=0;
	CString str;
	//时间段查找
	for (t=0;t<i;t++)
	{
		CTime  time(findFile[t].CreateFileTime);
		int nTime = time.GetHour()*3600 + time.GetMinute()*60 +time.GetSecond();
		
		if ((nstart <= nTime) && ( nTime <= nend ))
		{
			TimeRec_FileInfo_t *p = pfile+j;
			
			CTime st1(findFile[t].CreateFileTime);
			str = st1.Format("%Y-%m-%d %H:%M:%S"); 
			strcpy(p->szCreateTime, (const char *)str.GetBuffer(str.GetLength()));
			
			CTime st2(findFile[t].LastWriteTime);
			str = st2.Format("%Y-%m-%d %H:%M:%S"); 
			strcpy(p->szLastWriteTime, (const char *)str.GetBuffer(str.GetLength()));
			
			p->dwFileSize = findFile[t].dwFileSize;
			memcpy(p->filepath,findFile[t].FileName,MAX_PATH);
			
			j++;
		}
	}
	
	*fileNum = j;
#endif
	
}