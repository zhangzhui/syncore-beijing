//BssClient.h
#ifndef __BssClient_H
#define __BssClient_H

#if defined( _WINDLL)
#define BSSCLIENT_API  extern "C" __declspec(dllexport) 
#else 
#define BSSCLIENT_API  extern "C" __declspec(dllimport) 
#endif
//244
//extern int m_nCountTest;
#include <string>
#include <vector>
#include <list>
#include <set>
using namespace std;
typedef struct AREAINFO
{
	BOOL    bDomain;            //TRUEΪ��ṹ��FALSEΪ����
	char    DomainName[32];      //����
	char    DomainID[32];        //��ID
	char    UpDomainID[32];      //�ϼ���ID
	char    DomainIP[16];        //��IP��ַ
	char    CSGIP[32];          //CSG IP    
	char    Remark[128];        //��ע
	
	char    AreaName[32];       //������
	char    AreaID[32];         //����ID
	char    UpAreaID[32];       //�ϼ�����ID
	char    UpAreaName[32];     //�ϼ���������
}_AREAINFO;

//����Ա����
typedef struct	ADMININFO		
{
	char	AdminCount[32];		//�ʺ����ƣ�
	char	AdminPWD[32];		//�ʺ����룻
	char    DomainID[32];       //��ID��
	char    DomainName[32];     //DoaminName;
	char	AreaID[32];			//����ID��
	char    AreaName[32];       //��������
	BOOL    bLevel;             //��������Ա1,��Ϊ0��
}_ADMININFO;
//�ͻ��ṹ
typedef struct	CLIENTINFO		
{
	char	ClientID[32];    	//�ͻ�ID
	char    DomainID[32];		//������domainID
	char    DomainName[32];
	char    AreaID[32];			//��������ID
	char    AreaName[64];
	char    Certificate[32];    //���֤����
	char    Birth[32];          //����
	BOOL    bSex;				//�Ա�
	BOOL    bMarriage;          //����״��
	char    Education[32];      //ѧ��
	char    School[32];         //��ҵԺУ
	char    workDepartment[32]; //������λ
	
}_CLIENTINFO;
//�û��ṹ
typedef struct USERINFO{
	char    User[32];         //�û�ID
	char    Password[32];     //�û�����
	char    ClientID[32];     //�����ͻ�ID  
	BOOL    bCheckActive;     //����״̬
	char   	DayName[32];      //��������
	long    Cyc;              //��������
	long    nLoginMode;       //��¼ģʽ  1������ʽ��Ĭ��ģʽ����2����ռʽ��3����ռʽ
	int		nNum;			  //������
//add by wy 2010.01.08
	BOOL    m_bSupperUsr;
//add end
}_USERINFO;

//Ȩ�޽ṹ
typedef struct SECURITYINFO
{
	char    User[32];
	char    GUID[32];
	char    DomainID[32];
	char    GuidName[32];
	char    DefenID[32];
	char    DefenName[32];
	char    TvwallID[32];
	char    TvwallName[32];
	char    GroupName[32];
	char    GroupID[32];
	char    TourID[32];
	char    TourName[32];
	int		Right;
	long	lDomeRight; //��̨����Ȩ�ޣ�0�ޣ�1��2��3�С�Ĭ��1
}_SECURITYINFO;

//��ش������ṹ  2014-08-19 by hhs
typedef struct __ck_ch_param_t
{
	char use_flag;
	char ck_type;
	char unuse[2];
	
	char ck_name[32];
	char ck_id[16]; //eg: yc00001
	
	float alarm_up_val;
	float alarm_down_val;
	
	
	
}ck_ch_param_t;

typedef struct __ck_dev_param_t
{
	int dev_id;
	
	char use_flag;
	char dev_type;
	char unused[2];
	
	
	char dev_name[32];
	
	ck_ch_param_t ck_ch_param[8];
	
}ck_dev_param_t;

