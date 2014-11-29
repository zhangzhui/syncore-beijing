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
	BOOL    bDomain;            //TRUE为域结构，FALSE为机构
	char    DomainName[32];      //域名
	char    DomainID[32];        //域ID
	char    UpDomainID[32];      //上级域ID
	char    DomainIP[16];        //域IP地址
	char    CSGIP[32];          //CSG IP    
	char    Remark[128];        //备注
	
	char    AreaName[32];       //机构名
	char    AreaID[32];         //机构ID
	char    UpAreaID[32];       //上级机构ID
	char    UpAreaName[32];     //上级机构名称
}_AREAINFO;

//管理员机构
typedef struct	ADMININFO		
{
	char	AdminCount[32];		//帐号名称；
	char	AdminPWD[32];		//帐号密码；
	char    DomainID[32];       //域ID；
	char    DomainName[32];     //DoaminName;
	char	AreaID[32];			//机构ID；
	char    AreaName[32];       //机构名称
	BOOL    bLevel;             //超级管理员1,非为0；
}_ADMININFO;
//客户结构
typedef struct	CLIENTINFO		
{
	char	ClientID[32];    	//客户ID
	char    DomainID[32];		//隶属域domainID
	char    DomainName[32];
	char    AreaID[32];			//隶属机构ID
	char    AreaName[64];
	char    Certificate[32];    //身份证号码
	char    Birth[32];          //生日
	BOOL    bSex;				//性别
	BOOL    bMarriage;          //婚姻状况
	char    Education[32];      //学历
	char    School[32];         //毕业院校
	char    workDepartment[32]; //工作单位
	
}_CLIENTINFO;
//用户结构
typedef struct USERINFO{
	char    User[32];         //用户ID
	char    Password[32];     //用户密码
	char    ClientID[32];     //隶属客户ID  
	BOOL    bCheckActive;     //激活状态
	char   	DayName[32];      //激活日期
	long    Cyc;              //激活周期
	long    nLoginMode;       //登录模式  1、共享式（默认模式），2、抢占式，3、独占式
	int		nNum;			  //共享数
//add by wy 2010.01.08
	BOOL    m_bSupperUsr;
//add end
}_USERINFO;

//权限结构
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
	long	lDomeRight; //云台控制权限：0无，1、2、3有。默认1
}_SECURITYINFO;

//测控传感器结构  2014-08-19 by hhs
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

