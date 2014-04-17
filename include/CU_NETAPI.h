//CU_NETAPI.h	
#pragma once
#include "Afxtempl.h" 

#ifdef CU_NETAPI_EXPORT
#define CU_NET_API extern "C" __declspec(dllexport)
#else
#define CU_NET_API  extern "C" __declspec(dllimport)
#endif

// buf修改为512 * 1024 否则会因内存越界导致客户端崩溃 Date: 2013-9-3 Author: yms
#define FRAME_MAX_SIZE_T         512 * 1024        
// Error Code, 所有错误类型都为非正值
#define ST_OK                   S_OK
#define ST_FAILED               S_FALSE
#define ST_ERR_UNKNOWN          0x80000000    // 未知错误类型
#define ST_ERR_SOCKET           0x80008001
#define ST_ERR_XML              0x80008002
#define ST_COM_ERROR            0x80008003
#define ST_ERR_HTTPDOC          0x80008004
#define ST_ERR_SENDDATA         0x80008015
#define ST_ERR_DOMAIN_PASE		0x80008016	//域名解析失败
#define ST_TIMEDOUT             0x80008021
#define ST_ERR_RELOGIN          0x80008030
#define ST_ERR_REJECT           0x80008031
#define ST_ERR_SMU              0x80008032    // 这个错误表示CMU连接SMU故障
#define ST_ERR_ROUTE            0x80008033
#define ST_ERR_COMMAND			0x80008034	  //CMU不支持的命令

//the rule of port offset  in the net communication define (mdu_base_port)
#define ST_MDU_VOICE_OFFSET		1 //语音对讲时基于MDU端口的偏移量
#define VOD_BASE_MDU_OFFSET		2
#define VOD_BASE_MSU_OFFSET		1

//the rule of port offset  in the net communication define (cmu_base_port)
#define PORT_CSG_INCREASE_NUM	1	
//////////////////////////////////////////////////////////////////////////

//device type define
//1-音视频主码流，2-报警输入，3-报警输出,4-解码通道，5-显示通道 6-音视频从码流
//A-测控量-遥测，B-测控量-遥信，C-测控量-遥控，D-测控量-遥调
#define AUDIO_AND_VIDEO_PRIMARY_STREAM		1
#define ALARM_PUTIN							2
#define ALARM_PUTOUT						3
#define DECODER_CHANNEL						4
#define DISPLAY_CHANNEL						5
#define AUDIO_AND_VIDEO_SECONDARY_STREAM	6
#define REMOTE_MEASURE						17	//	A
#define REMOTE_SEMAPHORE					18	//	B
#define REMOTE_CONTROL						19	//	C
#define REMOTE_ADJUST						20	//	D

//alarm type define
#define NET_ALARM_PU_ONLINE						0x0000	//pu上线
#define NET_ALARM_PU_LOGOUT						0x0001	//pu下线
#define NET_ALARM_CMU_CONNECT_INTERMIT			0x0002	//CMU连接中断
#define NET_ALARM_CMU_RECONNECT_SUCCESS			0x0003	//重连CMU成功
#define NET_ALARM_VIDEO_INTERMIT				0x0004	//视频中断
#define NET_ALARM_VIDEO_RECONNECT_SUCCEED		0x0005	//重连视频成功
#define NET_ALARM_VIDEO_RECONNECT_FAILED		0x0006	//重连视频失败
#define NET_ALARM_USER_LOGIN_IN_THE_OTHER_PLACE	0x0007	//该用户已在其它地方登录
#define PU_ALARM_PRI_CHANNEL_I_O					0x0100	//主通道:I/O探头告警
#define PU_ALARM_PRI_CHANNEL_MOVE_DETECTIVE			0x0101	//主通道:移动侦测告警
#define PU_ALARM_PRI_CHANNEL_VIDEO_LOST				0x0102	//主通道:视频丢失告警
#define PU_ALARM_PRI_CHANNEL_HARDDISK				0x0104	//主通道:硬盘告警
#define PU_ALARM_PRI_CHANNEL_MDU_IP_ID_NOT_MATCH	0x0105	//主通道:MDU的IP与ID不匹配
#define PU_ALARM_SEC_CHANNEL_I_O					0x0110	//从通道:I/O探头告警
#define PU_ALARM_SEC_CHANNEL_MOVE_DETECTIVE			0x0111	//从通道:移动侦测告警
#define PU_ALARM_SEC_CHANNEL_VIDEO_LOST				0x0112	//从通道:视频丢失告警
#define PU_ALARM_SEC_CHANNEL_HARDDISK				0x0114	//从通道:硬盘告警
#define PU_ALARM_SEC_CHANNEL_MDU_IP_ID_NOT_MATCH	0x0115	//从通道:MDU的IP与ID不匹配
#define PU_ALARM_SATELLITE_MAP_ALARM				0x0199	//卫星地图告警
#define TV_ALARM									0x0200	//电视墙告警
#define PU_ALARM_UPDATE_START						0x0300	//设备开始升级
#define PU_ALARM_UPDATE_SCCESS						0x0301	//升级成功
#define PU_ALARM_UPDATE_FAILED						0x0302	//升级失败
#define PU_ALARM_REMOTE_MEEASURE					0x0400	//遥测
#define ALARM_NOT_PARSE_TYPE						0xFFFF	//无法解析的警告类型

//right-control style define
#define	RIGHT_DOMERIGHT		0x00000001		//云台控制	1	
#define	RIGHT_PARMGET		0x00000002		//参数查询	2	
#define	RIGHT_PARMCONFIG	0x00000004		//参数设置  3 
#define	RIGHT_AUDIOTALK		0x00000008		//语音对讲	4	
#define	RIGHT_PLAYBACK		0x00000010		//历史回放	5	
#define	RIGHT_ALARMRECV		0x00000020		//告警接收	6	
#define	RIGHT_3DCONTROL		0x00000040		//3D球控制	7	
#define	RIGHT_EQUIPIP		0x00000080		//设备IP	8	
#define	RIGHT_MATRIX		0x00000100		//矩阵控制	9	
#define	RIGHT_MAINTAIN		0x00001000		//设备维护  10
#define	RIGHT_LOCALRECORD	0X00000200		//本地录像  11

//////////////////////////////////////////////////////////////////////////
#define MAX_BROADCAST_GROUP 32
#define MAX_NUM_IN_GROUP    32
#define MAX_NUM_DOMAIN		128

//电视墙
#define		MAX_MONITOR_NUM		100
#define		MAX_WINDOW_NUM		100

typedef  void(* RECVCALLBACK)( long lHandle, void* lpBuf, long lSize, long lDecoderID);
//namespace ST_CU_LIB
namespace CU_NET_LIB
{  	
	//初始化网络库实例　返回参数实用于每一个接口的第一个参数
	CU_NET_API DWORD  InitilLibInstance();
	//销毁网络库实例
	CU_NET_API BOOL  DeleteLibInstance(DWORD dwLibInstance);	
	struct GUINFO{
		char    DomainID[32];	//支持多域系统
		char    DomainName[128];
		int		DomainType;		//域类型： 0 本域; 1 子域;
		char    GUID[32];	
		char    GUName[256];
		char    PUID[32]; 
		int     GUType;
		