//�豸�ṹ
typedef struct  PUIDINFO{
	char    PUName[32];			//�豸��
	char    PUID[32];			//�豸PUID
	char    PUIP[32];			//PUIP
	long    Active;				//����״̬��0-��ֹͣ��δ����Ȩ�����ɱ����ʣ�1-���ã��Ѿ�����Ȩ����ϵͳ
	char    DomainName[32];		//����
	char    DomainID[32];		//������ID
	char    AreaName[32];  //��������
	char    AreaID[32];    //��������ID
	char    MduName[32];        //
	char    MduID[32];
	char    MsuName[32];
	char    MsuID[32];
	long    HeartFreq;
	int 	DeviceType;
	char	Description[1024];
//add by wy 2010.01.08
	BOOL	m_bOnlineNote;
	int		m_nOnlineNoteMode;
	char	m_szPhoteNum[12];
	char	m_szMsgContent[256];
	BOOL    m_bSaveGPSLog;
	int		m_nSaveGPSTimeSpan;
	char    m_szPosition[512];
	char    szDeviceType[32];
	char    szMulticastIP[32];
//add end
}_PUIDINFO;
//�豸ҵ��
typedef struct GUIDINFO{
	char     GuidName[32];      //ҵ����
	char     GUID[32];          //ҵ��GUID
	long     GuidType;          //ҵ�����ͣ�1-����Ƶ��2-�������룬3-�������, 4-������,5-��ʾͨ��, 6-����Ƶ(��)
	char     PUID[32];          //�����豸PUID
	char     DomainID[32];		//������ID
	char     WndModeID[32];             //����ģʽ����ʾͨ����
	char	 Description[1024];
	char	 AlarmText[512];
	char     MSUID0[32];        //��һ��MSUID
	char     MSUNAME0[32];      //��һ��MSUNAME
	char     MSUID1[32];        //�ڶ���MSUID
	char     MSUNAME1[32];      //�ڶ���MSUNAME
	char     MSUID2[32];        //������MSUID
	char     MSUNAME2[32];      //������MSUNAME
	char     szAlarmDevDefID[32]; //������������ID add by wy 2010.06.18
//	ck_dev_param_t ck_dev_param;
// 	char	 use_flag1;          //��һ��������  //Add on 2014-08-27 by hhs
// 	char	 ck_type1;
// 	char	 ck_name1[32];
// 	char    alarm_up_val1[16];
// 	char    alarm_down_val1[16];
// 	
// 	char	 use_flag2;          //�ڶ���������
// 	char	 ck_type2;
// 	char	 ck_name2[32];
// 	char    alarm_up_val2[16];
// 	char    alarm_down_val2[16];
// 	
// 	char	 use_flag3;          //������������
// 	char	 ck_type3;
// 	char	 ck_name3[32];
// 	char    alarm_up_val3[16];
// 	char    alarm_down_val3[16];
// 	
// 	char	 use_flag4;          //���ĸ�������
// 	char	 ck_type4;
// 	char	 ck_name4[32];
// 	char    alarm_up_val4[16];
// 	char    alarm_down_val4[16];
// 	
// 	char	 use_flag5;          //�����������
// 	char	 ck_type5;
// 	char	 ck_name5[32];
// 	char    alarm_up_val5[16];
// 	char    alarm_down_val5[16];
// 	
// 	char	 use_flag6;          //������������
// 	char	 ck_type6;
// 	char	 ck_name6[32];
// 	char    alarm_up_val6[16];
// 	char    alarm_down_val6[16];
// 	
// 	char	 use_flag7;          //���߸�������
// 	char	 ck_type7;
// 	char	 ck_name7[32];
// 	char    alarm_up_val7[16];
// 	char    alarm_down_val7[16];
// 	
// 	char	 use_flag8;          //�ڰ˸�������
// 	char	 ck_type8;
// 	char	 ck_name8[32];
// 	char    alarm_up_val8[16];
// 	char    alarm_down_val8[16];


}_GUIDINFO;

//ת����������Ϣ�ṹ
typedef struct MDUINFO  {
	char    MduName[32];	        //ת����������
	char    MduID[32];		    //ת��ID
	char    DomainID[32];		//������ID
	long    nPort;              //�˿�
	long    HeartFreq;          //��������
	long    iClientNum;		//��ǰ�ͻ���
	long	iVideoNum;	//��ǰ�豸��
	
	BOOL m_bSaveState;
	int  m_nSaveIntv;
}_MDUINFO;
//�洢��������
typedef struct MSUINFO {
	char	MsuName[32];	//�洢��������
	char    MsuID[32];		//�洢������ID
	char    DomainID[32];   //DomainID
	long    nPort;          //�˿�
	long    HeartFreq;      //��������
	long    iVideoNum;	//���¼����Ƶ��
	long    iMaxVodClient; //���㲥��Ƶ��

	BOOL m_bSaveState;
	int  m_nSaveIntv;
}_MSUINFO;
//ת��·����Ϣ�ṹ
typedef struct MDUROUTEINFO  {
	char    MduID[32];		    //ת��ID
	char    MduIP[64];		    //ת��IP
	char    CmuIP[64];          //CMU IP
}_MDUROUTEINFO;

//�洢·����Ϣ�ṹ
typedef struct MSUROUTEINFO  {
	char    MsuID[32];		    //�洢ID
	char    MsuIP[64];		    //�洢IP
	char    CmuIP[64];          //CMU IP
}_MSUROUTEINFO;

typedef struct TVINFO {
	char    name[64];           //����
	char    ip[16];             //IP
	long    lX;                 //�ֱ���x
	long    lY;                 //�ֱ���y
}_TVINFO;
//REOCRDPLAN
typedef struct RECOPLAN {
	char	GuidName[32];       //ҵ������
	char	MsuID[32];
	long	recordType;        //��ʱ�������ա�
	char	startTime[32];     //��ʼʱ��
	char	endTime[32];       //����ʱ��
	long	recordTime;        //����¼��ʱ��
	long	preRecordTime;     //Ԥ¼ʱ��
	
}_RECOPLAN;
//DEFENCE
typedef struct DEFEINFO{
	char	DefeID[32];          //����ID
	char 	DefeName[32];        //�������� 
    char   DomainID[32];         //��ID
	char	AreaID[32];          //����ID
	char	MapID[32];           
	char    MapName[32];    	//��ͼID����
	BOOL	bState;              //���״̬
   	//SetParam
}_DEFEINFO;
//DEFEPARA
typedef struct DEFEELEM{
    char	DefeID[32];          //����ID
	char	GUID[32];            //GUID
	long	nType;               //��ص����͡�0-��Ƶ, 1-��������, 2-�������, ������
	char	MapID[32];        //�������� 
	long	xPos;                //��ص��ڷ�����ͼ�ϵ�X����
	long	yPos;                //��ص��ڷ�����ͼ�ϵ�Y����
	BOOL	bBypass;              //��·״̬��0-����·��1-����·
}_DEFEELEM;



//////////////////////////////
#define TV_NUM_MAX  (100*4)
#define		MAX_MONITOR_NUM		256
struct MONITOR_INFO{
	int		index;
	int		iLeft;
	int		iTop;
	int		iRight;
	int		iBottom;
	char	szDisplayName[32];
	char	szDisplayGUID[32];
};
struct TWCONFIG_INFO{
	char	szDomainID[32];
	char	szAreaID[32];
	char	szTVID[32];
	char	szName[32];
	BOOL	bUnaltered;
	int		iSplitX;
	int		iSplitY;
	int		iMonitor;
	BOOL	bDivPattern;
	UINT	uSwitchNO;
	int		iLeftMax;
	int		iTopMax;
	int		iRightMax;
	int		iBottomMax;
	MONITOR_INFO  monitor_info[MAX_MONITOR_NUM];
};

