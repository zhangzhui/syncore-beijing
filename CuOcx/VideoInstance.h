#pragma once
#include "StdAfx.h"
typedef void (CALLBACK* RecvDataFunc)(long lHandle,     // 客户标识
									  void* lpBuf,      // 数据缓冲区指针
									  long lSize,       // 缓冲区大小
									  long lDecoderID   // 解码类型扩展
									  );
typedef struct
{
	long     lHandle;           // 客户标识
	HANDLE   hNotify;           // event对象
	RecvDataFunc   lpFunc;      // 客户对应的回调函数
}CLIENT_STRUCT;

class CVideoInstance : public CObject
{
public:
	CVideoInstance();
	virtual ~CVideoInstance();
	
private:
    int       m_nBuf;                   // 记录BUF中数据长度
	CWinThread*  m_pThread;
	CWinThread*  m_pThreadReconnect;
	CEvent    m_EventReconnect;
	DWORD     m_LastReconnect;
	BOOL	  m_bReconnectOk;
	BOOL	  m_bStraightConn;
	BOOL	  m_bLinkState;
	
public:
	CTypedPtrList<CPtrList, CLIENT_STRUCT*> m_List;// 所有客户的结构列表
	CCriticalSection m_csList;
	DWORD		m_dwFlag;
	CU_NET_LIB::GUINFO		m_guInfo;
	LONG		m_hVideo;
	
	
	BOOL m_bReconnectStatus;
	CCriticalSection m_csReConnect;
public:
	
	BOOL  Start(const CU_NET_LIB::GUINFO& guInfo, LONG lHandle, HANDLE hNotify, RecvDataFunc lpFunc); 
	BOOL  Stop(LONG lHandle);
	BOOL  Reconnect();
	
	static UINT Thread_Start(LPVOID lParam);
	static UINT Thread_Reconnect(LPVOID lParam);
	void   WaitForThread();
	DWORD  GetFlag(){ return m_dwFlag; }

	BOOL GetReConnectStatus(){return m_bReconnectOk;}
	void SetReconnectStatus(BOOL bFlag);
};
/*
// 前提, 视频请求时不能进行任何停止视频的操作
1. 窗口启动视频前, 先检查是否已经存在要请求的GUID, 若已经存在, 则返回该对象指针, 转第2步, 否则转第3步
2. 创建一个新的CVieoInstance对象, 保存指针, 并设置对象的GUDINFO属性; 
ps: 这里是同步方式;  
3. 调用CVieoInstanc::StartRealMedia, 结束;

  4. 调用Stop, 检查是否只存在一个引用,如果是则退出这个连接; 如果不是, 则仅在列表中删除它
  5. 视频数据的回调函数负责对视频的分发, 依据是列表中的对象;
  6. 需要注意的是, 在视频分发的过程中, 一定首先保证指针的有效性;
-------------------------------------------------*/