		BOOL    HasDome;
		int		right;
		int		nptzlevel;
		char    SepModeID[10];	//设备分屏模式ID
		LONG    lManufactType;	//指定厂商类型 '0x54533030' 金三立H264系列; '0x42483030' 汉邦H264系列;	
									//'0x4b483030' 海康H264系列; '0x48443030'大华H264系列;
// 		BOOL    DomeRight;
//		BOOL    EnConfig;
//		BOOL    EnTalk;
//		BOOL    EnBackPlay;
		BOOL	EnTcpPView; //应用程序赋值
		
		BOOL    Bypass;
		BOOL    bState;
		DWORD   dwLastTime;
	}; // The most important struct type, include all informations of a device;
	
	// 2008/06/05 增加数据结构
	struct DEVICE_NODE
	{
		int  nType; // 类型决定下面几个参数的有效性	0:Domain  1:Area
		char DomainName[32];
		char DomainID[32];
		char AreaName[32];
		char AreaID[32];
		GUINFO  guInfo;		
	};
	//获取设备列表
	CU_NET_API HRESULT  GetDeviceList(DWORD pdwServerPara, LPCTSTR lpszQueryID, int nType, DEVICE_NODE* pNode, int nMaxCount, int *pCount);
	
	struct CLIENTINFO{
		long            lHandle;        // 窗口句柄
		RECVCALLBACK    lpFunc;         // 对应的回调函数指针	
		GUINFO          guInfo;         // 摄像机描述
		long			nProtocolType;	// 协议类型 0-UDP 1-TCP
	};
	
	struct MEDIA_DATA_INFO
	{
		unsigned int  packages;		    // 总包数
		unsigned int  packages_rate;    // 包率
		unsigned int  lost;             // 总丢包
		unsigned int      lostrate;     // 丢包率
		unsigned int      rate;         // 码率
		ULONG64   size;			        // 总大小
	};
	
	struct DisInfo
	{
		int  nSwitch;	//0成功，1:窗口被锁定　 2:失败  5:解码器不在线
		char szEncoderName[32];
		int  nWndNo;
	};
	struct TwAlarmInfo
	{
		char    szDisGuID[32];
		char	szTVID[32];
		char    szSepID[10];
		int     nMonitorNo;
		int		iRunType;	//  1 巡回，2 群组, 3 单步
		char	szRunName[32];
		int     nDisInfoNum;	//显示信息个数
		BOOL    bKeepOthers;
		DisInfo	disInfo[MAX_WINDOW_NUM];
	};
	struct AlarmInfo
	{
		char  szDomainid[32];
		char  szPuid[32];
		char  szGuid[32];              // GUID
		DOUBLE  dwLongitude;        // 经度
		DOUBLE  dwLatitude;         // 纬度
		DOUBLE  dwSpeed;				   //速度
		DOUBLE  dwVerifyLongitude;  // 校验经度
		DOUBLE  dwVerifyLatitude;   // 校验纬度

		char  szDeviceName[64];        //告警源设备名称
		char  szAlarmInfo[128];        //告警内容
		char  szRemarks[256];		   //告警备注信息
		DWORD   nAlarmType;			   //告警类型
		DWORD   dwAlarmTime;	       //告警发生时间
		DWORD   dwParam1;              // 附加参数
		TwAlarmInfo twInfo;
	};
	
	// Time-out interval, in milliseconds , 只能在ST_ClientStartUp之前调用
	CU_NET_API void   SetCmdTimeOut(DWORD pdwServerPara, DWORD dwMilliseconds);    
	CU_NET_API BOOL   GetMediaInfo(DWORD pdwServerPara, long lHandle, MEDIA_DATA_INFO* pInfo);
	
	// 通过消息传递主动通知上层应用程序(包括告警信息\视频终止信息等)
	//注册窗口和消息, 在其他网络通信库函数之前
	CU_NET_API BOOL  ClientStartUp(DWORD pdwServerPara, UINT nMessage, HWND hWnd);  
	//清除窗口注册
	CU_NET_API BOOL  ClientCleanUp(DWORD pdwServerPara);
	//获取告警信息
	CU_NET_API BOOL  GetAlarmInfo(DWORD pdwServerPara, AlarmInfo *pInfo); // 如果有记录则返回TRUE,其他返回FALSE;
	
	// 登陆相关
	//获取登录标志
	CU_NET_API DWORD     GetLoginFlag(DWORD pdwServerPara);
	//请求登录
	CU_NET_API BOOL      RequestLogin(DWORD pdwServerPara, LPCTSTR lpszServerIP, UINT nPort,LPCTSTR lpszUserID, LPCTSTR lpszUserPwd, LPTSTR lpszLocalDomainID, LPTSTR lpRemoteIP, int& nSum);
	//发送抢占登录命令
	CU_NET_API BOOL	   GrabLogin(DWORD pdwServerPara);
	//注销登录
	CU_NET_API BOOL      RequestLogout(DWORD pdwServerPara);	
	//订阅平台告警信息上传
	CU_NET_API HRESULT   SubNotifyInfo(DWORD pdwServerPara);
	//用户密码设置
	CU_NET_API HRESULT   ChangePassword(DWORD pdwServerPara, LPCTSTR lpszOldPwd, LPCTSTR lpszNewPwd);
	CU_NET_API HRESULT   QueryDeviceList(DWORD pdwServerPara, LPCTSTR lpszXmlFile);
	CU_NET_API HRESULT   GetCmuIp(DWORD pdwServerPara, LPCTSTR lpCmuIp, int nLen);
	//获取登录域ＩＤ
	CU_NET_API HRESULT   GetDomainInfo(DWORD pdwServerPara, LPCTSTR lpDomainID, int nLen);
	//获取平台CMU版本信息
	CU_NET_API HRESULT   GetCMUVersionInfo(DWORD pdwServerPara, char* pszCmuVersion, int nLen);
	
	// 实时视频浏览(2008/02/28)
	// 终止一个全局的阻塞调用
	CU_NET_API void      CancelWaitting(DWORD pdwServerPara);                        // 终止一个全局的阻塞调用
	// 创建一个视频连接实例
	CU_NET_API LONG      CreateVideoInstance(DWORD pdwServerPara, CLIENTINFO client);  // 创建一个视频连接实例
	// 销毁一个由上述接口创建的视频连接实列
	CU_NET_API BOOL      CancelVideoInstance(DWORD pdwServerPara, long lHandle);        
	//获取上述接口创建的视频连接实列的状态	
	CU_NET_API BOOL      GetMediaState(DWORD pdwServerPara, long lHandle);
	//上述接口创建的视频连接实列的重连	
	CU_NET_API BOOL      Reconnect(DWORD pdwServerPara, long lHandle);
	 
