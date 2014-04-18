#pragma once
class CVideoInstance;
// CVideoManage ÃüÁîÄ¿±ê

class CVideoManage : public CObject
{
public:
	CVideoManage();
	virtual ~CVideoManage();

public:
	CCriticalSection        m_csList;
private:
	CTypedPtrList<CPtrList, CVideoInstance*>   m_List;
	POSITION  FindInsByGuid(LPCTSTR lpszGuid);

public:
	CVideoInstance*  CreateVideoInstance(LPCTSTR lpszGuid);
	void ReleaseInstance(LPCTSTR lpszGuid);
	void ReleaseInstance(CVideoInstance* pInstance);
};
