// CameraControlThread.cpp: implementation of the CCameraControlThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CuOcx.h"
#include "CameraControlThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraControlThread::CCameraControlThread()
{
	m_pptzThread = NULL;
	m_eventExit.ResetEvent();
	m_bClosing = FALSE;
	Init();
}

CCameraControlThread::~CCameraControlThread()
{
	DeInit();
}

void CCameraControlThread::Init()
{
	m_pptzThread = AfxBeginThread(ptzControlThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	if (m_pptzThread != NULL)
	{
		m_bClosing = FALSE;
		m_pptzThread->m_bAutoDelete = FALSE;
		m_pptzThread->ResumeThread();
	}
	else
	{
		AfxMessageBox(_T("创建摄像头操作线程失败，摄像头无法操作！"));
	}
}

void CCameraControlThread::DeInit()
{
	ExitThread();
}

void CCameraControlThread::ExitThread()
{
	m_eventExit.SetEvent();
	if(m_pptzThread)
	{
		HANDLE  hThread = m_pptzThread->m_hThread;
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
		SAFE_DELETE(m_pptzThread);
	}

	USE_SYNCHRONIZE
	{
		CSingleLock sl(&m_ptzQueue);
		if (sl.Lock(INFINITE))
		{
			m_bClosing = TRUE;//队列不再接收数据
			while(m_ptzQueue.size() > 0)
			{
				ptz_control_t *pCtrlT = PopFront();
				if (pCtrlT != NULL)
				{
					delete pCtrlT;
				}
			}
		}
	}
}

UINT AFX_CDECL CCameraControlThread::ptzControlThread(LPVOID lParam)
{
	CCameraControlThread *pCtlThread = static_cast<CCameraControlThread *>(lParam);
	if (pCtlThread == NULL)
	{
		ASSERT(FALSE);
		return 0;
	}
	
	ptz_control_t *pCtrlT = NULL;
	while(1)
	{
		pCtrlT = pCtlThread->PopFront();
		if (pCtrlT != NULL)
		{
			ptz_control_t ptz_control =  *((ptz_control_t*)pCtrlT);
			delete  (ptz_control_t*)pCtrlT;
			
			CU_NET_LIB::DomeControl(g_dwServerId, ptz_control.guInfo, /*(const unsigned short *)*/ptz_control.csgIp,  ptz_control.csgport,
				ptz_control.msgtype, ptz_control.speed, ptz_control.cmd, ptz_control.param);
			
			TRACE(_T("PTZ=============== msgtype: %s, cmd: %s, param: %s, speed: %d\n"), ptz_control.msgtype, ptz_control.cmd, ptz_control.param, ptz_control.speed);
		}

		if (pCtlThread->WaitToExit(NTIMEOUT))
		{
			break;
		}
	}
	return 0;
}

BOOL CCameraControlThread::WaitToExit(DWORD dwTimeOut)
{
	if (WaitForSingleObject(m_eventExit, dwTimeOut) == WAIT_OBJECT_0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CCameraControlThread::PushBack(ptz_control_t *p_ctrl_t)
{
	USE_SYNCHRONIZE
	{
		CSingleLock sl(&m_ptzQueue);
		if (!sl.Lock(NTIMEOUT))
		{
			return FALSE;
		}
		if (m_bClosing == TRUE)
		{
			return FALSE;//不再接收数据
		}
		m_ptzQueue.push_back(p_ctrl_t);
	}
	return TRUE;
}

ptz_control_t* CCameraControlThread::PopFront()
{
	ptz_control_t *pResult = NULL;
	USE_SYNCHRONIZE
	{
		CSingleLock sl(&m_ptzQueue);
		if (!sl.Lock(NTIMEOUT))
		{
			return pResult;
		}

		if (m_ptzQueue.size() > 0)
		{
			pResult = *m_ptzQueue.begin();
			m_ptzQueue.pop_front();
		}
		return pResult;
	}
}