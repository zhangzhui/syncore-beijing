// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

DWORD g_dwServerId = 0;
DWORD m_gdwAudioInstance = 0;
char g_szDomainID[32];

SyncObejct<GUINFO_OCX, CCriticalSection> g_GuInfoList;
DEVICENODE_OCX g_DeviceNodeList;