// VideoInsList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoManage.h"
#include "VideoInstance.h"

// CVideoManage

CVideoManage::CVideoManage()
{
}

CVideoManage::~CVideoManage()
{
}
// CVideoManage ��Ա����
POSITION  CVideoManage::FindInsByGuid(LPCTSTR lpszGuid)
{
	m_csList.Lock();
	POSITION pos = m_List.GetHeadPosition();
	while(pos)
	{
		CVideoInstance* pIns = m_List.GetAt(pos);
		if( 0 == strcmp(pIns->m_guInfo.GUID, (const char *)lpszGuid))
			break;
		else
			m_List.GetNext(pos);
	}
	m_csList.Unlock();
	return pos;  // �޶�ӦԪ���򷵻�NULL;
}

CVideoInstance*  CVideoManage::CreateVideoInstance(LPCTSTR lpszGuid)
{
	CVideoInstance* pIns = NULL;
	m_csList.Lock();
	POSITION pos = FindInsByGuid(lpszGuid);
	if( pos == NULL)
	{
		pIns = new CVideoInstance;
		if(pIns)
			m_List.AddTail(pIns);
	}
	else
	{
		pIns = m_List.GetAt(pos);
	}
	m_csList.Unlock();
	return pIns;
}
void CVideoManage::ReleaseInstance(CVideoInstance* pInstance)
{
	m_csList.Lock();
	POSITION pos = m_List.GetHeadPosition();
	while(pos)
	{
		CVideoInstance* pIns = m_List.GetAt(pos);
		if(pIns == pInstance)
		{
			m_List.RemoveAt(pos);
			break;
		}
		else
			m_List.GetNext(pos);
	}
	m_csList.Unlock();
	
}