	typedef struct tag_mdu_route_info
	{
		int	 DomainType; //非0时所有信息有效
		char szLocalMduIp[128];	//本域MDU IP
		char szLocalMduId[32];	//本哉MDU ID
		UINT uLocalPort;		//本哉MDU port
		char szRemoteCsgIp[128];	//子域CSG IP
		UINT uRemoteCsgPort;		//子域CSG port
		char szRemoteMduIp[128];//子域MDU IP
		char szRemoteMduId[32];	//子哉MDU ID
		UINT uRemoteMduPort;	//子哉MDU port
	}MDU_ROUTE_INFO;
	//获取视频路由信息
	CU_NET_API HRESULT   QueryPuRealRoute(DWORD pdwServerPara, GUINFO guInfo, MDU_ROUTE_INFO &mduInfo); 
	//获取CSG路由信息
	CU_NET_API HRESULT   QueryCsgRoute(DWORD pdwServerPara, GUINFO guInfo, MDU_ROUTE_INFO &mduInfo); 
	//此接口不再使用
	CU_NET_API HRESULT   QueryPURoute(DWORD pdwServerPara, LPCTSTR lpszDomanID, LPCTSTR lpszPUID, LPTSTR lpszSevIp, UINT& uPort); 
	// 启动由CreateVideoInstance创建的视频连接
	CU_NET_API HRESULT   RealVideoPreviewStart(DWORD pdwServerPara, long lHandle, MDU_ROUTE_INFO mduInfo);
	// 终止由CreateVideoInstance创建的视频连接
	CU_NET_API HRESULT   RealVideoPreviewStop(DWORD pdwServerPara, long lHandle);      // 终止视频连接
	
	// 前端I/O控制
	CU_NET_API HRESULT   IoControl(DWORD pdwServerPara, GUINFO guInfo, BOOL bStatus, BOOL bReturn); //0-不返回 1-不等待回应立即返回
	
	// 订阅或取消某个设备告警
	CU_NET_API HRESULT   SubAlarmInfo(DWORD pdwServerPara, GUINFO guInfo, BOOL bFlag);
	
	// 语音部分
	struct BROADCAST_INFO
	{
		char szDomainID[32];
		char szPuID[32];
		char szGuID[32];
		char GUName[256];
		int nRouteFlag;
		MDU_ROUTE_INFO routeInfo;
	};
	//此函数不再作用
	CU_NET_API BOOL      IsChartOpen(DWORD pdwServerPara);
	// ChartWithOne 启动语音对讲 nProtocolType 0-UDP, 1-TCP;
	CU_NET_API HRESULT   ChartWithOne(DWORD pdwServerPara, const GUINFO guInfo, const int nProtocolType, CLIENTINFO client);
	//发送语音数据
	CU_NET_API BOOL      SendVoiceData(DWORD pdwServerPara, const void* lpBuf, int nLen);                     // 发送音频数据
	//停止语音
	CU_NET_API HRESULT   StopChart(DWORD pdwServerPara);
	//开始语音广播
	CU_NET_API HRESULT   StartBroadcast(DWORD pdwServerPara, DWORD* dwBroadcastID, const int nProtocolType, 
									 char *szMduIp, int nPort, BROADCAST_INFO* pBroadInfo, int nCount);
	//发送语音广播数据
	CU_NET_API HRESULT   SendBroadcastData(DWORD dwBroadcastID, const void* lpBuf, int nLen);    
	//停止语音广播
	CU_NET_API HRESULT   StopBroadcast(DWORD dwBroadcastID);  

	
	// 手动要求前端录象;抓拍;布防;撤防
	//启动前端录像
	CU_NET_API HRESULT   RemoteStartRecord(DWORD pdwServerPara, GUINFO guInfo, int nTimesec);
	//启动前端抓拍
	CU_NET_API HRESULT   RemoteCapturePic(DWORD pdwServerPara, GUINFO guInfo);
	CU_NET_API HRESULT   RemoteRetCapPic(DWORD pdwServerPara, GUINFO guInfo, LPCTSTR lpsMSUID, char* pszFilePath, int pathLen);	//返回抓拍成功后的全路径
	//布防;撤防
	CU_NET_API HRESULT   RemoteAlarmEnable(DWORD pdwServerPara, GUINFO guInfo, BOOL bEnabled);
	struct Timeseg
	{
		BOOL bEnable;
		int SHour;
		int SMinute;
		int SSecond;
		int EHour;
		int EMiniute;
		int ESecond;
	};
	struct Dayseg
	{
		Timeseg time_seg[4];
	};
	struct MsuRecTime
	{
		Dayseg day_seg[7];
	};
	// 设置中心定时录像策略
	CU_NET_API HRESULT	SetMsuRecTimePlan(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuid, LPCTSTR lpszGuid, LPCTSTR lpszMsuId, const MsuRecTime *pMsuRecTime);
	CU_NET_API HRESULT	GetMsuRecTimePlan(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuid, LPCTSTR lpszGuid, LPCTSTR lpszMsuId, MsuRecTime *pMsuRecTime);
	
	struct ENCODER_NO
	{
		int	iNo;
		char szEncGuid[32];
		char szEncName[32];
		char szDomainid[32];	
	};
	//设置编码器序号
	CU_NET_API HRESULT	SetEncoderNo(DWORD pdwServerPara, ENCODER_NO *pEncoderNo, int iCount);
	CU_NET_API HRESULT	GetEncoderNo(DWORD pdwServerPara, ENCODER_NO *pEncoderNo, int iMax, int *pCount);
	struct DECODER_NO
	{
		char szDomainid[32];
		char szDecGuid[32];
		char szDecName[32];
		char szDisGuid[32];
		char szDisName[32];
		int	iNo;
	};
	//以下两接口不再使用
	CU_NET_API HRESULT	SetDecoderNo(DWORD pdwServerPara, DECODER_NO *pDecoderNo, int iCount);
	CU_NET_API HRESULT	GetDecoderNo(DWORD pdwServerPara, DECODER_NO *pDecoderNo, int iMax, int *pCount);
	//////////////////////////////////////////////////////////////////////////
	// 编码器查询/设置部分
	// 版本查询
	struct  PU_VERSION_INFO
	{
        char    version_number[32];    //版本号
        char    version_author[16];    //版权所有
        char    version_date[16];      //版本日期
	};
	//获取设备版本信息
	CU_NET_API HRESULT  GetPuVersionInfo(DWORD pdwServerPara, const GUINFO& guInfo, PU_VERSION_INFO *pInfo);
	
	// 基本参数(未归类的参数)
	struct  PU_BASICCFG_INFO
	{
		int coverType;                    // 覆盖方式,0:自动覆盖,1:报警提示.
		int prerecStatus;                 // 预录状态,0:停止,1:开启
		int switchFileTime;               // 录像文件切换时间 10~30分钟
		int twoStreamFlag;                // 双码流使能标志 1: enable, 0: disable
		int reserveSpace;                 // 保留大小
		int manualRecordTime;             // 手动录象时长
		int deleteSize;					  // 删盘大小
	};
	CU_NET_API HRESULT  GetPuBasicCfgInfo(DWORD pdwServerPara, GUINFO guInfo, PU_BASICCFG_INFO* pInfo);
	CU_NET_API HRESULT  SetPuBasicCfgInfo(DWORD pdwServerPara, GUINFO guInfo, const PU_BASICCFG_INFO* pInfo);
	