//设备结构
typedef struct  PUIDINFO{
	char    PUName[32];			//设备名
	char    PUID[32];			//设备PUID
	char    PUIP[32];			//PUIP
	long    Active;				//启用状态：0-已停止，未被授权，不可被访问；1-启用，已经被授权接入系统
	char    DomainName[32];		//域名
	char    DomainID[32];		//所属域ID
	char    AreaName[32];  //机构名称
	char    AreaID[32];    //隶属机构ID
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
//设备业务
typedef struct GUIDINFO{
	char     GuidName[32];      //业务名
	char     GUID[32];          //业务GUID
	long     GuidType;          //业务类型：1-音视频，2-报警输入，3-报警输出, 4-解码器,5-显示通道, 6-音视频(从)
	char     PUID[32];          //所属设备PUID
	char     DomainID[32];		//所属域ID
	char     WndModeID[32];             //分屏模式（显示通道）
	char	 Description[1024];
	char	 AlarmText[512];
	char     MSUID0[32];        //第一个MSUID
	char     MSUNAME0[32];      //第一个MSUNAME
	char     MSUID1[32];        //第二个MSUID
	char     MSUNAME1[32];      //第二个MSUNAME
	char     MSUID2[32];        //第三个MSUID
	char     MSUNAME2[32];      //第三个MSUNAME
	char     szAlarmDevDefID[32]; //报警主机防区ID add by wy 2010.06.18
//	ck_dev_param_t ck_dev_param;
// 	char	 use_flag1;          //第一个传感器  //Add on 2014-08-27 by hhs
// 	char	 ck_type1;
// 	char	 ck_name1[32];
// 	char    alarm_up_val1[16];
// 	char    alarm_down_val1[16];
// 	
// 	char	 use_flag2;          //第二个传感器
// 	char	 ck_type2;
// 	char	 ck_name2[32];
// 	char    alarm_up_val2[16];
// 	char    alarm_down_val2[16];
// 	
// 	char	 use_flag3;          //第三个传感器
// 	char	 ck_type3;
// 	char	 ck_name3[32];
// 	char    alarm_up_val3[16];
// 	char    alarm_down_val3[16];
// 	
// 	char	 use_flag4;          //第四个传感器
// 	char	 ck_type4;
// 	char	 ck_name4[32];
// 	char    alarm_up_val4[16];
// 	char    alarm_down_val4[16];
// 	
// 	char	 use_flag5;          //第五个传感器
// 	char	 ck_type5;
// 	char	 ck_name5[32];
// 	char    alarm_up_val5[16];
// 	char    alarm_down_val5[16];
// 	
// 	char	 use_flag6;          //第六个传感器
// 	char	 ck_type6;
// 	char	 ck_name6[32];
// 	char    alarm_up_val6[16];
// 	char    alarm_down_val6[16];
// 	
// 	char	 use_flag7;          //第七个传感器
// 	char	 ck_type7;
// 	char	 ck_name7[32];
// 	char    alarm_up_val7[16];
// 	char    alarm_down_val7[16];
// 	
// 	char	 use_flag8;          //第八个传感器
// 	char	 ck_type8;
// 	char	 ck_name8[32];
// 	char    alarm_up_val8[16];
// 	char    alarm_down_val8[16];


}_GUIDINFO;

//转发服务器信息结构
typedef struct MDUINFO  {
	char    MduName[32];	        //转发服务器名
	char    MduID[32];		    //转发ID
	char    DomainID[32];		//隶属域ID
	long    nPort;              //端口
	long    HeartFreq;          //心跳周期
	long    iClientNum;		//当前客户数
	long	iVideoNum;	//当前设备数
	
	BOOL m_bSaveState;
	int  m_nSaveIntv;
}_MDUINFO;
//存储服务器表
typedef struct MSUINFO {
	char	MsuName[32];	//存储服务器名
	char    MsuID[32];		//存储服务器ID
	char    DomainID[32];   //DomainID
	long    nPort;          //端口
	long    HeartFreq;      //心跳周期
	long    iVideoNum;	//最大录像视频数
	long    iMaxVodClient; //最大点播视频数

	BOOL m_bSaveState;
	int  m_nSaveIntv;
}_MSUINFO;
//转发路由信息结构
typedef struct MDUROUTEINFO  {
	char    MduID[32];		    //转发ID
	char    MduIP[64];		    //转发IP
	char    CmuIP[64];          //CMU IP
}_MDUROUTEINFO;

//存储路由信息结构
typedef struct MSUROUTEINFO  {
	char    MsuID[32];		    //存储ID
	char    MsuIP[64];		    //存储IP
	char    CmuIP[64];          //CMU IP
}_MSUROUTEINFO;

typedef struct TVINFO {
	char    name[64];           //名称
	char    ip[16];             //IP
	long    lX;                 //分辨率x
	long    lY;                 //分辨率y
}_TVINFO;
//REOCRDPLAN
typedef struct RECOPLAN {
	char	GuidName[32];       //业务名称
	char	MsuID[32];
	long	recordType;        //定时、特殊日、
	char	startTime[32];     //开始时间
	char	endTime[32];       //结束时间
	long	recordTime;        //报警录像时长
	long	preRecordTime;     //预录时间
	
}_RECOPLAN;
//DEFENCE
typedef struct DEFEINFO{
	char	DefeID[32];          //防区ID
	char 	DefeName[32];        //防区名称 
    char   DomainID[32];         //域ID
	char	AreaID[32];          //机构ID
	char	MapID[32];           
	char    MapName[32];    	//地图ID名称
	BOOL	bState;              //设防状态
   	//SetParam
}_DEFEINFO;
//DEFEPARA
typedef struct DEFEELEM{
    char	DefeID[32];          //防区ID
	char	GUID[32];            //GUID
	long	nType;               //监控点类型。0-视频, 1-报警输入, 2-报警输出, 解码器
	char	MapID[32];        //防区名称 
	long	xPos;                //监控点在防区地图上的X坐标
	long	yPos;                //监控点在防区地图上的Y坐标
	BOOL	bBypass;              //旁路状态。0-已旁路，1-清旁路
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

//设置巡回
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
//设置群组
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
//新的群组结构----------------------------------begin
struct GROUP_WND{ //群组步内（电视墙）的一个监视器中的一个窗口信息
	string strEncGuid;
	string strEncName;
};

typedef vector<GROUP_WND> GROUP_WNDLIST;
typedef vector<RECT> GROUP_RECTLIST;
struct GROUP_MONITOR{ //群组步内（电视墙）的一个监视器信息
	GROUP_MONITOR() : pWndMode(NULL), bExclude(FALSE) {}
	string strWndModeID;
	GROUP_WNDLIST wnd_list;

	BOOL bExclude;
	TWCONFIG_INFO *pWndMode;
	GROUP_RECTLIST rcWnd_list;
};

typedef vector<GROUP_MONITOR> GROUP_MONITORLIST;
struct GROUP_STEP{ //群组步
	GROUP_STEP() : iStepID(0) {}
	int iStepID;
	int iStepLen;
	GROUP_MONITORLIST monitor_list;

	GROUP_RECTLIST rcMonitor_list;
};
struct GROUP_INFO{ //群组
	string strDomainID;
	string strAreaID;
	string strGroupID;
	string strGroupName;
	int iGroupNO;
	
	string strTVWallID;
	string strTVWallName;
	int iMonitorCount; //添加群组时的电视墙监视器个数，以做后面判断电视墙是否结构更改的依据

	auto_ptr<TWCONFIG_INFO> pTVWallInfo;

	list<GROUP_STEP> step_list;
};
//------------------------------新的群组结构end
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
	string strType;   //0：本域		1：子域			2：父域
	BOOL m_bSaveState;
	int m_nSaveIntv;
}DOMAININFO;
typedef vector<DOMAININFO> DOMAINLIST;



BSSCLIENT_API extern DOMAINLIST g_listDomain;

//
BSSCLIENT_API long	ST_BSS_Login(const char* ip, int* port, const char* user, const char* pwd, char* buffer);

BSSCLIENT_API BOOL ST_BSS_Logout(long lClient);
//AreaInfo;//bFlag 为真添加域信息，为假则添加机构信息, buffer 为添加成功后返回的buffer)
BSSCLIENT_API int ST_BSS_AddAreaInfo(long lClient, BOOL bFlag, AREAINFO* pAreaInfo);
//bFlag 为真添加域信息，为假则添加机构信息, buffer 为添加成功后返回的buffer)
BSSCLIENT_API BOOL ST_BSS_DeleAreaInfo(long lClient, BOOL bFlag, char* pAreaID, const char* User, char* buffer);

BSSCLIENT_API BOOL ST_BSS_PropAreaInfo(long lClient, BOOL bFlag, AREAINFO* pAreaInfo, char* buffer);
//bFlag 为真查询域信息，为假查询机构信息，返回值存在buffer中
BSSCLIENT_API BOOL  ST_BSS_QuerAreaInfo(long lClient, BOOL bSign, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL *bEnd);
BSSCLIENT_API BOOL  ST_BSS_QuerNextAreaInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd );

