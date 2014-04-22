// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

DWORD g_dwServerId = 0;
DWORD g_dwAudioInstance = 0;
char g_szDomainID[32];
CVideoManage g_VideoMng;
CCameraControlThread g_CameraCtrl;

SyncObject<GUINFO_OCX, CCriticalSection> g_GuInfoList;
DEVICENODE_OCX g_DeviceNodeList;