	struct VEDIO_SWITCH_INFO
	{
// 		BOOL bFirst;		//第一通道 TRUE：选择  FALSE：未选择
// 		BOOL bSecond;		//第二通道
// 		BOOL bThird;		//第三通道 
// 		BOOL bFourth;		//第四通道 
		UINT uSelected;		//以位表示第几通道 "00001101" 表示;选中了三个通道(1、3、4)
		UINT uIntervalTime;	//切换时间 2-10秒
	};
	CU_NET_API HRESULT  GetVedioSwitchInfo(DWORD pdwServerPara, GUINFO guInfo, VEDIO_SWITCH_INFO* pInfo);
	CU_NET_API HRESULT  SetVedioSwitchInfo(DWORD pdwServerPara, GUINFO guInfo, const VEDIO_SWITCH_INFO* pInfo);

	CU_NET_API HRESULT  SetVedioMutexInfo(DWORD pdwServerPara, GUINFO guInfo, int nChannel);
	CU_NET_API HRESULT  GetVedioChannelSum(DWORD pdwServerPara, GUINFO guInfo, int& nChannels);
	// 前端设备图像编码参数
	struct IMAGEENCODEPARAM{
		int video_format;           	//制式选择 0:PAL   1:NTSC
		int resolution;             	//分辨率,0:QCIF,1:CIF,2:HD1,3:D1
		int bitrate_type;           	//位率类型,0:CBR,1:VBR
		int level;            		//画质,200kbit3000kbit
		int frame_rate;			//每秒侦数
		int Iframe_interval;      	//I侦间隔
		int prefer_frame;		//侦率优先
		int Qp;					//量化系数
		int encode_type;		//0:音视频流, 1:视频流, 2:音频流
	};	
	
	CU_NET_API HRESULT   GetPuImageEncodePara(DWORD pdwServerPara, const GUINFO& guInfo, IMAGEENCODEPARAM* lpParam);
	CU_NET_API HRESULT   SetPuImageEncodePara(DWORD pdwServerPara, const GUINFO& guInfo, IMAGEENCODEPARAM param);
	CU_NET_API HRESULT   GetPuImageDisplayPara(DWORD pdwServerPara, const GUINFO& guInfo, int* contrast,	int* bright, int* hue, int* saturation);
	CU_NET_API HRESULT   DefaultPuImageDisplayPara(DWORD pdwServerPara, const GUINFO& guInfo, int* contrast,	int* bright, int* hue, int* saturation);
	CU_NET_API HRESULT   SetPuImageDisplayPara(DWORD pdwServerPara, const GUINFO& guInfo, int contrast,	int bright, int hue, int saturation);
    //add by fengzx 2011-06-29 for CMOS HD
	CU_NET_API HRESULT   GetPuImageDisplayParaCmos(DWORD pdwServerPara, const GUINFO& guInfo, int* brightness ,int* acutance ,int *chroma, int *red, int *blue);
	CU_NET_API HRESULT   DefaultPuImageDisplayParaCmos(DWORD pdwServerPara, const GUINFO& guInfo, int* brightness ,int* acutance ,int *chroma, int *red, int *blue);
	CU_NET_API HRESULT   SetPuImageDisplayParaCmos(DWORD pdwServerPara, const GUINFO& guInfo, int brightness ,int acutance ,int chroma, int red, int blue);
	// 串口参数
	struct SERIALPORTPARAM
	{
		int data_bit;       //数据位,值:5/6/7/8 默认8
		int stop_bit;       //停止位,值:0/1/2 默认1
		int reserve[2];
		int verify_rule;    //验证规则,-1:无,0:奇校验,1:偶校验, 默认-1
		int baut_rate;      //波特率,协议特定 默认9600
	};
	CU_NET_API HRESULT   GetPuSerialPort(DWORD pdwServerPara, const GUINFO& guInfo, int serialNo , SERIALPORTPARAM* lpParam);
	CU_NET_API HRESULT   SetPuSerialPort(DWORD pdwServerPara, const GUINFO& guInfo, int serialNo , SERIALPORTPARAM  param);
	
	//云台设置个与控制
	struct PTZPARAM
	{
		int ptz_addr;       //云台地址0 ~ 255
		int ptz_type;       //云台类型索引.PELCO_D-1,PELCO_P-2,松下-3,YAAN-4,santachi-5,santachi_in-6,矩阵-9
		int serial_no;      //串口号,值默认为1
		SERIALPORTPARAM serial_param;
		int reserve;
	};
	typedef struct _ptzcontrol_t
	{
		char    csgIp[32];	
		char    cmd[32];
		char    param[32];
		char    msgtype[32];
		UINT    csgport;
		int     speed;
		GUINFO  guInfo;
	}PTZControl;
	CU_NET_API HRESULT   GetPuPtzParam(DWORD pdwServerPara, const GUINFO& guInfo, PTZPARAM* lpParam);
	CU_NET_API HRESULT   SetPuPtzParam(DWORD pdwServerPara, const GUINFO& guInfo, PTZPARAM  param);
	CU_NET_API HRESULT   DomeCtrlRequest(DWORD pdwServerPara, LPCTSTR lpszDomainID, LPCTSTR lpszGUID, DWORD *pCode, LPTSTR lpszCsgIp, UINT& uPort);	//pCode：返回的错误代码
	CU_NET_API HRESULT   DomeControl(DWORD pdwServerPara, GUINFO guInfo, LPCTSTR lpszIP, UINT uPort, char* msgType, int nSpeed, const char* cmdType, const char* param);
	
	//设置与查询 LOGO参数
	struct IMAGETEXTPARAM
	{
		BOOL bitmapTimeEnable;   // 时间
		int  bitmapX;
		int  bitmapY;
		COLORREF  clrTime;
		
		BOOL bitmapTextEnable;	
        int  bitmapTextX;
		int  bitmapTextY;
		COLORREF  clrText;
		char bitmapText[48];
	};
	CU_NET_API HRESULT   GetPuImageTextPara(DWORD pdwServerPara, const GUINFO& guInfo, IMAGETEXTPARAM* lpParam);
	CU_NET_API HRESULT   SetPuImageTextPara(DWORD pdwServerPara, const GUINFO& guInfo, IMAGETEXTPARAM  param);
	// 前端设备时间参数
	CU_NET_API HRESULT   GetPuTime(DWORD pdwServerPara, GUINFO guInfo, SYSTEMTIME* lptime);
	CU_NET_API HRESULT   SetPuTime(DWORD pdwServerPara, GUINFO guInfo, SYSTEMTIME  time);
	// 设置设备遮挡区域
	typedef struct {
		COLORREF  HideAreaColor;	//颜色
		int HideAreaX;	//X坐标
		int HideAreaY;	//Y坐标
		int HideAreaWidth;	//区域的宽度
		int HideAreaHeight;	//区域的高度
	}HIDEIMAGEAREA_ITEM;
	struct HIDEIMAGEAREA
	{
		BOOL bEnable;	//遮挡是否生效
		int  nNum;		//区域个数
		int  reserve[2];
		HIDEIMAGEAREA_ITEM  item[16];
	};
	CU_NET_API HRESULT   GetPuImageHideArea(DWORD pdwServerPara, GUINFO guInfo, HIDEIMAGEAREA *pArea);
	CU_NET_API HRESULT   SetPuImageHideArea(DWORD pdwServerPara, GUINFO guInfo, HIDEIMAGEAREA Area);
	
