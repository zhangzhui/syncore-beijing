#pragma once
#include "StdAfx.h"
typedef void (CALLBACK* RecvDataFunc)(long lHandle,     // �ͻ���ʶ
									  void* lpBuf,      // ���ݻ�����ָ��
									  long lSize,       // ��������С
									  long lDecoderID   // ����������չ
									  );
typedef struct
{
	long     lHandle;           // �ͻ���ʶ
	HANDLE   hNotify;           // event����
	RecvDataFunc   lpFunc;      // �ͻ���Ӧ�Ļص�����
}CLIENT_STRUCT;

class CVideoInstance : public CObject
{
public:
	CVideoInstance();
	virtual ~CVideoInstance();
	
private:
    int       m_nBuf;                   // ��¼BUF�����ݳ���
	CWinThread*  m_pThread;
	CWinThread*  m_pThreadReconnect;
	CEvent    m_EventReconnect;
	DWORD     m_LastReconnect;
	BOOL	  m_bReconnectOk;
	BOOL	  m_bStraightConn;
	BOOL	  m_bLinkState;
	
public:
	CTypedPtrList<CPtrList, CLIENT_STRUCT*> m_List;// ���пͻ��Ľṹ�б�
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
// ǰ��, ��Ƶ����ʱ���ܽ����κ�ֹͣ��Ƶ�Ĳ���
1. ����������Ƶǰ, �ȼ���Ƿ��Ѿ�����Ҫ�����GUID, ���Ѿ�����, �򷵻ظö���ָ��, ת��2��, ����ת��3��
2. ����һ���µ�CVieoInstance����, ����ָ��, �����ö����GUDINFO����; 
ps: ������ͬ����ʽ;  
3. ����CVieoInstanc::StartRealMedia, ����;

  4. ����Stop, ����Ƿ�ֻ����һ������,��������˳��������; �������, ������б���ɾ����
  5. ��Ƶ���ݵĻص������������Ƶ�ķַ�, �������б��еĶ���;
  6. ��Ҫע�����, ����Ƶ�ַ��Ĺ�����, һ�����ȱ�ָ֤�����Ч��;
-------------------------------------------------*/