// VideoInstance.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoInstance.h"
//#include "VideoManage.h"

//extern CVideoManage   g_VideoMng;
void CallBack_NetData( long lHandle, void* lpBuf, long lSize, long lDecoderID);
// CVideoInstance
CVideoInstance::CVideoInstance()
:m_EventReconnect(0, TRUE, 0, 0)
{
	m_hVideo = NULL;
//	m_dwFlag =  (DWORD)-1;
	m_dwFlag =  (DWORD)0;
	m_pThread = NULL;
	m_bReconnectOk = FALSE;
	m_bReconnectStatus = FALSE;
	m_bStraightConn = FALSE;
	m_bLinkState = FALSE;
}

CVideoInstance::~CVideoInstance()
{
	m_hVideo = NULL;
}
void  CVideoInstance::WaitForThread()
{
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
				CU_NET_LIB::CancelWaitting(g_dwServerId);
				if(m_hVideo)
					CU_NET_LIB::CancelVideoInstance(g_dwServerId, m_hVideo);
				Sleep(1);
			}
			else
			{
				break;
			}
		}
		SAFE_DELETE(m_pThread);
	}
	TRACE(_T("WaitForThread lost time: %d\n"), GetTickCount()-dwStart);
}

// CVideoInstance ��Ա����
// �ú����Ƿ���������, �贮��
BOOL  CVideoInstance::Start(const CU_NET_LIB::GUINFO& guInfo, LONG lHandle, HANDLE hNotify, RecvDataFunc lpFunc)
{
	CLIENT_STRUCT* pClient = new CLIENT_STRUCT;
	if(!pClient)
		return FALSE;
	pClient->lHandle = lHandle;
	pClient->lpFunc  = lpFunc;
	pClient->hNotify = hNotify;
	
	m_csList.Lock();
	if(m_List.GetCount()>0)
	{
		m_List.AddTail(pClient);
		if(m_dwFlag == ST_OK) //֮ǰ���Ѿ����ӳɹ�
		{
			::SetEvent(hNotify);
		}
		
		m_csList.Unlock();
		return TRUE;
	}
	else
	{
		m_guInfo = guInfo;
		CU_NET_LIB::CLIENTINFO client;
		::ZeroMemory(&client, sizeof(CU_NET_LIB::CLIENTINFO));
		client.guInfo = m_guInfo;
		client.lpFunc = CallBack_NetData;        
		client.lHandle = (long)this;    
		client.nProtocolType = guInfo.EnTcpPView;
		m_hVideo = CU_NET_LIB::CreateVideoInstance(g_dwServerId, client);
		if(!m_hVideo)
		{
			SAFE_DELETE(pClient);
			m_csList.Unlock();
			return FALSE;
		}
		else
		{
			m_pThread = AfxBeginThread(Thread_Start, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
			if(m_pThread != NULL)
			{
				m_pThread->m_bAutoDelete = FALSE;
				m_pThread->ResumeThread();
				m_List.AddTail(pClient);  // ��ӵ��б���
				m_csList.Unlock();
				return TRUE;
			}
			else
			{
				SAFE_DELETE(pClient);
				m_csList.Unlock();
				return FALSE;
			}
		}	
	}
	m_csList.Unlock();
}

// �������Ϊ������
BOOL  CVideoInstance::Stop(LONG lHandle)
{
	int nCount;
	m_csList.Lock();  
	POSITION pos = m_List.GetHeadPosition();
	while(pos)
	{
		CLIENT_STRUCT* pClient = m_List.GetAt(pos);
		if(lHandle == pClient->lHandle)
		{
			m_List.RemoveAt(pos);
			SAFE_DELETE(pClient);
			break;
		}
		else
			m_List.GetNext(pos);
	}
	nCount = m_List.GetCount();
	m_csList.Unlock();
	if(!pos)
		return FALSE;
    	
	// �����û���κ�����, ���������ʵ��
	if(0 == nCount)
	{
		if(m_hVideo)
		{
			WaitForThread(); // �ȴ�������Ƶ���߳��˳�, �����̷���
			// �ж��Ƿ��������߳�����, �����, ����Ҫ�ȴ�
			while(1)
			{
				DWORD dwResult = :: WaitForSingleObject(m_EventReconnect.m_hObject, 0);
				if(dwResult != WAIT_OBJECT_0 )
					break;
				else
					Sleep(1);
			}
			CU_NET_LIB::RealVideoPreviewStop(g_dwServerId, m_hVideo);	//ֻ��������
			// ������
//			g_VideoMng.ReleaseInstance(this);
			m_hVideo = NULL; 
	//		delete this;
		}
	}
    return TRUE;
}

// ������Ƶ�����߳�
UINT  CVideoInstance::Thread_Start(LPVOID lParam)
{
	CString strMsg;
	CVideoInstance*  pIns = (CVideoInstance*)lParam;
	CU_NET_LIB::GUINFO guInfo = pIns->m_guInfo;
	// ��ѯ·��
	TCHAR    szMduIp[128] = {0};
	CString  strMduIp = _T("");
	UINT     uPort= 0;	
	
	HRESULT hr;
 	CU_NET_LIB::MDU_ROUTE_INFO mduInfo;	
	memset(&mduInfo, 0, sizeof(CU_NET_LIB::MDU_ROUTE_INFO));
	
	hr = CU_NET_LIB::QueryPuRealRoute(g_dwServerId, guInfo, mduInfo);
	
	if(hr != 0)
	{
		if(strcmp(mduInfo.szLocalMduIp, "") == 0 && strcmp(mduInfo.szRemoteMduIp, "") == 0)
		{
			hr = 0x80008033;
			goto THREAD_EXIT;
		}
		if(strcmp(mduInfo.szLocalMduIp, "NULL") == 0 && strcmp(mduInfo.szRemoteMduIp, "NULL") == 0 )
		{
			hr = 0x80008033;
			goto THREAD_EXIT;
		}
	}
	//--------------------------------------------------------------------------//
	hr = CU_NET_LIB::RealVideoPreviewStart(g_dwServerId, pIns->m_hVideo, mduInfo);

THREAD_EXIT:
	pIns->m_dwFlag = hr;
	pIns->m_csList.Lock();
	POSITION pos = pIns->m_List.GetHeadPosition();
	while(pos)
	{
		CLIENT_STRUCT* pClient = pIns->m_List.GetAt(pos);
		::SetEvent(pClient->hNotify);
		pIns->m_List.GetNext(pos);
	}
	pIns->m_csList.Unlock();

	return 0;
}
BOOL CVideoInstance::Reconnect()
{
// 	m_csReConnect.Lock();
	if (m_bReconnectStatus)
	{
		return FALSE;
	}

	m_bReconnectStatus = TRUE;
	if(GetTickCount()-m_LastReconnect > 5000 || GetTickCount() < m_LastReconnect)
	{
		DWORD dwResult = :: WaitForSingleObject(m_EventReconnect.m_hObject, 0);
		if(dwResult == WAIT_OBJECT_0 || dwResult == WAIT_FAILED)
			return FALSE;

		m_bReconnectOk = FALSE;
		this->m_EventReconnect.SetEvent();
		m_bReconnectOk = CU_NET_LIB::Reconnect(g_dwServerId, m_hVideo);
		m_EventReconnect.ResetEvent();
		m_LastReconnect = GetTickCount();
	}
	m_bReconnectStatus = FALSE;
//   	m_csReConnect.Unlock();

	TRACE(_T("++++++++++++++++++++++++++++++++++++++++++%d\n"), m_bReconnectOk);
	return m_bReconnectOk;
// 	m_bReconnectOk = FALSE;
// 	if(GetTickCount()-m_LastReconnect > 5000 || GetTickCount() < m_LastReconnect)
// 	{
// 		m_csReConnect.Lock();
// 		if (m_bReconnectStatus == TRUE)
// 		{
// 			m_csReConnect.Unlock();
// 			return FALSE;
// 		}
// 		m_bReconnectStatus = TRUE;
// 		m_csReConnect.Unlock();
// 
// 		DWORD dwResult = :: WaitForSingleObject(m_EventReconnect.m_hObject, 0);
// 		if(dwResult == WAIT_OBJECT_0 || dwResult == WAIT_FAILED)
// 			return FALSE;
// 		m_pThreadReconnect = AfxBeginThread(Thread_Reconnect, this, 
// 			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
// 		if(m_pThreadReconnect != NULL)
// 		{
// 			this->m_EventReconnect.SetEvent();
// 			m_pThreadReconnect->ResumeThread();
// 			m_LastReconnect = GetTickCount();
// 			return TRUE;   
// 		}
// 		return FALSE;
// 	}
// 	else
// 		return FALSE;
}
UINT CVideoInstance::Thread_Reconnect(LPVOID lParam)
{
	DWORD dwStart = GetTickCount();
	CVideoInstance* pIns = (CVideoInstance*)lParam;
	if(!pIns)
		return 0;
	TRACE(_T("Prepare to Reconnect to mdu\n"));
	pIns->m_bReconnectOk = CU_NET_LIB::Reconnect(g_dwServerId, pIns->m_hVideo);
//	TRACE("(((((((((((((((((((((((((((((((((((((((((((((((((((((( %d\n", pIns->m_bReconnectOk);
	pIns->m_EventReconnect.ResetEvent();
	
	pIns->m_csReConnect.Lock();
	pIns->m_bReconnectStatus = FALSE;
	pIns->m_csReConnect.Unlock();
//	TRACE("Thread_Reconnect lost time=%d\n", GetTickCount()-dwStart);
	return 0;
}
void CVideoInstance::SetReconnectStatus(BOOL bFlag)
{
	m_bReconnectOk = FALSE;
	return;
}

// �ص�����, ���ﲶ��(��)��Ƶ���ݲ����зַ�
void CallBack_NetData( long lHandle, void* lpBuf, long lSize, long lDecoderID)
{
	CVideoInstance *pIns = (CVideoInstance*)lHandle;
	if(pIns == NULL)
		return;

	pIns->m_csList.Lock();
	POSITION pos = pIns->m_List.GetHeadPosition();
//	TRACE("-------------------VideoInstance handle=%0xd; window count=%d\n", lHandle, pIns->m_List.GetCount());
    while(pos)
	{
		CLIENT_STRUCT* pClient = pIns->m_List.GetAt(pos);
		pClient->lpFunc( pClient->lHandle, lpBuf, lSize, lDecoderID);
		pIns->m_List.GetNext(pos);
	}
	pIns->m_csList.Unlock();
}