	typedef struct 
	{
		int SHour;
		int SMinute;
		int SSecond;
		int EHour;
		int EMiniute;
		int ESecond;
	}RECORD_TIMESEG, MOTION_TIMESEG, PROBER_TIMESEG,CAPTRUE_TIMESEG;
	struct RECORD_INFO    // 一天的时间段
	{
		BOOL   bEnable;
		RECORD_TIMESEG  timeSeg[4]; // 4个时间段	
	};

	typedef struct    //用于抓拍
	{
		char nEnable;
		UINT uInterval;
		CAPTRUE_TIMESEG timeSeg[4];
	}CAPTRUE_INFO;


	CU_NET_API HRESULT   GetPuLocalStorageTask(DWORD pdwServerPara, GUINFO guInfo, RECORD_INFO* pRecInfo, int nCount);
	CU_NET_API HRESULT   SetPuLocalStorageTask(DWORD pdwServerPara, GUINFO guInfo, const RECORD_INFO* pRecInfo, int nCount);
	CU_NET_API HRESULT   GetPuTimeSnapTask(DWORD pdwServerPara, GUINFO guInfo, CAPTRUE_INFO* pRecInfo, int nCount);
	CU_NET_API HRESULT   SetPuTimeSnapTask(DWORD pdwServerPara, GUINFO guInfo, const CAPTRUE_INFO* pRecInfo, int nCount);
	
