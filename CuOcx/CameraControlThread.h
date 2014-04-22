// CameraControlThread.h: interface for the CCameraControlThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERACONTROLTHREAD_H__2650A496_B4B0_47A9_BDCD_319CE869B74E__INCLUDED_)
#define AFX_CAMERACONTROLTHREAD_H__2650A496_B4B0_47A9_BDCD_319CE869B74E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "Syncronization.h"
#include <algorithm>
#include <list>

class CCameraControlThread
{
public:
	CCameraControlThread();
	virtual ~CCameraControlThread();
	BOOL PushBack(ptz_control_t *p_ctrl_t);

private:
	void Init();
	void DeInit();
	void ExitThread();
	BOOL WaitToExit(DWORD dwTimeOut);
	static UINT AFX_CDECL ptzControlThread(LPVOID lParam);
	
	ptz_control_t* PopFront();
private:
	typedef std::list<ptz_control_t *> PTZLIST;
	SyncObject<PTZLIST, CMutex> m_ptzQueue;
	CWinThread *m_pptzThread;
	CEvent m_eventExit;
	BOOL m_bClosing;//正在关闭，不允许往队列中插入数据
};

#endif // !defined(AFX_CAMERACONTROLTHREAD_H__2650A496_B4B0_47A9_BDCD_319CE869B74E__INCLUDED_)
