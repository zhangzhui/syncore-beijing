// TimeRecRuntime.h: interface for the CTimeRecRuntime class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

typedef struct  __Find_file_t
{
	char   FileName[MAX_PATH];
	FILETIME CreateFileTime;
	FILETIME LastWriteTime;
	DWORD dwFileSize;
	//   SYSTEMTIME sTime;
}Find_file_t;


// struct - xuyz ------------------------------------
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

struct _timerec_runtime_info_t;
// end struct ---------------------------------------


class CTimeRecRuntime  
{
public:

	BOOL m_bRefreshState;
	BOOL m_bAutoFlag;

	BOOL m_bExit;
	HANDLE m_hCheckEvent;//event
	HANDLE m_hCheckThread;

	//¥≈≈Ã≈‰÷√
	BOOL	m_bCoverFlag;
	UINT	m_iResSize;
	UINT	m_iSwitchTime;
	UINT    m_iDiskNum;
	CString strDrive[128];
	int m_nDriverIndex;

	CString m_szServerIP;
	CString m_szLoginUserName;


public:
	int IniRuntimeInfo();
	CTimeRecRuntime();
	virtual ~CTimeRecRuntime();

public:
	void DelRuntimeInfo();
	static UINT StopRunThread(LPVOID lPvoid);

	void FindFile(char *guName,TimeRec_Day_t yymmdd,TimeRec_Time_t startTime,TimeRec_Time_t endTime,TimeRec_FileInfo_t *pfile,int *fileNum);
	void RefreshState();
	void ModifyThreadState(int nState);
	BOOL CheckCurDisk(int n);
	BOOL LoadRuntimeInfo();
	Find_file_t DelFiles[1024];
	bool DeleteDirectory(char* sDirName);
	BOOL  FindDelDir();
	void AotuRunAllRec();
	void SaveRuntimeInfo();
	void CreateNewFile(_timerec_runtime_info_t *  pInfo);
	void StopRecByIndex(int nIndex);
	void StartRecByIndex(int nIndex);
	_timerec_runtime_info_t *GetOneRuntimeInfo(int nIndex);
	//void ModifyOneRuntimeInfo(_timerec_runtime_info_t *Info , int nIndex);
	void AddRuntimeInfo(_timerec_runtime_info_t *Info);
	void DelRuntimeInfo(int nIndex);
	void StartRec(_timerec_runtime_info_t *  pInfo);
	void StopRec(_timerec_runtime_info_t *  pInfo);
	CCriticalSection   cs;
	CTypedPtrList<CPtrList, _timerec_runtime_info_t*> g_timerecInfoList;

};