	// 移动侦测告警参数
	struct MOTIONDETECTION_INFO{
		int  moveGuardFlag;        // 布/撤防
		int  moveEnable;           // 报警使能
		int  sensitiveLevel;       // 灵敏度,1:1级,...,9:9级
		int  alarmIntervalTime;    // 侦察间隔时间
		int  jointRecordTime;      // 持续录像的时间
		int  jointOutputTime;      // 持续输出的时间
		int  beepOutputTime;       // 持续锋鸣器发声的时间
		int  beepOutputEnable;     // 锋鸣器输出使能
		int  jointSnapEnableCh;    // 联动抓拍使能
		int  jointRecordEnableCh;  // 联动录像使能
		int  jointOutputEnableCh;  // 联动输出使能
		char motionarea[128];           // 侦测区域(自定义格式)
		MOTION_TIMESEG  timeSeg[4];
	};
	CU_NET_API HRESULT   GetPuMotionDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, MOTIONDETECTION_INFO* pMotionInfo);
	CU_NET_API HRESULT   SetPuMotionDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, const MOTIONDETECTION_INFO*  pMotionInfo);
	
	// 视频丢失告警
	struct LOSEDETECTION_INFO{
		int  loseGuardFlag;        // 布/撤防
		int  loseEnable;           // 报警使能
		int  alarmIntervalTime;    // 侦察间隔时间
		int  jointRecordTime;      // 持续录像的时间
		int  jointOutputTime;      // 持续输出的时间
		int  beepOutputTime;       // 持续锋鸣器发声的时间
		int  beepOutputEnable;     // 锋鸣器输出使能
		int  jointSnapEnableCh;    // 联动抓拍使能
		int  jointRecordEnableCh;  // 联动录像使能
		int  jointOutputEnableCh;  // 联动输出使能
	};
	CU_NET_API HRESULT   GetPuLoseDetectionCfg(DWORD pdwServerPara, GUINFO guInfo,  LOSEDETECTION_INFO* pLoseInfo);
	CU_NET_API HRESULT   SetPuLoseDetectionCfg(DWORD pdwServerPara, GUINFO guInfo,  const LOSEDETECTION_INFO*  pLoseInfo);
	
	// I/O告警
	struct PROBERDETECTION_INFO{
		int  proberType;           // 探头类型 0:常开  1:常闭
		int  proberGuardFlag;      // 布/撤防
		int  proberEnable;         // 报警使能
		int  alarmIntervalTime;    // 侦察间隔时间
		int  jointRecordTime;      // 持续录像的时间
		int  jointOutputTime;      // 持续输出的时间
		int  beepOutputTime;       // 持续锋鸣器发声的时间
		int  beepOutputEnable;     // 锋鸣器输出使能
		int  jointSnapEnableCh;    // 联动抓拍使能
		int  jointRecordEnableCh;  // 联动录像使能
		int  jointOutputEnableCh;  // 联动输出使能
		PROBER_TIMESEG timeSeg[4];
	};
	CU_NET_API HRESULT   GetPuProberDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, PROBERDETECTION_INFO* pProberInfo);
	CU_NET_API HRESULT   SetPuProberDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, const PROBERDETECTION_INFO*  pProberInfo);
	
	// 解码器信令接口
	// 解码器手动切换
	CU_NET_API HRESULT   DecoderSwitch(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuidDec, LPCTSTR lpszGuidDec, LPCTSTR lpszPuidEnc, LPCTSTR lpszGuidEnc);
	
	// 恢复出厂设置
	CU_NET_API HRESULT   RestorePuConfig(DWORD pdwServerPara, GUINFO guInfo);
	// VOD接口
	struct VODSERVER_INFO{
		char    szDomainID[32];
		char	szVodName[64];
		char	szVodIp[16];
		char	szVodID[32];
		unsigned short  nVodPort;
	};
	CU_NET_API HRESULT   VodServerQuery(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszGuid, int *pCount, VODSERVER_INFO *pVodServerInfo);
	// MSU接口
	CU_NET_API HRESULT   MsuManualRecordReq(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuid, LPCTSTR lpszGuid, int nTime, LPCTSTR lpszMsuName, LPCTSTR lpszMsuIp, LPCTSTR lpszMsuID);
	
	//pu文件查询 nQueryType 0-录像文件 1-图片文件 nQueryType=1时nType无效
	struct GuFileInfo
	{
		//@{"FileName:/record/hd0/2008-02-28/guid12345678/09-22-00.dat"}
		char file[256];
		int type;	//@{Bit Set}
		int size;	//@{Total Size Of The File}
	} ;
	CU_NET_API HRESULT QueryGuFileLists(DWORD pdwServerPara, GUINFO guInfo, int nQueryType, int nType, SYSTEMTIME* pSysStartTime, SYSTEMTIME* pSysEndTime, GuFileInfo *pFileList, int nMaxCount, int *pCount);
	//查询设备IP信息
	struct PuIpInfo
	{
		char IpAddress[256];
		int	iControlPort;
		int iSipPort;
		char subNetMask[16];
		char Geteway[16];
		char IpPublicAddress[256];
		char IpWifiAddress[256];
	};
	CU_NET_API HRESULT GetPuIpInfo(DWORD pdwServerPara, GUINFO guInfo, PuIpInfo *pIpInfo);
	
	struct PuRealStreamInfo
	{
		char szCodeRate[10];	//码率
		char szframeRate[10];	//帧率
	};
	//获取设备端的实际码流信息
	CU_NET_API HRESULT GetPuRealStreamInfo(DWORD pdwServerPara, GUINFO guInfo, PuRealStreamInfo *pInfo);

	struct PlatformInfo
	{
		char puId[64];
		char puName[128];
		char puPassword[64];
// 		int  controlPort;
// 		int  sipPort;
// 		int  rtspPort;
// 		char dns[16];		
		int  registerServerPort;
		char registerServerIp[128];
		int  sipRegisterServerPort;
		char sipRegisterServerIp[128];
		char enableFlag;//0:不启用;  1:启用.
		char conType;//0:UDP  1: TCP
		BOOL bSmoothFlag;
	};
	//获取设备端的平台参数信息
	CU_NET_API HRESULT GetPlatformInfo(DWORD pdwServerPara, GUINFO guInfo, PlatformInfo* pInfo);
	//设置设备端的平台参数信息
	CU_NET_API HRESULT SetPlatformInfo(DWORD pdwServerPara, GUINFO guInfo, PlatformInfo pInfo);
	//获取系统时间
	CU_NET_API HRESULT GetSystemTime(DWORD pdwServerPara, char* pTime, int nMaxLen);
	//校正系统时间
	CU_NET_API HRESULT VerifySystemTime(DWORD pdwServerPara, char* pTime);

	struct PPPOEInfo
	{
		char account[64];
		char password[24];
		char ip[16];
		int	 enable;
		int	 status;
		int  ppp_interface;		//eth0 :0,  eth2 :1   cdma:2
		int  dns_server;	//qdns 0,qdns-static 1, dyndns 2, dyndns-static 3,changeip 4
		int  dns_enable;
		char mydomain[256];
		char username[128];
		char dns_pwd[128];
	};
	//获取设备端PPPOE信息
	CU_NET_API HRESULT GetPPPOEInfo(DWORD pdwServerPara, GUINFO guInfo, PPPOEInfo* pInfo);
	//设置设备端PPPOE信息
	CU_NET_API HRESULT SetPPPOEInfo(DWORD pdwServerPara, GUINFO guInfo, PPPOEInfo pInfo);

	//重新启动设备
	CU_NET_API HRESULT RestartPuDevice(DWORD pdwServerPara, GUINFO guInfo);
	//恢复设备端的默认值
	CU_NET_API HRESULT SetPuDeviceDefult(DWORD pdwServerPara, GUINFO guInfo);
	//恢复设备端的出厂设置
	CU_NET_API HRESULT RecovePuDeviceFactory(DWORD pdwServerPara, GUINFO guInfo);
	//为设备提供升级文件
	struct UPDATE_FILE_INFO
	{
		char szUser[32];
		char szPwd[32];
		char szPath[256];
		char szName[128];
		int  nSize;
	};
	CU_NET_API HRESULT SetPuUpdateFile(DWORD pdwServerPara, GUINFO guInfo, UPDATE_FILE_INFO fileInfo);
	//获取GPS轨迹信息
	struct GPS_TRACK_INFO 
	{
		char szTime[30];	
		char szLongitude[15];
		char szLatitude[15];
		char szSpeed[10];
	};
	//strStart, strEnd格式: YYYYMMDD-HH:MM:SS
	//这个定位符, 你看下是用你返回的最后一条记录,还是另外你给我返回一个什么值做你那边的定位符.
	//你返回的记录格式:	RECORD;RECORD;...;RECORD;
	//每个RECODE内容包括:时间,经度,纬度,速度...
	CU_NET_API HRESULT GetGPSTrackInfo(DWORD pdwServerPara, GUINFO guInfo, LPCSTR strStart, LPCSTR strEnd,
		GPS_TRACK_INFO *pTrackInfo, int& nInfoNum, int nPos);
	//////////////////////////////////////////////////////////////////////////
	// 电视墙API
	// 设置电视墙
	//////////////////////////////////////////////////////////////////////////
	struct WINDOW_INFO	//窗口信息
	{
		int     nMoniterNo;			//窗口属于哪个监视器	不属于任何监视器：0;
		int		nWindNo;			//窗口序号
		char	szDisplayName[32];
		char	szDisplayGUID[32];
		BOOL	bFullScreen;		//是否处于全屏状态
		BOOL	bWinLock;			//是否处于锁定状态
		BOOL	bPlaySound;			//声音是否开启
		UINT    uSwitchType;		//切换类型，无效值：0，单步：1，巡回：2，群组：3。
		BOOL	bState;
		char    szEncoderName[128];//编码器
		WINDOW_INFO()
		{
			nMoniterNo = 0;
			nWindNo = 0;
			bFullScreen = FALSE;
			bWinLock = FALSE;
			bPlaySound = FALSE;
			uSwitchType = 0;
			bState = FALSE;
			memset(szDisplayName, 0, sizeof(szDisplayName));
			memset(szDisplayGUID, 0, sizeof(szDisplayGUID));
			memset(szEncoderName, 0, sizeof(szEncoderName));
		}
	};
	struct SEP_SCREEN_INFO	//分屏信息
	{
		char	szSepID[10];	//隶属哪种分屏模式
		int		nWinNum;
		RECT   rectWnd[MAX_WINDOW_NUM];
	};
	struct MONITOR_INFO{
		int     iMonterNo;		//监视器序号
		int		index;
		int		iLeft;			//确定监视器坐标的的四个边界值
		int		iTop;			//..2.
		int		iRight;			//..3.
		int		iBottom;		//..4.
		char	szTVID[32];				//所属电视墙ID		
		char	szDisplayName[32];		//显示通道名
		char	szDisplayGUID[32];		//显示GUID与分屏模式是绑定在一起的	
		SEP_SCREEN_INFO  sepInfo;		//指向分屏信息（无法直接指向分屏信息，因分屏信息可以刷新。会导致重定向有问题）
		WINDOW_INFO*	 pWinInfo[MAX_WINDOW_NUM];	//根据分屏信息动态创建窗口信息
		MONITOR_INFO()
		{
			iMonterNo = -1;
			index = -1;
			iLeft = 0;
			iTop = 0;
			iRight = 0;
			iBottom = 0;
			memset(szTVID, 0, sizeof(szTVID)-1);
			memset(szDisplayName, 0, sizeof(szDisplayName)-1);
			memset(szDisplayGUID, 0, sizeof(szDisplayGUID)-1);
			for (int i =0; i < MAX_WINDOW_NUM; i++)
			{
				pWinInfo[i] = NULL;
			}
		}
	};
	struct TWCONFIG_INFO{
		char	szDomainID[32];
		char	szAreaID[32];
		char	szTVID[32];
		char	szName[32];
		int		iSplitX;
		int		iSplitY;
		int		iMonitor;
		MONITOR_INFO*  pMonitorInfo[MAX_MONITOR_NUM];	//根据监视器个数动态创建监视器信息
	};
	//设置巡回