//����Ѳ��
#define MAX_TOURSTEP_NUM	128
struct TOURSTEP_INFO{
	int		iInterTime;
	char	szEncoderGUID[32];
	char	szDomainID[32];
	char	szEncoderName[32];
};
struct TOURCONFIG_INFO{
	char	szDomainID[32];
	char	szAreaID[32];
	char	szTourID[32];
	char	szName[32];
	int		iTourNo;
	int		iSteps;
	BOOL	bAutoJump;
	TOURSTEP_INFO	TourStep_info[MAX_TOURSTEP_NUM];
};
//����Ⱥ��
#define MAX_GROUPSTEP_NUM	128
#define MAX_GROUPDECODER_NUM	128 //
struct GROUPENCODER_INFO{ //
	char	szEncoderGUID[32];
	char	szDomainID[32];
	char	szEncoderName[32];
};
struct GROUPDECODER_INFO{ //
	char	szDescription[64];
	char	szDecoderGUID[32];
	char	szDecoderName[32];
	char	szDisplayGUID[32];
	char	szDisplayName[32];
	int     iWinNo;
};
struct GROUPSTEP_INFO{
	int		iInterTime;


	GROUPENCODER_INFO	GroupEncoder_info[MAX_GROUPDECODER_NUM];//
};

struct GROUPCONFIG_INFO{
	char	szDomainID[32];
	char	szAreaID[32];
	char	szGroupID[32];
	char	szName[32];
	int		iGroupNo;
	char	szTVID[32];
	char	szTVName[64];
	int		iMonitorNum;
	int		iStepCount;
	GROUPSTEP_INFO	GroupStepInfo[MAX_GROUPSTEP_NUM];
	

	int		iDecoderCount;//
	GROUPDECODER_INFO	GroupDecoder_info[MAX_GROUPDECODER_NUM];//
};
//�µ�Ⱥ��ṹ----------------------------------begin
struct GROUP_WND{ //Ⱥ�鲽�ڣ�����ǽ����һ���������е�һ��������Ϣ
	string strEncGuid;
	string strEncName;
};

typedef vector<GROUP_WND> GROUP_WNDLIST;
typedef vector<RECT> GROUP_RECTLIST;
struct GROUP_MONITOR{ //Ⱥ�鲽�ڣ�����ǽ����һ����������Ϣ
	GROUP_MONITOR() : pWndMode(NULL), bExclude(FALSE) {}
	string strWndModeID;
	GROUP_WNDLIST wnd_list;

	BOOL bExclude;
	TWCONFIG_INFO *pWndMode;
	GROUP_RECTLIST rcWnd_list;
};

typedef vector<GROUP_MONITOR> GROUP_MONITORLIST;
struct GROUP_STEP{ //Ⱥ�鲽
	GROUP_STEP() : iStepID(0) {}
	int iStepID;
	int iStepLen;
	GROUP_MONITORLIST monitor_list;

	GROUP_RECTLIST rcMonitor_list;
};
struct GROUP_INFO{ //Ⱥ��
	string strDomainID;
	string strAreaID;
	string strGroupID;
	string strGroupName;
	int iGroupNO;
	
	string strTVWallID;
	string strTVWallName;
	int iMonitorCount; //���Ⱥ��ʱ�ĵ���ǽ���������������������жϵ���ǽ�Ƿ�ṹ���ĵ�����

	auto_ptr<TWCONFIG_INFO> pTVWallInfo;

	list<GROUP_STEP> step_list;
};
//------------------------------�µ�Ⱥ��ṹend
typedef struct _RECPLANKEY
{
	string strGUID;
	string strDomainID;
	string strMSUID;
}RECPLANKEY;

typedef struct _DOMAININFO
{
	string strID;
	string strName;
	string strIP;
	string strPort;
	string strUser;
	string strPWD;
	string strType;   //0������		1������			2������
	BOOL m_bSaveState;
	int m_nSaveIntv;
}DOMAININFO;
typedef vector<DOMAININFO> DOMAINLIST;



BSSCLIENT_API extern DOMAINLIST g_listDomain;

//
BSSCLIENT_API long	ST_BSS_Login(const char* ip, int* port, const char* user, const char* pwd, char* buffer);

BSSCLIENT_API BOOL ST_BSS_Logout(long lClient);
//AreaInfo;//bFlag Ϊ���������Ϣ��Ϊ������ӻ�����Ϣ, buffer Ϊ��ӳɹ��󷵻ص�buffer)
BSSCLIENT_API int ST_BSS_AddAreaInfo(long lClient, BOOL bFlag, AREAINFO* pAreaInfo);
//bFlag Ϊ���������Ϣ��Ϊ������ӻ�����Ϣ, buffer Ϊ��ӳɹ��󷵻ص�buffer)
BSSCLIENT_API BOOL ST_BSS_DeleAreaInfo(long lClient, BOOL bFlag, char* pAreaID, const char* User, char* buffer);

BSSCLIENT_API BOOL ST_BSS_PropAreaInfo(long lClient, BOOL bFlag, AREAINFO* pAreaInfo, char* buffer);
//bFlag Ϊ���ѯ����Ϣ��Ϊ�ٲ�ѯ������Ϣ������ֵ����buffer��
BSSCLIENT_API BOOL  ST_BSS_QuerAreaInfo(long lClient, BOOL bSign, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL *bEnd);
BSSCLIENT_API BOOL  ST_BSS_QuerNextAreaInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd );

//AdminInfo;
BSSCLIENT_API int	ST_BSS_AddAdminInfo(long lClient, ADMININFO* pAdminInfo);
//pDelAdmin Ҫɾ�����û���pAdmin ��¼���û�
BSSCLIENT_API BOOL  ST_BSS_DeleAdminInfo(long lClient, char* pDelAdmin, char* pAdmin, char* pDomainID, char* AreaID);

