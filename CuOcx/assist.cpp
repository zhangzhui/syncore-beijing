#include "StdAfx.h"
#include "assist.h"

namespace Assist
{
	BOOL ParseDomain(char* szDomainName)
	{
		CString strIP;
		struct hostent * hp;
		char szIP[128] = {0};
		if ((hp = gethostbyname(szDomainName)) != NULL)//根据网络域名ip获取对应的IP地址
		{
			struct in_addr inAddr;
			LPSTR  lpAddr = hp->h_addr_list[0];
			if(lpAddr)     
			{
				//struct in_addr inAddr;   
				memmove(&inAddr, lpAddr, 4);   
				strIP = inet_ntoa(inAddr);   
				if(strIP.IsEmpty())
				{
					strIP =  _T("Not available");
				}
				sprintf(szIP, "%s", strIP);
			}
		}
		else
		{
			int nRes = WSAGetLastError();
			return FALSE;
		}
		
		sprintf(szDomainName, szIP);
		return TRUE;
	}
}