#define MAX_TOURSTEP_NUM	128
	struct TOURSTEP_INFO{
		int		iInterTime;
		char	szDomainID[32];
		char	szEncoderGUID[32];
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
	//此函数不再使用
	CU_NET_API HRESULT   TourConfigSet(DWORD pdwServerPara, TOURCONFIG_INFO *pTourInfo);

	//获取ID
	CU_NET_API HRESULT   GetTVID(DWORD pdwServerPara, LPCTSTR lpDomain, LPCTSTR lpAreaID, LPCTSTR lpName, LPCTSTR lpID);
	CU_NET_API HRESULT   GetTourID(DWORD pdwServerPara, LPCTSTR lpDomain, LPCTSTR lpAreaID, LPCTSTR lpName, int iTourNo, BOOL bAutoJump, LPCTSTR lpID);
	CU_NET_API HRESULT   GetGroupID(DWORD pdwServerPara, LPCTSTR lpDomain, LPCTSTR lpAreaID, LPCTSTR lpName, LPCTSTR lpID, int iGroupNo);
	//删除电视墙\巡回\群组列表	iModifyType 0-电视墙 1-巡回 2-群组
	CU_NET_API HRESULT   DeleteConfig(DWORD pdwServerPara, int iDeleteType, LPCTSTR lpID);
	//查询电视墙\巡回\群组列表 iQueryType 0-电视墙 1-巡回 2-群组
	struct QUERY_INFO{
		char	szName[32];
		char	szID[32];
		char	szNo[32];
		char    szTVID[32];	//以下三个字段，只有在群组信息中有效
		char    szTVName[32];
		int     nMonitorNum;
	};
	CU_NET_API HRESULT   QueryList(DWORD pdwServerPara, int iQueryType, LPCTSTR lpDomainID, LPCTSTR lpAreaID, QUERY_INFO *pInfo, int *pCount);
	//查询电视墙详细配置
	CU_NET_API HRESULT   QueryTWConfig(DWORD pdwServerPara, LPCTSTR lpTVID, int& nSplitX, int& nSplitY, int& nMonNum, MONITOR_INFO *pMonInfo);
	//查询电视墙分屏信息
	CU_NET_API HRESULT   QuerySepScreenInfo(DWORD pdwServerPara, LPCTSTR lpScrModeID, SEP_SCREEN_INFO *pSepScrInfo);
	//查询电视墙分屏模式
#define MAX_SEP_SCREEN_NUM 100
	struct SEP_SCREEN_MODE
	{
		char ModeID[10];
		char ModeNo[20];
		char ModeName[32];
		SEP_SCREEN_INFO ScreenInfo;
	};
	CU_NET_API HRESULT   QuerySepScreenMode(DWORD pdwServerPara, SEP_SCREEN_MODE *pSepScrMode, int& nRetrunNum);
	CU_NET_API HRESULT   SetDisGuidSepMode(DWORD pdwServerPara, LPCTSTR lpGuID, LPCTSTR lpModeID);
	//查询巡回详细配置
	CU_NET_API HRESULT   QueryTourConfig(DWORD pdwServerPara, LPCTSTR lpTourID, TOURCONFIG_INFO *pTourConfig);
	//群组配置信息
#define MAX_GROUPSTEP_NUM	128
#define MAX_GROUPDECODER_NUM	128
	struct GROUP_WND{ //群组步内（电视墙）的一个监视器中的一个窗口信息
		int		nWndNo;
		char    szDomainID[10];
		char	szEncGuid[32];
		char	szEncName[32];
	};	
	struct STEP_DETAILED_INFO{
		int		nMonitorNo;
		char	szSepModeID[32];	//分屏模式ID
		int     nWndNum;
		GROUP_WND* pGroupWnd[MAX_WINDOW_NUM]; 
		STEP_DETAILED_INFO()
		{
			for(int i = 0; i < MAX_WINDOW_NUM; i++)
			{
				pGroupWnd[i] = NULL;
			}
		}
	};
	struct GROUPSTEP_INFO{
		int		iInterTime;
		char    szStepID[32];		
		int     nMonitorNum;
		STEP_DETAILED_INFO* pStep_Detailed_info[MAX_MONITOR_NUM];
		GROUPSTEP_INFO()
		{
			for(int i = 0; i < MAX_MONITOR_NUM; i++)
			{
				pStep_Detailed_info[i] = NULL;
			}		
		}
	};
	struct GROUPCONFIG_INFO{
		char	szDomainID[32];
		char	szAreaID[32];
		char	szGroupID[32];
		int		nGroupNo;
		char	szName[32];
		char    szTVID[32];
		char    szTvMame[32];
		int     nMonitorCount;
		int     nStepNum;
		GROUPSTEP_INFO* pGroupStep_info[MAX_GROUPSTEP_NUM];
		GROUPCONFIG_INFO()
		{
			for(int i = 0; i < MAX_GROUPSTEP_NUM; i++)
			{
				pGroupStep_info[i] = NULL;
			}
		}
	};
	//查询群组配置
	CU_NET_API HRESULT   QueryGroupConfig(DWORD pdwServerPara, LPCTSTR lpGroupID, GROUPCONFIG_INFO *pGroupConfig);
	//查询群组步信息	
	CU_NET_API HRESULT   QueryGroupStepInfo(DWORD pdwServerPara, LPCTSTR lpStepID, GROUPSTEP_INFO *pGroupStep);
	//单步切换
	CU_NET_API HRESULT   StepRun(DWORD pdwServerPara, LPCTSTR lpTVID, LPCTSTR lpEncoderGUID, LPCTSTR lpDisplayGUID, LPCTSTR lpModeID, int nWndNo);
	//停止解码		   
	CU_NET_API HRESULT   TvDisStop(DWORD pdwServerPara, LPCTSTR lpTVID, char* szDisGUID, int nMonNo, int nWndNo);
	//巡回切换/所有巡回停止/单通道巡回停止 iType(0-单通道巡回停止 1-运行)
	CU_NET_API HRESULT   TourRun(DWORD pdwServerPara, LPCTSTR lpTourID, LPCTSTR lpTVID, LPCTSTR lpDisplayGUID, LPCTSTR lpModeID, int iWndNo);
	CU_NET_API HRESULT   TourRunAllStop(DWORD pdwServerPara, LPCTSTR lpTourID);
	//单通道停止巡回/群组
	CU_NET_API HRESULT   CHRunStop(DWORD pdwServerPara, LPCTSTR lpTVID, char* szDisGUID, char* szDecoderGUID, int nMonNo, int nWndNo);
	//群组切换/停止/暂停/恢复 iType(0-停止 1-运行 2-暂停 3-恢复)
	CU_NET_API HRESULT   GroupRun(DWORD pdwServerPara, int iType, LPCTSTR lpGroupID, LPCTSTR lpTVID);
	//解码器窗口全屏/取消全屏
	CU_NET_API HRESULT   TWWindowIsFull(DWORD pdwServerPara, BOOL bFull, char* szDisGUID, int nMonNo, int nWndNo);
	//解码器播放声音
	CU_NET_API HRESULT   TWAudioPlay(DWORD pdwServerPara, BOOL bAudio, char* szDisGUID, int nMonNo, int nWndNo);
	//获取电视墙某个窗口的状态信息
struct TV_WALL_STATE
{
	char szWndModeID[32];
	int  nWIndNum;
	WINDOW_INFO WndInfo[MAX_WINDOW_NUM];
};
	CU_NET_API HRESULT   GetTWWindowState(DWORD pdwServerPara, TV_WALL_STATE* pTvWallState, LPCTSTR lpPuid, LPCTSTR lpDisplayid, int iWindowNo = 0);
	//解码器默认连接
	CU_NET_API HRESULT   TWDefaultConnect(DWORD pdwServerPara, char* szDecoderGUID, char* szDisGUID, int nMonNo, int nWndNo);
    //解码器窗口切换锁定/取消锁定
    CU_NET_API HRESULT   TWWindowLock(DWORD pdwServerPara, BOOL bLock, char* szDisGUID, int nMonNo, int nWndNo);
    //群组、巡回运行状态查询 //1 巡回，2 群组
    CU_NET_API HRESULT   QueryRunStatus(DWORD pdwServerPara, int iType, LPCTSTR lpszID, BOOL *bStatus, LPCTSTR lpTVID = "");
	
	//矩阵单步切换
	CU_NET_API HRESULT   MatrixStepRun(DWORD pdwServerPara, LPCTSTR lpPuid, int iCameraNo, int iMonitorNo, LPCTSTR lpGuid);
	//矩阵巡回切换
	CU_NET_API HRESULT   MatrixTourRun(DWORD pdwServerPara, LPCTSTR lpPuid, int iMonitorNo, int iTourNo, LPCTSTR lpGuid);
	//矩阵群组切换
	CU_NET_API HRESULT   MatrixGroupRun(DWORD pdwServerPara, LPCTSTR lpPuid, int iGroupNo, LPCTSTR lpGuid);
	
	//查询企业信息
#define MAX_REMARK_LEN 2048
	CU_NET_API HRESULT   QueryGuidRemark(DWORD pdwServerPara, const GUINFO guInfo, char* pszContent, int nLen);

#define MAX_QUERY_RECORD_NUM 100
	struct ALARM_RECORD
	{
		char szGUID[32];
		char szGuName[64];
		char szDomainID[10];
		char szPUID[32];
		char szAlarmTime[20];
		int  nAlarmType;
		char szAlarmDesc[64];
		BOOL bAckFlag;
		int nAlarmID;
	};
	CU_NET_API HRESULT   QueryAlarmRecords(DWORD pdwServerPara, int nCount, GUINFO guInfo, const char* pszStartTime, 
		const char* pszEndTime,	int nPos, ALARM_RECORD* pAlamRecord, int& nRreNum);
	CU_NET_API HRESULT   QueryAlarmDealInfo(DWORD pdwServerPara, const char* pszAlarmID, char* pszContent, int nLen);
#define LOOKOVER_REALTIME_VIDEO 0//0-查看实时视频，1-查看历史视频，2-查看附加信息，3-确认。
#define LOOKOVER_HISTROY_VIDEO	1
#define LOOKOVER_ADDITIVE_INFO	2
#define LOOKOVER_CONFIRM_DEAL	3
	CU_NET_API HRESULT   SetAlarmDealInfo(DWORD pdwServerPara, const char* pszAlarmID, int nDealType, const char* pszTime, const char* pszInfo = NULL);
	CU_NET_API HRESULT   QueryBroadCastInfo(DWORD pdwServerPara, GUINFO* pGuList, int nMax, int& nReCount, int nGroupID);
	CU_NET_API HRESULT   SetBroadCastInfo(DWORD pdwServerPara, GUINFO* pGuList, int nCount, int nGroupID);
	struct DOMAIN_INFO
	{
		char szDomainID[20];
		char szDomainName[128];
	};
	CU_NET_API HRESULT   QueryDomainInfo(DWORD pdwServerPara, DOMAIN_INFO* pDomainList, int nMax, int& nReCount);
	//查询设备的可升级文件列表
	CU_NET_API HRESULT   QueryUpdateFile(DWORD pdwServerPara, UPDATE_FILE_INFO* pFileInfo, GUINFO guInfo, int nMax, int& nReCount);

	//测控接口
	CU_NET_API HRESULT   GetLatestRemoteMeasure(DWORD pdwServerPara, GUINFO guInfo,  char* pszBuf, int nMaxLen);
	CU_NET_API HRESULT   GetLatestRemoteSemaphore(DWORD pdwServerPara, GUINFO guInfo,  char* pszBuf, int nMaxLen);	
	CU_NET_API HRESULT   OperateRemoteControlDevice(DWORD pdwServerPara, GUINFO guInfo, BOOL bState);

	//for AMU
	CU_NET_API HRESULT Amu_GetDefensState(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, char* pszXml);
	CU_NET_API HRESULT Amu_SetDefensState(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, const char cState, char* pszXml);
	CU_NET_API HRESULT Amu_GetGUType(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, const char* GUID, char* pszXml);
	CU_NET_API HRESULT Amu_GetGUByPass(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, const char* GUID, char* pszXml, int nlen);
	CU_NET_API HRESULT Amu_SetGUByPass(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, const char* GUID, const char cByPass, char* pszXml);
	CU_NET_API HRESULT Amu_GetGUPos(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, const char* GUID, char* pszXml);
	CU_NET_API HRESULT Amu_QueryActionLinkCfg(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, const char* GUID, char* pszXml);
	CU_NET_API HRESULT Amu_QueryMap(DWORD pdwServerPara, const char *pszDomainID, const char* pszDefens, char* pszXml);
	CU_NET_API HRESULT Amu_QueryDefensInfo(DWORD pdwServerPara, const char *pszDomainID, const char *pszDefenseID, char* pszXml);
	CU_NET_API HRESULT Amu_QueryAreaInfo(DWORD pdwServerPara, const char* pszUserName, const char* pszAreaID, char* pszXml);
	CU_NET_API char*   Amu_GetLoginAreaID(DWORD pdwServerPara);
	CU_NET_API char*   GetLoginDomainID(DWORD pdwServerPara);


}

CU_NET_API void Bool_Convert(BOOL bVal, LPTSTR lpszVal);
CU_NET_API BOOL Convert_Bool(LPCTSTR lpszVal);
CU_NET_API BOOL LoadXml(MSXML2::IXMLDOMDocumentPtr pXMLDoc, const char* pSrc, BOOL bFromFile = TRUE);

