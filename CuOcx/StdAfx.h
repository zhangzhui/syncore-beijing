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

#include "Syncronization.h"

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

extern DWORD g_dwServerId;
extern DWORD m_gdwAudioInstance;
extern char g_szDomainID[32];


typedef std::list<CU_NET_LIB::GUINFO*> GUINFO_OCX;
extern SyncObejct<GUINFO_OCX, CCriticalSection> g_GuInfoList;
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__08590DEB_D0E7_43A2_A404_0E3DEEBA7856__INCLUDED_)
