#pragma once

#ifdef __HTTP_API_EXP_
#define HTTP_APT extern "C" __declspec(dllexport)
#else
#define HTTP_APT extern "C" __declspec(dllimport)
#endif

namespace HTTP_LIB
{
    #define MAX_PARAM_NUM    16
	#define REQ_TYPE_GET 	 0
	#define REQ_TYPE_POST 	 1
	#define RESP_TYPE        2
	#define HTTP_XML_BUF_SIZE	 256*1024

	typedef struct  http_object_t
	{
		int 		type;		// type
		int			seq;
		char		cmd[32];	// command
		char		xml[HTTP_XML_BUF_SIZE];
		struct    param{
			char	 paramName[256];
			char	 paramValue[256];
		}cmdparm[MAX_PARAM_NUM];
	}HTTP_OBJECT;

	//recv
	HTTP_APT int st_http_recvHttpPackage (int sock, char *recv_buf); 
	//pack interface
	HTTP_APT char *st_http_addParam (char *buffer, char *fmt, ...);
	HTTP_APT char * st_http_makeHttp(const char * type,		//����������������Ӧ
						unsigned int seq,		//�������, �������к�
						char *buffer,			//�������, ���ķ���ֵ
						int *len,				//�������, ���ĳ���
					    char *cmd ,				//�������, �����ִ�
						char *param_buf=NULL,	//�������, http�����ִ�,��ӦʱĬ��Ϊ��
						char *xml_buf=NULL);	//�������, ����ʱĬ��Ϊ��
	//parse interface
	HTTP_APT unsigned char st_http_parseHttp (const char *recv_buf, HTTP_OBJECT *ho_ptr);
	HTTP_APT int st_http_parseHttpParam (HTTP_OBJECT *ho_ptr, const char *szParam, char *parseBuf);
}