//AdminInfo;
BSSCLIENT_API int	ST_BSS_AddAdminInfo(long lClient, ADMININFO* pAdminInfo);
//pDelAdmin 要删除的用户，pAdmin 登录的用户
BSSCLIENT_API BOOL  ST_BSS_DeleAdminInfo(long lClient, char* pDelAdmin, char* pAdmin, char* pDomainID, char* AreaID);

BSSCLIENT_API int  ST_BSS_PropAdminInfo(long lClient, ADMININFO* pAdminInfo);
//查询管理员
BSSCLIENT_API BOOL  ST_BSS_QuerAdminInfo(long lClient, char* pDomainID, char *pAreaID, char* pUser, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_QuerNextAdminInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd);

//PUID
BSSCLIENT_API BOOL	ST_BSS_AddPuidInfo(long lClient, PUIDINFO* pPuidInfo, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_DelePuidInfo(long lClient, const char* pPuid, const char *pDomainID, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_PropPuidInfo(long lClient, PUIDINFO* pPuidInfo, char* buffer);

BSSCLIENT_API BOOL  ST_BSS_QuerPuidInfo(long lClient, char* pDomainID, char* pAreaID, PUIDINFO *pPuidNode, BOOL bSign, int *pCount);

BSSCLIENT_API BOOL  ST_BSS_QuerNextPuidInfo(long lClient, char* pDomainID, char* buffer, int* len, BOOL *bEnd);

//Add GUID, 当添加为解码器类型的GUID时，pGuidCode就是编码器类型的，否则为NULL
BSSCLIENT_API int ST_BSS_AddGuidInfo(long lClient, GUIDINFO* pGuidInfo, int& num);
BSSCLIENT_API BOOL ST_BSS_DeleGuidInfo(long lClient, char* pGuId, const char *pDomainID);
BSSCLIENT_API int ST_BSS_PropGuidInfo(long lClient, GUIDINFO* pGuidInfo, int& num);
//查询一个域下面的GUID
BSSCLIENT_API BOOL  ST_BSS_QuerGuidInfo(long lClient, char* pDomainID, char* pAreaID, GUIDINFO *pGuidNode, BOOL bSign, int *pCount);
BSSCLIENT_API BOOL  ST_BSS_QuerNextGuidInfo(long lClient, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL *bEnd);

//RecoPlan
BSSCLIENT_API BOOL	ST_BSS_AddRecordPlan(long lClient, char* addBuf, char* recvBuf);
BSSCLIENT_API BOOL	ST_BSS_AddRecPlanGuidList(long lClient, char* addBuf, char* recvBuf);
BSSCLIENT_API BOOL  ST_BSS_DeleRecordPlan(long lClient, char* pGuid, char* buffer);
BSSCLIENT_API BOOL  ST_BSS_PropRecordPlan(long lClient, RECOPLAN* pRecoPlan, char* buffer);
//单个查询guid的录像策略
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
//Route 添加路由信息1-mdu路由，2-msu路由
BSSCLIENT_API int	ST_BSS_AddRouteInfo(long lClient, int nType, char *pID, char *pIP, char *pCmuIP);
//Route 删除路由信息1-mdu路由，2-msu路由
BSSCLIENT_API BOOL	ST_BSS_DeleRouteInfo(long lClient, int nType, char *pID, char *pIP, char *pCmuIP);
//Route 查询路由信息1-mdu路由，2-msu路由
BSSCLIENT_API BOOL	ST_BSS_QuerRouteInfo(long lClient, int nType, char *pID, char* buffer);
//Route 修改路由信息1-mdu路由，2-msu路由
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
//用户权限User=%s&GUID=%s&DomeRight=%s&EnConfig=%s&EnTalk=%s&EnBackPlay=%s
BSSCLIENT_API BOOL ST_BSS_AddUserSecurity(long lClient, char* buffer, char* outBuf);
BSSCLIENT_API BOOL ST_BSS_AddSecuInfosToSmu(long lClient, int nType, char* buffer, char* outBuf);
BSSCLIENT_API BOOL ST_BSS_DeleUserSecurity(long lClient, char* pUserID, char* pGuid, char* buffer);
BSSCLIENT_API BOOL ST_BSS_PropUserSecurity(long lClient, char* buffer, char* outBuf);
BSSCLIENT_API BOOL ST_BSS_QuerUserSecurityOneArea(long lClient, char* pUserID, char* pAreaID, char* pDomainID, char* buffer);	
//权限查询
BSSCLIENT_API BOOL ST_BSS_QuerUserSecuInfos(long lClient, int nType, char* pUserID, char* pAreaID, char* pDomainID, char* buffer);	
//用户的GUID到BUFF，bSecurity 为TRUE即是有GUID，为FALSE就没有GUID
// bFirst 为TRUE即是满90个第一轮添加，为FALSE就不是第一轮
// bHead  为TRUE即是第一批90，为FALS就不是第一批90
BSSCLIENT_API char* ST_BSS_AddGuidToIni(long lClient, char* pAddBuf, SECURITYINFO *pSecurityInfo, BOOL bSecurity, BOOL bFirst, BOOL bHead);
//0-defen, 1-tvwall, 2-tour, 3-group
BSSCLIENT_API BOOL ST_BSS_AddSecuInfosToIni(long lClient, int nType, char* pAddBuf, SECURITYINFO *pSecurityInfo, BOOL bSecurity, BOOL bFirst, BOOL bHead);
//
//心跳函数
BSSCLIENT_API BOOL ST_BSS_KeepAlive(long lClient);
BSSCLIENT_API BOOL ST_BSS_AddDefeInfo(long lClient, char *addBuf, char* buffer);
BSSCLIENT_API BOOL ST_BSS_DeleDefeInfo(long lClient, char* pDefeID, char* buffer);
BSSCLIENT_API BOOL ST_BSS_PropOneDefeInfo(long lClient, char *addBuf, char* buffer);
BSSCLIENT_API BOOL ST_BSS_QuerAreaDefeInfos(long lClient, char* pDomainID, char* pAreaID, char* buffer, int* len, BOOL* bEnd);//查询某个机构下所有防区的信息
BSSCLIENT_API BOOL ST_BSS_QuerOneDefeInfo(long lClient, char* pDefeID, char* buffer, int* len, BOOL* bEnd);//查询某个防区的信息
//为防区添加一个图元
BSSCLIENT_API BOOL ST_BSS_AddDefeGuid(long lClient, char* addBuf, char* buffer);
BSSCLIENT_API BOOL ST_BSS_DeleDefeGuid(long lClient, char* pDefeID, char* pGuid,  const char *pDomainID, char* buffer);
BSSCLIENT_API BOOL ST_BSS_PropDefeGuid(long lClient, char* pDefeID, char* pGuid, const char *pDomainID, int xPos, int yPos, char* buffer);
BSSCLIENT_API BOOL ST_BSS_QuerDefeGuid(long lClient, char* pDefeID, char* buffer, int *len, BOOL *bEnd);
//iType = 0-请求防区信息(添加防区时，pDefeNameNew = "NULL", 修改防区用到pDefeNameNew)；2-联动配置
BSSCLIENT_API BOOL ST_BSS_RequstDefe(long lClient, int iType, char* pDefeName, char* pDomainID, char* pAreaID, char* pDefeNameNew, char* buffer); 
BSSCLIENT_API BOOL ST_BSS_ReceiveRequ(long lClient); //接收SMU的添加防区信息的请求(TRUE-收到，FALSE-没收到)
//请求防区的GUID, iTypt=0添加，iType=1修改
BSSCLIENT_API BOOL ST_BSS_RequDefeGuid(long lClient, int iType, char* pDefeID, char* pGuid, const char *pDomainID, char* buffer); 
//iType 0(音视频)、1(预置位)
BSSCLIENT_API BOOL ST_BSS_RequLnk(long lClient, int iType, char* pDefeID, char* pGuid, const char *pDomainID, char* buffer);
//添加联动
BSSCLIENT_API BOOL ST_BSS_AddLnkInfo(long lClient, char* addBuf, char* buffer);
//查询联动
BSSCLIENT_API BOOL ST_BSS_QuerLnkInfo(long lClient, char* pDefeID, char* pGuid, const char *pDomainID, char* buffer, int *len, BOOL *bEnd);
//查询所有的防区名称和ID
BSSCLIENT_API BOOL ST_BSS_QuerAllMaps(long lClient, char* buffer);
//添加联动的策略
BSSCLIENT_API BOOL	ST_BSS_AddLnkAllInfo(long lClient, char* addBuf, char* recvBuf);
//查询联动策略
BSSCLIENT_API BOOL ST_BSS_QuerLnkAllInfo(long lClient, char* pGuId, char* EvtCode, const char *pDomainID, char* buffer, int* len, BOOL *bEnd);
//请求TvwallID
BSSCLIENT_API int ST_BSS_GetTvwallID(long lClient, char *pDomainID, char *pAreaID, char *pTvwallName, UINT uSwitchNo, char *pTvwallID);
//请求TourID
BSSCLIENT_API int  ST_BSS_GetTourID(long lClient, char *pDomainID, char *pAreaID, char *pTourName, int nTourNo, BOOL bAutoJump, char *pTourID);
//请求GroupID
BSSCLIENT_API int  ST_BSS_GetGroupID(long lClient, char *pDomainID, char *pAreaID, char *pGroupName, int nGroupNo, char *pGroupID);
//添加电视墙的基本信息
BSSCLIENT_API int  ST_BSS_AddTvwallBase(long lClient, TWCONFIG_INFO *pTvwallInfo);
//添加电视墙的详细信息
BSSCLIENT_API BOOL  ST_BSS_AddTvwallInfos(long lClient, TWCONFIG_INFO *pTvwallInfo);
//添加巡回基本信息 
BSSCLIENT_API BOOL  ST_BSS_AddTourBase(long lClient, TOURCONFIG_INFO *pTourInfo);
//添加巡回详细信息 
BSSCLIENT_API BOOL  ST_BSS_AddTourInfos(long lClient, TOURCONFIG_INFO *pTourInfo);
//添加群组基本信息AreaID=%s&DomainID=%s&GroupID=%s&Name=%s&GroupNo=%d",
BSSCLIENT_API int  ST_BSS_AddGroupBase(long lClient, GROUPCONFIG_INFO *pGroupInfo);
//添加群组详细信息
BSSCLIENT_API BOOL  ST_BSS_AddGroupInfos(long lClient, GROUPCONFIG_INFO *pGroupInfo);
//编辑电视墙的基本信息
BSSCLIENT_API int  ST_BSS_PropTvwallBase(long lClient, TWCONFIG_INFO *pTvwallInfo);
//编辑巡回基本信息
BSSCLIENT_API int  ST_BSS_PropTourBase(long lClient, TOURCONFIG_INFO *pTourInfo);
//编辑群组基本信息
BSSCLIENT_API int  ST_BSS_PropGroupBase(long lClient, GROUPCONFIG_INFO *pGroupInfo);

//编辑电视墙的详细信息
BSSCLIENT_API int ST_BSS_PropTvwallCont(long lClient, TWCONFIG_INFO *pTvwallInfo);
//编辑巡回详细信息
BSSCLIENT_API int  ST_BSS_PropTourCont(long lClient, char *pTourID);
//编辑群组详细信息
BSSCLIENT_API int  ST_BSS_PropGroupCont(long lClient, char *pGroupID);
//查询一个机构下的所有电视墙(基本信息)
BSSCLIENT_API BOOL  ST_BSS_QuerOneAreaTvwallInfos(long lClient, char *pDomainID, char *pAreaID, char *buffer);
//查询电视墙信息
BSSCLIENT_API BOOL ST_BSS_QuerOneTvwallInfos(long lClient, const char* pTvwallID, TWCONFIG_INFO *pTvwallInfo);
//查询一个巡回的具体信息
BSSCLIENT_API BOOL  ST_BSS_QuerOneTourInfos(long lClient, char* pTourID, TOURCONFIG_INFO *pTourInfo);
//查询一个群组的具体信息
BSSCLIENT_API BOOL  ST_BSS_QuerOneGroupInfos(long lClient, GROUP_INFO *pGroupInfo);
//Query Tour 2008-11-04//查询一个机构下所有巡回(基本信息)
BSSCLIENT_API BOOL  ST_BSS_QuerOneAreaTourInfos(long lClient, char* pDomainID, char* pAreaID, char* buffer);
//Query Group 2008-11-04//查询一个机构下所有群组(基本信息)
BSSCLIENT_API BOOL  ST_BSS_QuerOneAreaGroupInfos(long lClient, char* pDomainID, char* pAreaID, char* buffer);
//删除Tvwall
BSSCLIENT_API BOOL ST_BSS_DeleteTvwall(long lClient, TWCONFIG_INFO *pInfo);
//删除Group
BSSCLIENT_API BOOL  ST_BSS_DeleteGroup(long lClient, char* pGroupID);
//删除Tour
BSSCLIENT_API BOOL  ST_BSS_DeleteTour(long lClient, char* pTourID);
//群组、巡回运行状态查询 //1 巡回，2 群组, 1-可以修改，标识不在运行状态， 0-运行，2-找不到csg
BSSCLIENT_API int  ST_BSS_QueryRunStatus(long lClient, int nType, char *pID);

BSSCLIENT_API BOOL ST_BSS_QueryDomainList(long lClient, DOMAINLIST& listDomain);
BSSCLIENT_API int ST_BSS_AddDomain(long lClient, const DOMAININFO *pDomainInfo);
BSSCLIENT_API int ST_BSS_ModifyDomain(long lClient, const DOMAININFO *pDomainInfo);
BSSCLIENT_API BOOL ST_BSS_DeleteDomain(long lClient, const char *pDomainID);


//新的群组API
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
//PU、GU附加信息
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

//门禁系统
struct __DoorInfo;
struct __DoorAreaInfo;
struct __DoorSysInfo;
struct __DoorServerInfo;

typedef struct __DoorRelationGU //门相关GU
{
	string strGUID;
	string strGUName;
	bool operator==(const string &str) const
	{
		return strGUID == str;
	}
}DoorRelationGU, *PDoorRelationGU;

typedef struct __DoorInfo // 门信息
{
	string strDoorID;
	string strDoorName; //32
	
	long lDoorIndex; //门地址序号
	
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
typedef struct __DoorServerInfo //门禁控制器信息
{
	__DoorServerInfo() {}
	__DoorServerInfo(const string& strDSID) : strDoorServerID(strDSID) {}

	string strDoorServerID;
	string strDoorServerName; //32

	long lAccessMode; // 门禁控制器访问方式：0－485串口模式，1－IP网络模式
	string strDoorServerAddr; //32
	long lPort;
	long lDoorServerType; //控制器系统类型 1：DONE厂商的门禁系统
	long lSubType; //1:门禁控制器，2：电梯控制器

	//以下485串口模式下有效
	long lBaud;  //波特率
	long lDatabit; //数据位
	long lStopbit; //停止位
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


typedef struct __DoorAreaInfo // 门区信息（虚拟）
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


typedef struct __DoorSysInfo // 门禁系统信息
{
	
	string strDoorSysID;
	string strDoorSysName;
	string strDoorSysPUID; //6位域代码＋4位厂商代码＋18位其它
	long lSysMode; // 0-系统服务器模式，1－控制器直接访问模式
	long lHeartFreq;

	list<DoorInfo> DoorList;
	list<DoorAreaInfo> DoorAreaList;

	list<DoorServerInfo> DoorServerList;
	bool operator== (const string &str) const
	{
		return strDoorSysID == str;
	}
}DoorSysInfo, *PDoorSysInfo;


typedef struct __UserDoorRight //用户门禁权限
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
typedef struct __CardPerson //持卡人
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

typedef struct __CardInfo // 门卡信息
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

//门禁告警联动
BSSCLIENT_API int ST_BSS_AddDoorAlarmRelation(long lClient, char *add_buf, char *recv_buf);
BSSCLIENT_API int ST_BSS_QueryDoorAlarmRelation(long lClient, const char *door_id, const char* domain_id, char *recv_buf);
BSSCLIENT_API int ST_BSS_DeleteAlarmDoorRelation(long lClient, const char *door_id, const char* domain_id);

//查询子防区ICON
BSSCLIENT_API BOOL ST_BSS_QuerySubDefeIcon(long lClient, char* pDefeID, char* buffer, int *len, BOOL *bEnd);

//------- add by wy 2010.06.17 -------//
//报警码查询
BSSCLIENT_API int ST_BSS_QueryEventCodeDef(long lClient, const char *evtCode, char *buffer);	
//添加有效报警事件
BSSCLIENT_API BOOL ST_BSS_AddEventFilter(long lClient, const char *evtCode, const char *GUID, char *buffer);
//删除有效报警事件过滤
BSSCLIENT_API BOOL ST_BSS_DeleteEventFilter(long lClient, const char *evtCode, const char *GUID, char *buffer);
//查询有效报警事件
BSSCLIENT_API BOOL ST_BSS_QueryEventFilter(long lClient, const char *GUID, char *buffer);
//查询服务版本
BSSCLIENT_API BOOL ST_BSS_QueryServiceVersion(long lClient, const char *username, char *buffer);
//--------------- add end -----------//

#endif