BSSCLIENT_API int  ST_BSS_PropAdminInfo(long lClient, ADMININFO* pAdminInfo);
//��ѯ����Ա
BSSCLIENT_API BOOL  ST_BSS_QuerAdminInfo(long lClient, char* pDomainID, char *pAreaID, char* pUser, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_QuerNextAdminInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd);

//PUID
BSSCLIENT_API BOOL	ST_BSS_AddPuidInfo(long lClient, PUIDINFO* pPuidInfo, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_DelePuidInfo(long lClient, const char* pPuid, const char *pDomainID, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_PropPuidInfo(long lClient, PUIDINFO* pPuidInfo, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_QuerPuidInfo(long lClient, char* pDomainID, char* pAreaID, PUIDINFO *pPuidNode, BOOL bSign, int *pCount);

BSSCLIENT_API BOOL  ST_BSS_QuerNextPuidInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd);

//Add GUID, �����Ϊ���������͵�GUIDʱ��pGuidCode���Ǳ��������͵ģ�����ΪNULL
BSSCLIENT_API int ST_BSS_AddGuidInfo(long lClient, GUIDINFO* pGuidInfo, int& num);
BSSCLIENT_API BOOL ST_BSS_DeleGuidInfo(long lClient, char* pGuId, const char *pDomainID);
BSSCLIENT_API int ST_BSS_PropGuidInfo(long lClient, GUIDINFO* pGuidInfo, int& num);
//��ѯһ���������GUID
BSSCLIENT_API BOOL  ST_BSS_QuerGuidInfo(long lClient, char* pDomainID, char* pAreaID, GUIDINFO *pGuidNode, BOOL bSign, int *pCount);
BSSCLIENT_API BOOL  ST_BSS_QuerNextGuidInfo(long lClient, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL *bEnd);

//RecoPlan
BSSCLIENT_API BOOL	ST_BSS_AddRecordPlan(long lClient, char* addBuf, char* recvBuf);
BSSCLIENT_API BOOL	ST_BSS_AddRecPlanGuidList(long lClient, char* addBuf, char* recvBuf);
BSSCLIENT_API BOOL  ST_BSS_DeleRecordPlan(long lClient, char* pGuid, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_PropRecordPlan(long lClient, RECOPLAN* pRecoPlan, char* buffer);
//������ѯguid��¼�����
BSSCLIENT_API BOOL  ST_BSS_QuerRecordPlan(long lClient,const char *pGuID, const char *pDomainID, const char* pMsuID, char* buffer, int* len, BOOL *bEnd);
BSSCLIENT_API BOOL  ST_BSS_QuerNextRecordPlan(long lClient, char* pGuId, char* buffer, int* len, BOOL *bEnd);
//MSU
BSSCLIENT_API int	ST_BSS_AddMsuInfo(long lClient, MSUINFO* pMsuInfo);
BSSCLIENT_API int   ST_BSS_DeleMsuInfo(long lClient, char* pMsuId);
BSSCLIENT_API int ST_BSS_PropMsuInfo(long lClient, MSUINFO* pMsuInfo, int& num);
BSSCLIENT_API BOOL  ST_BSS_QuerMsuInfo(long lClient, char* pDomainID, char* pAreaID, MSUINFO *pMsuNode, int nMaxNum, int *pCount);
BSSCLIENT_API BOOL  ST_BSS_QuerNextMsuInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd);
//MDU
BSSCLIENT_API int	ST_BSS_AddMduInfo(long lClient, MDUINFO* pMduInfo);
BSSCLIENT_API int  ST_BSS_DeleMduInfo(long lClient, char* pMduId);
BSSCLIENT_API int ST_BSS_PropMduInfo(long lClient, MDUINFO* pMduInfo, int& num);
BSSCLIENT_API BOOL  ST_BSS_QuerMduInfo(long lClient, char* pDomainID, char* pAreaID, MDUINFO *pMduNode, int nMaxNum, int *pCount);
BSSCLIENT_API BOOL  ST_BSS_QuerNextMduInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL* bEnd);
//Route ���·����Ϣ1-mdu·�ɣ�2-msu·��
BSSCLIENT_API int	ST_BSS_AddRouteInfo(long lClient, int nType, char *pID, char *pIP, char *pCmuIP);
//Route ɾ��·����Ϣ1-mdu·�ɣ�2-msu·��
BSSCLIENT_API BOOL	ST_BSS_DeleRouteInfo(long lClient, int nType, char *pID, char *pIP, char *pCmuIP);
//Route ��ѯ·����Ϣ1-mdu·�ɣ�2-msu·��
BSSCLIENT_API BOOL	ST_BSS_QuerRouteInfo(long lClient, int nType, char *pID, char* buffer);
//Route �޸�·����Ϣ1-mdu·�ɣ�2-msu·��
BSSCLIENT_API BOOL	ST_BSS_PropRouteInfo(long lClient, int nType, char *pID, char *pIP, char *pCmuIP);

//TV
BSSCLIENT_API BOOL	ST_BSS_AddTvInfo(long lClient, TVINFO *pTvInfo, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_DeleTvInfo(long lClient, char* pTvName, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_PropTvInfo(long lClient, TVINFO *pTvInfo, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_QuerTvInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL* bEnd);
BSSCLIENT_API BOOL  ST_BSS_QuerNextTvInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL* bEnd);
//CLIENT
BSSCLIENT_API BOOL	ST_BSS_AddClientInfo(long lClient, CLIENTINFO* pClientInfo, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_DeleClientInfo(long lClient, char* pClienId, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_PropClientInfo(long lClient, CLIENTINFO* pClientInfo, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_QuerClientInfo(long lClient, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL* bEnd);
BSSCLIENT_API BOOL  ST_BSS_QuerNextClientInfo(long lClient, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL* bEnd);
//USER
BSSCLIENT_API int	ST_BSS_AddUserInfo(long lClient, USERINFO* pUserInfo);
BSSCLIENT_API int  ST_BSS_DeleUserInfo(long lClient, char* pUserId);
BSSCLIENT_API int  ST_BSS_PropUserInfo(long lClient, USERINFO* pUserInfo);
BSSCLIENT_API BOOL  ST_BSS_QuerUserInfo(long lClient, char* pClientID, char* buffer, int* len, BOOL* bEnd);
BSSCLIENT_API BOOL  ST_BSS_QuerNextUserInfo(long lClient, char* userInfo, int* len, BOOL *bEnd);
//�û�Ȩ��User=%s&GUID=%s&DomeRight=%s&EnConfig=%s&EnTalk=%s&EnBackPlay=%s
BSSCLIENT_API BOOL ST_BSS_AddUserSecurity(long lClient, char* buffer, char* outBuf);
BSSCLIENT_API BOOL ST_BSS_AddSecuInfosToSmu(long lClient, int nType, char* buffer, char* outBuf);
BSSCLIENT_API BOOL ST_BSS_DeleUserSecurity(long lClient, char* pUserID, char* pGuid, char* buffer);
BSSCLIENT_API BOOL ST_BSS_PropUserSecurity(long lClient, char* buffer, char* outBuf);
BSSCLIENT_API BOOL ST_BSS_QuerUserSecurityOneArea(long lClient, char* pUserID, char* pAreaID, char* pDomainID, char* buffer);	
//Ȩ�޲�ѯ
BSSCLIENT_API BOOL ST_BSS_QuerUserSecuInfos(long lClient, int nType, char* pUserID, char* pAreaID, char* pDomainID, char* buffer);	
//�û���GUID��BUFF��bSecurity ΪTRUE������GUID��ΪFALSE��û��GUID
// bFirst ΪTRUE������90����һ����ӣ�ΪFALSE�Ͳ��ǵ�һ��
// bHead  ΪTRUE���ǵ�һ��90��ΪFALS�Ͳ��ǵ�һ��90
BSSCLIENT_API char* ST_BSS_AddGuidToIni(long lClient, char* pAddBuf, SECURITYINFO *pSecurityInfo, BOOL bSecurity, BOOL bFirst, BOOL bHead);
//0-defen, 1-tvwall, 2-tour, 3-group
BSSCLIENT_API BOOL ST_BSS_AddSecuInfosToIni(long lClient, int nType, char* pAddBuf, SECURITYINFO *pSecurityInfo, BOOL bSecurity, BOOL bFirst, BOOL bHead);
//
//��������
BSSCLIENT_API BOOL ST_BSS_KeepAlive(long lClient);
BSSCLIENT_API BOOL ST_BSS_AddDefeInfo(long lClient, char *addBuf, char* buffer);
BSSCLIENT_API BOOL ST_BSS_DeleDefeInfo(long lClient, char* pDefeID, char* buffer);
BSSCLIENT_API BOOL ST_BSS_PropOneDefeInfo(long lClient, char *addBuf, char* buffer);
BSSCLIENT_API BOOL ST_BSS_QuerAreaDefeInfos(long lClient, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL* bEnd);//��ѯĳ�����������з�������Ϣ
BSSCLIENT_API BOOL ST_BSS_QuerOneDefeInfo(long lClient, char* pDefeID, char* buffer, int* len, BOOL* bEnd);//��ѯĳ����������Ϣ
//Ϊ�������һ��ͼԪ
BSSCLIENT_API BOOL ST_BSS_AddDefeGuid(long lClient, char* addBuf, char* buffer);
BSSCLIENT_API BOOL ST_BSS_DeleDefeGuid(long lClient, char* pDefeID, char* pGuid,  const char *pDomainID, char* buffer);
BSSCLIENT_API BOOL ST_BSS_PropDefeGuid(long lClient, char* pDefeID, char* pGuid, const char *pDomainID, int xPos, int yPos, char* buffer);
BSSCLIENT_API BOOL ST_BSS_QuerDefeGuid(long lClient, char* pDefeID, char* buffer, int *len, BOOL *bEnd);
//iType = 0-���������Ϣ(��ӷ���ʱ��pDefeNameNew = "NULL", �޸ķ����õ�pDefeNameNew)��2-��������
BSSCLIENT_API BOOL ST_BSS_RequstDefe(long lClient, int iType, char* pDefeName, char* pDomainID, char* pAreaID, char* pDefeNameNew, char* buffer); 
BSSCLIENT_API BOOL ST_BSS_ReceiveRequ(long lClient); //����SMU����ӷ�����Ϣ������(TRUE-�յ���FALSE-û�յ�)
//���������GUID, iTypt=0��ӣ�iType=1�޸�
BSSCLIENT_API BOOL ST_BSS_RequDefeGuid(long lClient, int iType, char* pDefeID, char* pGuid, const char *pDomainID, char* buffer); 
//iType 0(����Ƶ)��1(Ԥ��λ)
BSSCLIENT_API BOOL ST_BSS_RequLnk(long lClient, int iType, char* pDefeID, char* pGuid, const char *pDomainID, char* buffer);
//�������
BSSCLIENT_API BOOL ST_BSS_AddLnkInfo(long lClient, char* addBuf, char* buffer);
//��ѯ����
BSSCLIENT_API BOOL ST_BSS_QuerLnkInfo(long lClient, char* pDefeID, char* pGuid, const char *pDomainID, char* buffer, int *len, BOOL *bEnd);
//��ѯ���еķ������ƺ�ID
BSSCLIENT_API BOOL ST_BSS_QuerAllMaps(long lClient, char* buffer);
//��������Ĳ���
BSSCLIENT_API BOOL	ST_BSS_AddLnkAllInfo(long lClient, char* addBuf, char* recvBuf);
//��ѯ��������
BSSCLIENT_API BOOL ST_BSS_QuerLnkAllInfo(long lClient, char* pGuId, char* EvtCode, const char *pDomainID, char* buffer, int* len, BOOL *bEnd);
//����TvwallID
BSSCLIENT_API int ST_BSS_GetTvwallID(long lClient, char *pDomainID, char *pAreaID, char *pTvwallName, UINT uSwitchNo, char *pTvwallID);
//����TourID
BSSCLIENT_API int  ST_BSS_GetTourID(long lClient, char *pDomainID, char *pAreaID, char *pTourName, int nTourNo, BOOL bAutoJump, char *pTourID);
//����GroupID
BSSCLIENT_API int  ST_BSS_GetGroupID(long lClient, char *pDomainID, char *pAreaID, char *pGroupName, int nGroupNo, char *pGroupID);
//��ӵ���ǽ�Ļ�����Ϣ
BSSCLIENT_API int  ST_BSS_AddTvwallBase(long lClient, TWCONFIG_INFO *pTvwallInfo);
//��ӵ���ǽ����ϸ��Ϣ
BSSCLIENT_API BOOL  ST_BSS_AddTvwallInfos(long lClient, TWCONFIG_INFO *pTvwallInfo);
//���Ѳ�ػ�����Ϣ 
BSSCLIENT_API BOOL  ST_BSS_AddTourBase(long lClient, TOURCONFIG_INFO *pTourInfo);
//���Ѳ����ϸ��Ϣ 
BSSCLIENT_API BOOL  ST_BSS_AddTourInfos(long lClient, TOURCONFIG_INFO *pTourInfo);
//���Ⱥ�������ϢAreaID=%s&DomainID=%s&GroupID=%s&Name=%s&GroupNo=%d",
BSSCLIENT_API int  ST_BSS_AddGroupBase(long lClient, GROUPCONFIG_INFO *pGroupInfo);
//���Ⱥ����ϸ��Ϣ
BSSCLIENT_API BOOL  ST_BSS_AddGroupInfos(long lClient, GROUPCONFIG_INFO *pGroupInfo);
//�༭����ǽ�Ļ�����Ϣ
BSSCLIENT_API int  ST_BSS_PropTvwallBase(long lClient, TWCONFIG_INFO *pTvwallInfo);
//�༭Ѳ�ػ�����Ϣ
BSSCLIENT_API int  ST_BSS_PropTourBase(long lClient, TOURCONFIG_INFO *pTourInfo);
//�༭Ⱥ�������Ϣ
BSSCLIENT_API int  ST_BSS_PropGroupBase(long lClient, GROUPCONFIG_INFO *pGroupInfo);

//�༭����ǽ����ϸ��Ϣ
BSSCLIENT_API int ST_BSS_PropTvwallCont(long lClient, TWCONFIG_INFO *pTvwallInfo);
//�༭Ѳ����ϸ��Ϣ
BSSCLIENT_API int  ST_BSS_PropTourCont(long lClient, char *pTourID);
//�༭Ⱥ����ϸ��Ϣ
BSSCLIENT_API int  ST_BSS_PropGroupCont(long lClient, char *pGroupID);
//��ѯһ�������µ����е���ǽ(������Ϣ)
BSSCLIENT_API BOOL  ST_BSS_QuerOneAreaTvwallInfos(long lClient, char *pDomainID, char *pAreaID, char *buffer);
//��ѯ����ǽ��Ϣ
BSSCLIENT_API BOOL ST_BSS_QuerOneTvwallInfos(long lClient, const char* pTvwallID, TWCONFIG_INFO *pTvwallInfo);
//��ѯһ��Ѳ�صľ�����Ϣ
BSSCLIENT_API BOOL  ST_BSS_QuerOneTourInfos(long lClient, char* pTourID, TOURCONFIG_INFO *pTourInfo);
//��ѯһ��Ⱥ��ľ�����Ϣ
BSSCLIENT_API BOOL  ST_BSS_QuerOneGroupInfos(long lClient, GROUP_INFO *pGroupInfo);
//Query Tour 2008-11-04//��ѯһ������������Ѳ��(������Ϣ)
BSSCLIENT_API BOOL  ST_BSS_QuerOneAreaTourInfos(long lClient, char* pDomainID, char* pAreaID, char* buffer);
//Query Group 2008-11-04//��ѯһ������������Ⱥ��(������Ϣ)
BSSCLIENT_API BOOL  ST_BSS_QuerOneAreaGroupInfos(long lClient, char* pDomainID, char* pAreaID, char* buffer);
//ɾ��Tvwall
BSSCLIENT_API BOOL ST_BSS_DeleteTvwall(long lClient, TWCONFIG_INFO *pInfo);
//ɾ��Group
BSSCLIENT_API BOOL  ST_BSS_DeleteGroup(long lClient, char* pGroupID);
//ɾ��Tour
BSSCLIENT_API BOOL  ST_BSS_DeleteTour(long lClient, char* pTourID);
//Ⱥ�顢Ѳ������״̬��ѯ //1 Ѳ�أ�2 Ⱥ��, 1-�����޸ģ���ʶ��������״̬�� 0-���У�2-�Ҳ���csg
BSSCLIENT_API int  ST_BSS_QueryRunStatus(long lClient, int nType, char *pID);

BSSCLIENT_API BOOL ST_BSS_QueryDomainList(long lClient, DOMAINLIST& listDomain);
BSSCLIENT_API int ST_BSS_AddDomain(long lClient, const DOMAININFO *pDomainInfo);
BSSCLIENT_API int ST_BSS_ModifyDomain(long lClient, const DOMAININFO *pDomainInfo);
BSSCLIENT_API BOOL ST_BSS_DeleteDomain(long lClient, const char *pDomainID);


//�µ�Ⱥ��API
BSSCLIENT_API int ST_BSS_AMDGroup(long lClient, GROUP_INFO *pGroupInfo, BOOL bDel = FALSE);
BSSCLIENT_API int ST_BSS_AMDGroupStep(long lClient, GROUP_INFO *pGroupInfo, GROUP_STEP *pGroupStep, BOOL bDel = FALSE);
BSSCLIENT_API int ST_BSS_QuerGroupOneStep(long lClient, GROUP_STEP *pGroupStep);

BSSCLIENT_API int ST_BSS_ModifyPUArea(long lClient, PUIDINFO *pPuidInfo, AREAINFO *pAreaInfo);

#define R_OK					0
#define R_INVALID_PARAM			0x80000001
#define R_SEND_ERROR			0x80000002
#define R_RECV_ERROR			0x80000003		
#define R_CREATE_XML_ERROR		0x80000004
#define R_INVALID_RSPXML		0x80000005
#define R_XML_EXCEPTION			0x80000006
#define R_OP_FAIL				0x80000007
#define R_ID_EXIST				0x80000008
#define R_NAME_EXIST			0x80000009
#define R_OTHER_EXIST			0x8000000a
//PU��GU������Ϣ
typedef struct __INFOITEM
{
	string strInfoItem;
}INFOITEM;

typedef struct __EXTRAINFO
{
	string strInfoItem;
	string strInfoText;
}EXTRAINFO;
enum { TYPE_PU, TYPE_GU };
BSSCLIENT_API int ST_BSS_QueryInfoItemList(long lClient, vector<INFOITEM>& InfoItemList, int type);
BSSCLIENT_API int ST_BSS_AddInfoItem(long lClient, const INFOITEM *pInfoItem, int type);
BSSCLIENT_API int ST_BSS_DelInfoItem(long lClient, const INFOITEM *pInfoItem, int type);


BSSCLIENT_API int ST_BSS_AddExtraInfo(long lClient, const char *pID, const vector<EXTRAINFO>& InfoList, int type);
BSSCLIENT_API int ST_BSS_QueryExtraInfo(long lClient, const char *pID, vector<EXTRAINFO>& InfoList, int type);

//�Ž�ϵͳ
struct __DoorInfo;
struct __DoorAreaInfo;
struct __DoorSysInfo;
struct __DoorServerInfo;

typedef struct __DoorRelationGU //�����GU
{
	string strGUID;
	string strGUName;
	bool operator==(const string &str) const
	{
		return strGUID == str;
	}
}DoorRelationGU, *PDoorRelationGU;

typedef struct __DoorInfo // ����Ϣ
{
	string strDoorID;
	string strDoorName; //32
	
	long lDoorIndex; //�ŵ�ַ���
	
	list<DoorRelationGU> DoorRelationGUList;
	
	string strDoorServerID;
	
	struct __DoorSysInfo *pDoorSysInfo;
	struct __DoorAreaInfo *pDoorAreaInfo;

	bool operator== (const string &str) const
	{
		return strDoorID == str;
	}
}DoorInfo, *PDoorInfo;


// #define ID_DEFAULT -1
// enum enumAccessMode { AM_485 = 0, AM_IP = 1, AM_DEFAULT = AM_485 };
// enum enumDoorServerType { DST_DONE = 1, DST_DEFAULT = DST_DONE };
// enum enumDoorServerSubType { DSST_DOOR = 1, DSST_DEFAULT = DSST_DOOR };
// enum enumVerify { VERIFY_NONE = 0, VERIFY_ODD = 1, VERIFY_EVEN = 2, VERIFY_DEFAULT = VERIFY_NONE };
typedef struct __DoorServerInfo //�Ž���������Ϣ
{
	__DoorServerInfo() {}
	__DoorServerInfo(const string& strDSID) : strDoorServerID(strDSID) {}

	string strDoorServerID;
	string strDoorServerName; //32

	long lAccessMode; // �Ž����������ʷ�ʽ��0��485����ģʽ��1��IP����ģʽ
	string strDoorServerAddr; //32
	long lPort;
	long lDoorServerType; //������ϵͳ���� 1��DONE���̵��Ž�ϵͳ
	long lSubType; //1:�Ž���������2�����ݿ�����

	//����485����ģʽ����Ч
	long lBaud;  //������
	long lDatabit; //����λ
	long lStopbit; //ֹͣλ
	long lVerify;
	
	struct __DoorSysInfo *pDoorSysInfo;

	bool operator<(const struct __DoorServerInfo& dsi) const
	{
		return strDoorServerID < dsi.strDoorServerID;
	}
	bool operator==(const string &str) const
	{
		return strDoorServerID == str;
	}
}DoorServerInfo, *PDoorServerInfo;


typedef struct __DoorAreaInfo // ������Ϣ�����⣩
{
	string strDoorAreaID;
	string strDoorAreaName;

	list<DoorInfo> DoorList;
	list<struct __DoorAreaInfo> *pDoorAreaList;

	struct __DoorSysInfo *pDoorSysInfo;
	struct __DoorAreaInfo *pUpDoorAreaInfo;

	~__DoorAreaInfo()
	{
		if (pDoorAreaList != NULL)
			delete pDoorAreaList;
	}
	bool operator==(const string &str) const
	{
		return strDoorAreaID == str;
	}
}DoorAreaInfo, *PDoorAreaInfo;


typedef struct __DoorSysInfo // �Ž�ϵͳ��Ϣ
{
	
	string strDoorSysID;
	string strDoorSysName;
	string strDoorSysPUID; //6λ����룫4λ���̴��룫18λ����
	long lSysMode; // 0-ϵͳ������ģʽ��1��������ֱ�ӷ���ģʽ
	long lHeartFreq;

	list<DoorInfo> DoorList;
	list<DoorAreaInfo> DoorAreaList;

	list<DoorServerInfo> DoorServerList;
	bool operator== (const string &str) const
	{
		return strDoorSysID == str;
	}
}DoorSysInfo, *PDoorSysInfo;


typedef struct __UserDoorRight //�û��Ž�Ȩ��
{
	string strDoorID;
	string strDoorName;
	long lDoorRight;

	bool operator<(const struct __UserDoorRight& udr) const
	{
		return strDoorID < udr.strDoorID;
	}
}UserDoorRight, *PUserDoorRight;

struct __CardInfo;
typedef struct __CardPerson //�ֿ���
{
	__CardPerson() {}
	__CardPerson(const string& strNID) : strNameID(strNID) {}

	string strNameID;
	string strName;
	string strPhotoID;

	bool operator<(const struct __CardPerson& cp) const
	{
		return strNameID < cp.strNameID;
	}

	bool operator== (const string &str) const
	{
		return strNameID == str;
	}
}CardPerson, *PCardPerson;

typedef struct __CardInfo // �ſ���Ϣ
{
	string strCardID;
	string strNameID;
	bool operator== (const string &str) const
	{
		return strCardID == str;
	}
}CardInfo, *PCardInfo;

template<class T1> class CmpFunctor
{
public:
	CmpFunctor(const string &str):m_str(str)
	{
	}

	bool operator()(const T1& p)
	{
		return p == m_str;
	}
private:
	string m_str;
};

enum enumOperatorType
{
	OT_ADD,	OT_MODIFY, OT_DEL
};

BSSCLIENT_API int ST_BSS_AMDDoorSysInfo(long lClient, PDoorSysInfo pDoorSysInfo, enumOperatorType ot);
BSSCLIENT_API int ST_BSS_AMDDoorAreaInfo(long lClient, PDoorAreaInfo pDoorAreaInfo, enumOperatorType ot);
BSSCLIENT_API int ST_BSS_AMDDoorServerInfo(long lClient, PDoorServerInfo pDoorServerInfo, enumOperatorType ot);
BSSCLIENT_API int ST_BSS_AMDDoorInfo(long lClient, PDoorInfo pDoorInfo, enumOperatorType ot);
BSSCLIENT_API int ST_BSS_AMDCardPerson(long lClient, PCardPerson pCardPerson, enumOperatorType ot);
BSSCLIENT_API int ST_BSS_AMDCardInfo(long lClient, PCardInfo pCardInfo, enumOperatorType ot);
BSSCLIENT_API int ST_BSS_AddDoorUserSecurity(long lClient, const char *pUser, const list<UserDoorRight>& DoorRightList);
BSSCLIENT_API int ST_BSS_AddDoorRelation(long lClient, PDoorInfo pDoorInfo, const list<DoorRelationGU>& DoorRelationGUList);

BSSCLIENT_API int ST_BSS_QueryDoorSysList(long lClient, list<DoorSysInfo>& DoorSysList);
BSSCLIENT_API int ST_BSS_QueryDoorServerList(long lClient, PDoorSysInfo pDoorSysInfo);
BSSCLIENT_API int ST_BSS_QuerySysADList(long lClient, PDoorSysInfo pDoorSysInfo);
BSSCLIENT_API int ST_BSS_QueryAreaADList(long lClient, PDoorAreaInfo pDoorAreaInfo);
BSSCLIENT_API int ST_BSS_QueryCardPersonList(long lClient, list<CardPerson>& CardPersonList);
BSSCLIENT_API int ST_BSS_QueryCardList(long lClient, list<CardInfo>& CardList);
BSSCLIENT_API int ST_BSS_QueryDoorUserSecurity(long lClient, const char *pUser, list<UserDoorRight>& DoorRightList);
BSSCLIENT_API int ST_BSS_QueryDoorRelation(long lClient, PDoorInfo pDoorInfo);

BSSCLIENT_API int ST_BSS_AddNVSAlarmCaseInfo(long lClient, char *add_buf, char *recv_buf);
BSSCLIENT_API int ST_BSS_QueryNVSAlarmCaseInfo(long lClient, const char *svr_id, const char *domian_id, char *recv_buf);
BSSCLIENT_API int ST_BSS_DeleteNVSAlarmCaseInfo(long lClient, const char *svr_id, const char* domain_id);

//�Ž��澯����
BSSCLIENT_API int ST_BSS_AddDoorAlarmRelation(long lClient, char *add_buf, char *recv_buf);
BSSCLIENT_API int ST_BSS_QueryDoorAlarmRelation(long lClient, const char *door_id, const char* domain_id, char *recv_buf);
BSSCLIENT_API int ST_BSS_DeleteAlarmDoorRelation(long lClient, const char *door_id, const char* domain_id);

//��ѯ�ӷ���ICON
BSSCLIENT_API BOOL ST_BSS_QuerySubDefeIcon(long lClient, char* pDefeID, char* buffer, int *len, BOOL *bEnd);

//------- add by wy 2010.06.17 -------//
//�������ѯ
BSSCLIENT_API int ST_BSS_QueryEventCodeDef(long lClient, const char *evtCode, char *buffer);	
//�����Ч�����¼�
BSSCLIENT_API BOOL ST_BSS_AddEventFilter(long lClient, const char *evtCode, const char *GUID, char *buffer);
//ɾ����Ч�����¼�����
BSSCLIENT_API BOOL ST_BSS_DeleteEventFilter(long lClient, const char *evtCode, const char *GUID, char *buffer);
//��ѯ��Ч�����¼�
BSSCLIENT_API BOOL ST_BSS_QueryEventFilter(long lClient, const char *GUID, char *buffer);
//��ѯ����汾
BSSCLIENT_API BOOL ST_BSS_QueryServiceVersion(long lClient, const char *username, char *buffer);
//--------------- add end -----------//

#endif
