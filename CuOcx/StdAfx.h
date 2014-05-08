#if !defined(AFX_STDAFX_H__08590DEB_D0E7_43A2_A404_0E3DEEBA7856__INCLUDED_)
#define AFX_STDAFX_H__08590DEB_D0E7_43A2_A404_0E3DEEBA7856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes

#include <afxole.h>
#include <AFXMT.H>
#include <mmsystem.h>
#include <afxinet.h>

#include <afxmt.h>                       // 同步对象类
#include <afxtempl.h>                    // 模板类
#include <ocidl.h>
#include <OLE2.H>
#include <olectl.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <wingdi.h>
#include <afxsock.h>		// MFC socket extensions
#include <objbase.h>
#include <AFXPRIV2.H>

#import "c:/windows/system32/msxml3.dll"
using namespace MSXML2;

#include "../include/dev_type.h"
#include "../include/CU_NETAPI.h"
#include "../include/global.h"
#include "../include/vod.h"
#include "../include/I_AVI.H"
#include "../include/PlayLib.h"
#include <list>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "../lib/CU_NetLib.lib") 
#pragma comment(lib, "../lib/vod.lib")
#pragma comment(lib, "../lib/AVI.lib")
#pragma comment(lib, "../lib/PlayLib.lib")
#pragma comment(lib, "../lib/PlaySDK.lib")

typedef struct _ptz_control_t
{
	char    csgIp[32];	
	char    cmd[32];
	char    param[32];
	char    msgtype[32];
	UINT    csgport;
	int     speed;
	CU_NET_LIB::GUINFO  guInfo;
}ptz_control_t;

#include "Syncronization.h"
#include "VideoManage.h"
#include "CameraControlThread.h"

#define NTIMEOUT 5000
#define WM_DOWNLOADMSG  (WM_USER+IDD_DIALOG_DOWNLOAD)


extern DWORD g_dwServerId;
extern DWORD g_dwAudioInstance;
extern char g_szDomainID[32];
extern CVideoManage g_VideoMng;

extern unsigned char g_HK8016_HeadBuf[40];
extern unsigned char g_HK8116_HeadBuf[40];

typedef std::list<CU_NET_LIB::GUINFO*> GUINFO_OCX;
extern SyncObject<GUINFO_OCX, CCriticalSection> g_GuInfoList;
typedef std::list<CU_NET_LIB::DEVICE_NODE*> DEVICENODE_OCX;
extern DEVICENODE_OCX g_DeviceNodeList;

#define MAX_TOUR_NAME		12
#define MAX_GROUP_NAME		12
#define MAX_TOUR_STEP		12
#define MAX_GROUP_STEP		12
#define MAX_DISPLAY_NUM		100

#define BTN_DOWN_DIS         2
#define BTN_UP_DIS           2
#define SM_CXMAXIMIZED       61
#define SM_CYMAXIMIZED       62

//文件类型
#define FILETYPE_ERR			0
#define FILETYPE_REC_LOCAL		1
#define FILETYPE_REC_VOD		2
#define FILETYPE_REC_PU			3
#define FILETYPE_PIC_LOCAL		11
#define FILETYPE_PIC_VOD		12
#define FILETYPE_PIC_PU			13

#define TEXT_MAXLEN	   256
// #define WM_DOWNLOADMSG  (WM_USER+IDD_DIALOG_DOWNLOAD)


//GU_TYPE定义
#define GU_TYPE_AV_MASTER		0x01
#define GU_TYPE_ALARM_INPUT		0x02
#define GU_TYPE_ALARM_OUTPUT	0x03
#define GU_TYPE_DECODE_CH		0x04
#define GU_TYPE_DISPLAY_CH		0x05
#define GU_TYPE_AV_SLAVE		0x06

#define MAX_DEVICE_NODE_NUM	256

struct _timerec_seg_t
{
	int		bFlag;      //是否启用
	int		start_hour;
	int		start_minute;
	int		start_second;
	int		end_hour;
	int		end_minute;
	int		end_second;
};

typedef struct _timerec_runtime_info_t
{
	BOOL bAotuStart;//是否随程序启动而启动；
	BOOL bStart; //是否启动录像
	
	BOOL bReConn;
	
	char szGuid[32];    //guid
	char szGuname[32];  //guname
	CU_NET_LIB::GUINFO *guInfo;     //szGuid 与 设备列表遍历后得到的树的项的DEVICE_NODE
	BOOL bFind;	        //szGuid 与 设备列表遍历后得到的 该guid是否存在的值
	void *pthis;
	HANDLE hExitEvent;
	HANDLE hExitThread;
	
	int runState;//线程运行状态0正常，1挂起，2切盘
	//int nSwitchTime;
	
	//CEvent m_hNotiy;
	HANDLE  hNotify;
	void *pVideoIns;
	void *prf;
	CRITICAL_SECTION g_cs;
	HANDLE hRecFile;
	SYSTEMTIME sysCreateTime;
	
	_timerec_seg_t     time_seg[7];
}_timerec_runtime_info_t;

typedef struct _TimeRec_FileInfo_t
{
	char filepath[MAX_PATH];
	char szCreateTime[32];
	char szLastWriteTime[32];
	DWORD dwFileSize;
}TimeRec_FileInfo_t;

typedef struct TimeRec_Day_t
{
	int year;
	int month;
	int day;
}TimeRec_Day_t;

typedef struct TimeRec_Time_t
{
	int hour;
	int minute;
	int second;
}TimeRec_Time_t;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__08590DEB_D0E7_43A2_A404_0E3DEEBA7856__INCLUDED_)
