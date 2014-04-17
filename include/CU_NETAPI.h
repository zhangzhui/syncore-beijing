//CU_NETAPI.h	
#pragma once
#include "Afxtempl.h" 

#ifdef CU_NETAPI_EXPORT
#define CU_NET_API extern "C" __declspec(dllexport)
#else
#define CU_NET_API  extern "C" __declspec(dllimport)
#endif

// buf�޸�Ϊ512 * 1024 ��������ڴ�Խ�絼�¿ͻ��˱��� Date: 2013-9-3 Author: yms
#define FRAME_MAX_SIZE_T         512 * 1024        
// Error Code, ���д������Ͷ�Ϊ����ֵ
#define ST_OK                   S_OK
#define ST_FAILED               S_FALSE
#define ST_ERR_UNKNOWN          0x80000000    // δ֪��������
#define ST_ERR_SOCKET           0x80008001
#define ST_ERR_XML              0x80008002
#define ST_COM_ERROR            0x80008003
#define ST_ERR_HTTPDOC          0x80008004
#define ST_ERR_SENDDATA         0x80008015
#define ST_ERR_DOMAIN_PASE		0x80008016	//��������ʧ��
#define ST_TIMEDOUT             0x80008021
#define ST_ERR_RELOGIN          0x80008030
#define ST_ERR_REJECT           0x80008031
#define ST_ERR_SMU              0x80008032    // ��������ʾCMU����SMU����
#define ST_ERR_ROUTE            0x80008033
#define ST_ERR_COMMAND			0x80008034	  //CMU��֧�ֵ�����

//the rule of port offset  in the net communication define (mdu_base_port)
#define ST_MDU_VOICE_OFFSET		1 //�����Խ�ʱ����MDU�˿ڵ�ƫ����
#define VOD_BASE_MDU_OFFSET		2
#define VOD_BASE_MSU_OFFSET		1

//the rule of port offset  in the net communication define (cmu_base_port)
#define PORT_CSG_INCREASE_NUM	1	
//////////////////////////////////////////////////////////////////////////

//device type define
//1-����Ƶ��������2-�������룬3-�������,4-����ͨ����5-��ʾͨ�� 6-����Ƶ������
//A-�����-ң�⣬B-�����-ң�ţ�C-�����-ң�أ�D-�����-ң��
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
#define NET_ALARM_PU_ONLINE						0x0000	//pu����
#define NET_ALARM_PU_LOGOUT						0x0001	//pu����
#define NET_ALARM_CMU_CONNECT_INTERMIT			0x0002	//CMU�����ж�
#define NET_ALARM_CMU_RECONNECT_SUCCESS			0x0003	//����CMU�ɹ�
#define NET_ALARM_VIDEO_INTERMIT				0x0004	//��Ƶ�ж�
#define NET_ALARM_VIDEO_RECONNECT_SUCCEED		0x0005	//������Ƶ�ɹ�
#define NET_ALARM_VIDEO_RECONNECT_FAILED		0x0006	//������Ƶʧ��
#define NET_ALARM_USER_LOGIN_IN_THE_OTHER_PLACE	0x0007	//���û����������ط���¼
#define PU_ALARM_PRI_CHANNEL_I_O					0x0100	//��ͨ��:I/O̽ͷ�澯
#define PU_ALARM_PRI_CHANNEL_MOVE_DETECTIVE			0x0101	//��ͨ��:�ƶ����澯
#define PU_ALARM_PRI_CHANNEL_VIDEO_LOST				0x0102	//��ͨ��:��Ƶ��ʧ�澯
#define PU_ALARM_PRI_CHANNEL_HARDDISK				0x0104	//��ͨ��:Ӳ�̸澯
#define PU_ALARM_PRI_CHANNEL_MDU_IP_ID_NOT_MATCH	0x0105	//��ͨ��:MDU��IP��ID��ƥ��
#define PU_ALARM_SEC_CHANNEL_I_O					0x0110	//��ͨ��:I/O̽ͷ�澯
#define PU_ALARM_SEC_CHANNEL_MOVE_DETECTIVE			0x0111	//��ͨ��:�ƶ����澯
#define PU_ALARM_SEC_CHANNEL_VIDEO_LOST				0x0112	//��ͨ��:��Ƶ��ʧ�澯
#define PU_ALARM_SEC_CHANNEL_HARDDISK				0x0114	//��ͨ��:Ӳ�̸澯
#define PU_ALARM_SEC_CHANNEL_MDU_IP_ID_NOT_MATCH	0x0115	//��ͨ��:MDU��IP��ID��ƥ��
#define PU_ALARM_SATELLITE_MAP_ALARM				0x0199	//���ǵ�ͼ�澯
#define TV_ALARM									0x0200	//����ǽ�澯
#define PU_ALARM_UPDATE_START						0x0300	//�豸��ʼ����
#define PU_ALARM_UPDATE_SCCESS						0x0301	//�����ɹ�
#define PU_ALARM_UPDATE_FAILED						0x0302	//����ʧ��
#define PU_ALARM_REMOTE_MEEASURE					0x0400	//ң��
#define ALARM_NOT_PARSE_TYPE						0xFFFF	//�޷������ľ�������

//right-control style define
#define	RIGHT_DOMERIGHT		0x00000001		//��̨����	1	
#define	RIGHT_PARMGET		0x00000002		//������ѯ	2	
#define	RIGHT_PARMCONFIG	0x00000004		//��������  3 
#define	RIGHT_AUDIOTALK		0x00000008		//�����Խ�	4	
#define	RIGHT_PLAYBACK		0x00000010		//��ʷ�ط�	5	
#define	RIGHT_ALARMRECV		0x00000020		//�澯����	6	
#define	RIGHT_3DCONTROL		0x00000040		//3D�����	7	
#define	RIGHT_EQUIPIP		0x00000080		//�豸IP	8	
#define	RIGHT_MATRIX		0x00000100		//�������	9	
#define	RIGHT_MAINTAIN		0x00001000		//�豸ά��  10
#define	RIGHT_LOCALRECORD	0X00000200		//����¼��  11

//////////////////////////////////////////////////////////////////////////
#define MAX_BROADCAST_GROUP 32
#define MAX_NUM_IN_GROUP    32
#define MAX_NUM_DOMAIN		128

//����ǽ
#define		MAX_MONITOR_NUM		100
#define		MAX_WINDOW_NUM		100

typedef  void(* RECVCALLBACK)( long lHandle, void* lpBuf, long lSize, long lDecoderID);
//namespace ST_CU_LIB
namespace CU_NET_LIB
{  	
	//��ʼ�������ʵ�������ز���ʵ����ÿһ���ӿڵĵ�һ������
	CU_NET_API DWORD  InitilLibInstance();
	//���������ʵ��
	CU_NET_API BOOL  DeleteLibInstance(DWORD dwLibInstance);	
	struct GUINFO{
		char    DomainID[32];	//֧�ֶ���ϵͳ
		char    DomainName[128];
		int		DomainType;		//�����ͣ� 0 ����; 1 ����;
		char    GUID[32];	
		char    GUName[256];
		char    PUID[32]; 
		int     GUType;
		
		BOOL    HasDome;
		int		right;
		int		nptzlevel;
		char    SepModeID[10];	//�豸����ģʽID
		LONG    lManufactType;	//ָ���������� '0x54533030' ������H264ϵ��; '0x42483030' ����H264ϵ��;	
									//'0x4b483030' ����H264ϵ��; '0x48443030'��H264ϵ��;
// 		BOOL    DomeRight;
//		BOOL    EnConfig;
//		BOOL    EnTalk;
//		BOOL    EnBackPlay;
		BOOL	EnTcpPView; //Ӧ�ó���ֵ
		
		BOOL    Bypass;
		BOOL    bState;
		DWORD   dwLastTime;
	}; // The most important struct type, include all informations of a device;
	
	// 2008/06/05 �������ݽṹ
	struct DEVICE_NODE
	{
		int  nType; // ���;������漸����������Ч��	0:Domain  1:Area
		char DomainName[32];
		char DomainID[32];
		char AreaName[32];
		char AreaID[32];
		GUINFO  guInfo;		
	};
	//��ȡ�豸�б�
	CU_NET_API HRESULT  GetDeviceList(DWORD pdwServerPara, LPCTSTR lpszQueryID, int nType, DEVICE_NODE* pNode, int nMaxCount, int *pCount);
	
	struct CLIENTINFO{
		long            lHandle;        // ���ھ��
		RECVCALLBACK    lpFunc;         // ��Ӧ�Ļص�����ָ��	
		GUINFO          guInfo;         // ���������
		long			nProtocolType;	// Э������ 0-UDP 1-TCP
	};
	
	struct MEDIA_DATA_INFO
	{
		unsigned int  packages;		    // �ܰ���
		unsigned int  packages_rate;    // ����
		unsigned int  lost;             // �ܶ���
		unsigned int      lostrate;     // ������
		unsigned int      rate;         // ����
		ULONG64   size;			        // �ܴ�С
	};
	
	struct DisInfo
	{
		int  nSwitch;	//0�ɹ���1:���ڱ������� 2:ʧ��  5:������������
		char szEncoderName[32];
		int  nWndNo;
	};
	struct TwAlarmInfo
	{
		char    szDisGuID[32];
		char	szTVID[32];
		char    szSepID[10];
		int     nMonitorNo;
		int		iRunType;	//  1 Ѳ�أ�2 Ⱥ��, 3 ����
		char	szRunName[32];
		int     nDisInfoNum;	//��ʾ��Ϣ����
		BOOL    bKeepOthers;
		DisInfo	disInfo[MAX_WINDOW_NUM];
	};
	struct AlarmInfo
	{
		char  szDomainid[32];
		char  szPuid[32];
		char  szGuid[32];              // GUID
		DOUBLE  dwLongitude;        // ����
		DOUBLE  dwLatitude;         // γ��
		DOUBLE  dwSpeed;				   //�ٶ�
		DOUBLE  dwVerifyLongitude;  // У�龭��
		DOUBLE  dwVerifyLatitude;   // У��γ��

		char  szDeviceName[64];        //�澯Դ�豸����
		char  szAlarmInfo[128];        //�澯����
		char  szRemarks[256];		   //�澯��ע��Ϣ
		DWORD   nAlarmType;			   //�澯����
		DWORD   dwAlarmTime;	       //�澯����ʱ��
		DWORD   dwParam1;              // ���Ӳ���
		TwAlarmInfo twInfo;
	};
	
	// Time-out interval, in milliseconds , ֻ����ST_ClientStartUp֮ǰ����
	CU_NET_API void   SetCmdTimeOut(DWORD pdwServerPara, DWORD dwMilliseconds);    
	CU_NET_API BOOL   GetMediaInfo(DWORD pdwServerPara, long lHandle, MEDIA_DATA_INFO* pInfo);
	
	// ͨ����Ϣ��������֪ͨ�ϲ�Ӧ�ó���(�����澯��Ϣ\��Ƶ��ֹ��Ϣ��)
	//ע�ᴰ�ں���Ϣ, ����������ͨ�ſ⺯��֮ǰ
	CU_NET_API BOOL  ClientStartUp(DWORD pdwServerPara, UINT nMessage, HWND hWnd);  
	//�������ע��
	CU_NET_API BOOL  ClientCleanUp(DWORD pdwServerPara);
	//��ȡ�澯��Ϣ
	CU_NET_API BOOL  GetAlarmInfo(DWORD pdwServerPara, AlarmInfo *pInfo); // ����м�¼�򷵻�TRUE,��������FALSE;
	
	// ��½���
	//��ȡ��¼��־
	CU_NET_API DWORD     GetLoginFlag(DWORD pdwServerPara);
	//�����¼
	CU_NET_API BOOL      RequestLogin(DWORD pdwServerPara, LPCTSTR lpszServerIP, UINT nPort,LPCTSTR lpszUserID, LPCTSTR lpszUserPwd, LPTSTR lpszLocalDomainID, LPTSTR lpRemoteIP, int& nSum);
	//������ռ��¼����
	CU_NET_API BOOL	   GrabLogin(DWORD pdwServerPara);
	//ע����¼
	CU_NET_API BOOL      RequestLogout(DWORD pdwServerPara);	
	//����ƽ̨�澯��Ϣ�ϴ�
	CU_NET_API HRESULT   SubNotifyInfo(DWORD pdwServerPara);
	//�û���������
	CU_NET_API HRESULT   ChangePassword(DWORD pdwServerPara, LPCTSTR lpszOldPwd, LPCTSTR lpszNewPwd);
	CU_NET_API HRESULT   QueryDeviceList(DWORD pdwServerPara, LPCTSTR lpszXmlFile);
	CU_NET_API HRESULT   GetCmuIp(DWORD pdwServerPara, LPCTSTR lpCmuIp, int nLen);
	//��ȡ��¼��ɣ�
	CU_NET_API HRESULT   GetDomainInfo(DWORD pdwServerPara, LPCTSTR lpDomainID, int nLen);
	//��ȡƽ̨CMU�汾��Ϣ
	CU_NET_API HRESULT   GetCMUVersionInfo(DWORD pdwServerPara, char* pszCmuVersion, int nLen);
	
	// ʵʱ��Ƶ���(2008/02/28)
	// ��ֹһ��ȫ�ֵ���������
	CU_NET_API void      CancelWaitting(DWORD pdwServerPara);                        // ��ֹһ��ȫ�ֵ���������
	// ����һ����Ƶ����ʵ��
	CU_NET_API LONG      CreateVideoInstance(DWORD pdwServerPara, CLIENTINFO client);  // ����һ����Ƶ����ʵ��
	// ����һ���������ӿڴ�������Ƶ����ʵ��
	CU_NET_API BOOL      CancelVideoInstance(DWORD pdwServerPara, long lHandle);        
	//��ȡ�����ӿڴ�������Ƶ����ʵ�е�״̬	
	CU_NET_API BOOL      GetMediaState(DWORD pdwServerPara, long lHandle);
	//�����ӿڴ�������Ƶ����ʵ�е�����	
	CU_NET_API BOOL      Reconnect(DWORD pdwServerPara, long lHandle);
	 
	typedef struct tag_mdu_route_info
	{
		int	 DomainType; //��0ʱ������Ϣ��Ч
		char szLocalMduIp[128];	//����MDU IP
		char szLocalMduId[32];	//����MDU ID
		UINT uLocalPort;		//����MDU port
		char szRemoteCsgIp[128];	//����CSG IP
		UINT uRemoteCsgPort;		//����CSG port
		char szRemoteMduIp[128];//����MDU IP
		char szRemoteMduId[32];	//����MDU ID
		UINT uRemoteMduPort;	//����MDU port
	}MDU_ROUTE_INFO;
	//��ȡ��Ƶ·����Ϣ
	CU_NET_API HRESULT   QueryPuRealRoute(DWORD pdwServerPara, GUINFO guInfo, MDU_ROUTE_INFO &mduInfo); 
	//��ȡCSG·����Ϣ
	CU_NET_API HRESULT   QueryCsgRoute(DWORD pdwServerPara, GUINFO guInfo, MDU_ROUTE_INFO &mduInfo); 
	//�˽ӿڲ���ʹ��
	CU_NET_API HRESULT   QueryPURoute(DWORD pdwServerPara, LPCTSTR lpszDomanID, LPCTSTR lpszPUID, LPTSTR lpszSevIp, UINT& uPort); 
	// ������CreateVideoInstance��������Ƶ����
	CU_NET_API HRESULT   RealVideoPreviewStart(DWORD pdwServerPara, long lHandle, MDU_ROUTE_INFO mduInfo);
	// ��ֹ��CreateVideoInstance��������Ƶ����
	CU_NET_API HRESULT   RealVideoPreviewStop(DWORD pdwServerPara, long lHandle);      // ��ֹ��Ƶ����
	
	// ǰ��I/O����
	CU_NET_API HRESULT   IoControl(DWORD pdwServerPara, GUINFO guInfo, BOOL bStatus, BOOL bReturn); //0-������ 1-���ȴ���Ӧ��������
	
	// ���Ļ�ȡ��ĳ���豸�澯
	CU_NET_API HRESULT   SubAlarmInfo(DWORD pdwServerPara, GUINFO guInfo, BOOL bFlag);
	
	// ��������
	struct BROADCAST_INFO
	{
		char szDomainID[32];
		char szPuID[32];
		char szGuID[32];
		char GUName[256];
		int nRouteFlag;
		MDU_ROUTE_INFO routeInfo;
	};
	//�˺�����������
	CU_NET_API BOOL      IsChartOpen(DWORD pdwServerPara);
	// ChartWithOne ���������Խ� nProtocolType 0-UDP, 1-TCP;
	CU_NET_API HRESULT   ChartWithOne(DWORD pdwServerPara, const GUINFO guInfo, const int nProtocolType, CLIENTINFO client);
	//������������
	CU_NET_API BOOL      SendVoiceData(DWORD pdwServerPara, const void* lpBuf, int nLen);                     // ������Ƶ����
	//ֹͣ����
	CU_NET_API HRESULT   StopChart(DWORD pdwServerPara);
	//��ʼ�����㲥
	CU_NET_API HRESULT   StartBroadcast(DWORD pdwServerPara, DWORD* dwBroadcastID, const int nProtocolType, 
									 char *szMduIp, int nPort, BROADCAST_INFO* pBroadInfo, int nCount);
	//���������㲥����
	CU_NET_API HRESULT   SendBroadcastData(DWORD dwBroadcastID, const void* lpBuf, int nLen);    
	//ֹͣ�����㲥
	CU_NET_API HRESULT   StopBroadcast(DWORD dwBroadcastID);  

	
	// �ֶ�Ҫ��ǰ��¼��;ץ��;����;����
	//����ǰ��¼��
	CU_NET_API HRESULT   RemoteStartRecord(DWORD pdwServerPara, GUINFO guInfo, int nTimesec);
	//����ǰ��ץ��
	CU_NET_API HRESULT   RemoteCapturePic(DWORD pdwServerPara, GUINFO guInfo);
	CU_NET_API HRESULT   RemoteRetCapPic(DWORD pdwServerPara, GUINFO guInfo, LPCTSTR lpsMSUID, char* pszFilePath, int pathLen);	//����ץ�ĳɹ����ȫ·��
	//����;����
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
	// �������Ķ�ʱ¼�����
	CU_NET_API HRESULT	SetMsuRecTimePlan(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuid, LPCTSTR lpszGuid, LPCTSTR lpszMsuId, const MsuRecTime *pMsuRecTime);
	CU_NET_API HRESULT	GetMsuRecTimePlan(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuid, LPCTSTR lpszGuid, LPCTSTR lpszMsuId, MsuRecTime *pMsuRecTime);
	
	struct ENCODER_NO
	{
		int	iNo;
		char szEncGuid[32];
		char szEncName[32];
		char szDomainid[32];	
	};
	//���ñ��������
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
	//�������ӿڲ���ʹ��
	CU_NET_API HRESULT	SetDecoderNo(DWORD pdwServerPara, DECODER_NO *pDecoderNo, int iCount);
	CU_NET_API HRESULT	GetDecoderNo(DWORD pdwServerPara, DECODER_NO *pDecoderNo, int iMax, int *pCount);
	//////////////////////////////////////////////////////////////////////////
	// ��������ѯ/���ò���
	// �汾��ѯ
	struct  PU_VERSION_INFO
	{
        char    version_number[32];    //�汾��
        char    version_author[16];    //��Ȩ����
        char    version_date[16];      //�汾����
	};
	//��ȡ�豸�汾��Ϣ
	CU_NET_API HRESULT  GetPuVersionInfo(DWORD pdwServerPara, const GUINFO& guInfo, PU_VERSION_INFO *pInfo);
	
	// ��������(δ����Ĳ���)
	struct  PU_BASICCFG_INFO
	{
		int coverType;                    // ���Ƿ�ʽ,0:�Զ�����,1:������ʾ.
		int prerecStatus;                 // Ԥ¼״̬,0:ֹͣ,1:����
		int switchFileTime;               // ¼���ļ��л�ʱ�� 10~30����
		int twoStreamFlag;                // ˫����ʹ�ܱ�־ 1: enable, 0: disable
		int reserveSpace;                 // ������С
		int manualRecordTime;             // �ֶ�¼��ʱ��
		int deleteSize;					  // ɾ�̴�С
	};
	CU_NET_API HRESULT  GetPuBasicCfgInfo(DWORD pdwServerPara, GUINFO guInfo, PU_BASICCFG_INFO* pInfo);
	CU_NET_API HRESULT  SetPuBasicCfgInfo(DWORD pdwServerPara, GUINFO guInfo, const PU_BASICCFG_INFO* pInfo);
	
	struct VEDIO_SWITCH_INFO
	{
// 		BOOL bFirst;		//��һͨ�� TRUE��ѡ��  FALSE��δѡ��
// 		BOOL bSecond;		//�ڶ�ͨ��
// 		BOOL bThird;		//����ͨ�� 
// 		BOOL bFourth;		//����ͨ�� 
		UINT uSelected;		//��λ��ʾ�ڼ�ͨ�� "00001101" ��ʾ;ѡ��������ͨ��(1��3��4)
		UINT uIntervalTime;	//�л�ʱ�� 2-10��
	};
	CU_NET_API HRESULT  GetVedioSwitchInfo(DWORD pdwServerPara, GUINFO guInfo, VEDIO_SWITCH_INFO* pInfo);
	CU_NET_API HRESULT  SetVedioSwitchInfo(DWORD pdwServerPara, GUINFO guInfo, const VEDIO_SWITCH_INFO* pInfo);

	CU_NET_API HRESULT  SetVedioMutexInfo(DWORD pdwServerPara, GUINFO guInfo, int nChannel);
	CU_NET_API HRESULT  GetVedioChannelSum(DWORD pdwServerPara, GUINFO guInfo, int& nChannels);
	// ǰ���豸ͼ��������
	struct IMAGEENCODEPARAM{
		int video_format;           	//��ʽѡ�� 0:PAL   1:NTSC
		int resolution;             	//�ֱ���,0:QCIF,1:CIF,2:HD1,3:D1
		int bitrate_type;           	//λ������,0:CBR,1:VBR
		int level;            		//����,200kbit3000kbit
		int frame_rate;			//ÿ������
		int Iframe_interval;      	//I����
		int prefer_frame;		//��������
		int Qp;					//����ϵ��
		int encode_type;		//0:����Ƶ��, 1:��Ƶ��, 2:��Ƶ��
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
	// ���ڲ���
	struct SERIALPORTPARAM
	{
		int data_bit;       //����λ,ֵ:5/6/7/8 Ĭ��8
		int stop_bit;       //ֹͣλ,ֵ:0/1/2 Ĭ��1
		int reserve[2];
		int verify_rule;    //��֤����,-1:��,0:��У��,1:żУ��, Ĭ��-1
		int baut_rate;      //������,Э���ض� Ĭ��9600
	};
	CU_NET_API HRESULT   GetPuSerialPort(DWORD pdwServerPara, const GUINFO& guInfo, int serialNo , SERIALPORTPARAM* lpParam);
	CU_NET_API HRESULT   SetPuSerialPort(DWORD pdwServerPara, const GUINFO& guInfo, int serialNo , SERIALPORTPARAM  param);
	
	//��̨���ø������
	struct PTZPARAM
	{
		int ptz_addr;       //��̨��ַ0 ~ 255
		int ptz_type;       //��̨��������.PELCO_D-1,PELCO_P-2,����-3,YAAN-4,santachi-5,santachi_in-6,����-9
		int serial_no;      //���ں�,ֵĬ��Ϊ1
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
	CU_NET_API HRESULT   DomeCtrlRequest(DWORD pdwServerPara, LPCTSTR lpszDomainID, LPCTSTR lpszGUID, DWORD *pCode, LPTSTR lpszCsgIp, UINT& uPort);	//pCode�����صĴ������
	CU_NET_API HRESULT   DomeControl(DWORD pdwServerPara, GUINFO guInfo, LPCTSTR lpszIP, UINT uPort, char* msgType, int nSpeed, const char* cmdType, const char* param);
	
	//�������ѯ LOGO����
	struct IMAGETEXTPARAM
	{
		BOOL bitmapTimeEnable;   // ʱ��
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
	// ǰ���豸ʱ�����
	CU_NET_API HRESULT   GetPuTime(DWORD pdwServerPara, GUINFO guInfo, SYSTEMTIME* lptime);
	CU_NET_API HRESULT   SetPuTime(DWORD pdwServerPara, GUINFO guInfo, SYSTEMTIME  time);
	// �����豸�ڵ�����
	typedef struct {
		COLORREF  HideAreaColor;	//��ɫ
		int HideAreaX;	//X����
		int HideAreaY;	//Y����
		int HideAreaWidth;	//����Ŀ��
		int HideAreaHeight;	//����ĸ߶�
	}HIDEIMAGEAREA_ITEM;
	struct HIDEIMAGEAREA
	{
		BOOL bEnable;	//�ڵ��Ƿ���Ч
		int  nNum;		//�������
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
	struct RECORD_INFO    // һ���ʱ���
	{
		BOOL   bEnable;
		RECORD_TIMESEG  timeSeg[4]; // 4��ʱ���	
	};

	typedef struct    //����ץ��
	{
		char nEnable;
		UINT uInterval;
		CAPTRUE_TIMESEG timeSeg[4];
	}CAPTRUE_INFO;


	CU_NET_API HRESULT   GetPuLocalStorageTask(DWORD pdwServerPara, GUINFO guInfo, RECORD_INFO* pRecInfo, int nCount);
	CU_NET_API HRESULT   SetPuLocalStorageTask(DWORD pdwServerPara, GUINFO guInfo, const RECORD_INFO* pRecInfo, int nCount);
	CU_NET_API HRESULT   GetPuTimeSnapTask(DWORD pdwServerPara, GUINFO guInfo, CAPTRUE_INFO* pRecInfo, int nCount);
	CU_NET_API HRESULT   SetPuTimeSnapTask(DWORD pdwServerPara, GUINFO guInfo, const CAPTRUE_INFO* pRecInfo, int nCount);
	
	// �ƶ����澯����
	struct MOTIONDETECTION_INFO{
		int  moveGuardFlag;        // ��/����
		int  moveEnable;           // ����ʹ��
		int  sensitiveLevel;       // ������,1:1��,...,9:9��
		int  alarmIntervalTime;    // �����ʱ��
		int  jointRecordTime;      // ����¼���ʱ��
		int  jointOutputTime;      // ���������ʱ��
		int  beepOutputTime;       // ����������������ʱ��
		int  beepOutputEnable;     // ���������ʹ��
		int  jointSnapEnableCh;    // ����ץ��ʹ��
		int  jointRecordEnableCh;  // ����¼��ʹ��
		int  jointOutputEnableCh;  // �������ʹ��
		char motionarea[128];           // �������(�Զ����ʽ)
		MOTION_TIMESEG  timeSeg[4];
	};
	CU_NET_API HRESULT   GetPuMotionDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, MOTIONDETECTION_INFO* pMotionInfo);
	CU_NET_API HRESULT   SetPuMotionDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, const MOTIONDETECTION_INFO*  pMotionInfo);
	
	// ��Ƶ��ʧ�澯
	struct LOSEDETECTION_INFO{
		int  loseGuardFlag;        // ��/����
		int  loseEnable;           // ����ʹ��
		int  alarmIntervalTime;    // �����ʱ��
		int  jointRecordTime;      // ����¼���ʱ��
		int  jointOutputTime;      // ���������ʱ��
		int  beepOutputTime;       // ����������������ʱ��
		int  beepOutputEnable;     // ���������ʹ��
		int  jointSnapEnableCh;    // ����ץ��ʹ��
		int  jointRecordEnableCh;  // ����¼��ʹ��
		int  jointOutputEnableCh;  // �������ʹ��
	};
	CU_NET_API HRESULT   GetPuLoseDetectionCfg(DWORD pdwServerPara, GUINFO guInfo,  LOSEDETECTION_INFO* pLoseInfo);
	CU_NET_API HRESULT   SetPuLoseDetectionCfg(DWORD pdwServerPara, GUINFO guInfo,  const LOSEDETECTION_INFO*  pLoseInfo);
	
	// I/O�澯
	struct PROBERDETECTION_INFO{
		int  proberType;           // ̽ͷ���� 0:����  1:����
		int  proberGuardFlag;      // ��/����
		int  proberEnable;         // ����ʹ��
		int  alarmIntervalTime;    // �����ʱ��
		int  jointRecordTime;      // ����¼���ʱ��
		int  jointOutputTime;      // ���������ʱ��
		int  beepOutputTime;       // ����������������ʱ��
		int  beepOutputEnable;     // ���������ʹ��
		int  jointSnapEnableCh;    // ����ץ��ʹ��
		int  jointRecordEnableCh;  // ����¼��ʹ��
		int  jointOutputEnableCh;  // �������ʹ��
		PROBER_TIMESEG timeSeg[4];
	};
	CU_NET_API HRESULT   GetPuProberDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, PROBERDETECTION_INFO* pProberInfo);
	CU_NET_API HRESULT   SetPuProberDetectionCfg(DWORD pdwServerPara, GUINFO guInfo, int nWeekDay, const PROBERDETECTION_INFO*  pProberInfo);
	
	// ����������ӿ�
	// �������ֶ��л�
	CU_NET_API HRESULT   DecoderSwitch(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuidDec, LPCTSTR lpszGuidDec, LPCTSTR lpszPuidEnc, LPCTSTR lpszGuidEnc);
	
	// �ָ���������
	CU_NET_API HRESULT   RestorePuConfig(DWORD pdwServerPara, GUINFO guInfo);
	// VOD�ӿ�
	struct VODSERVER_INFO{
		char    szDomainID[32];
		char	szVodName[64];
		char	szVodIp[16];
		char	szVodID[32];
		unsigned short  nVodPort;
	};
	CU_NET_API HRESULT   VodServerQuery(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszGuid, int *pCount, VODSERVER_INFO *pVodServerInfo);
	// MSU�ӿ�
	CU_NET_API HRESULT   MsuManualRecordReq(DWORD pdwServerPara, LPCTSTR lpszDomainId, LPCTSTR lpszPuid, LPCTSTR lpszGuid, int nTime, LPCTSTR lpszMsuName, LPCTSTR lpszMsuIp, LPCTSTR lpszMsuID);
	
	//pu�ļ���ѯ nQueryType 0-¼���ļ� 1-ͼƬ�ļ� nQueryType=1ʱnType��Ч
	struct GuFileInfo
	{
		//@{"FileName:/record/hd0/2008-02-28/guid12345678/09-22-00.dat"}
		char file[256];
		int type;	//@{Bit Set}
		int size;	//@{Total Size Of The File}
	} ;
	CU_NET_API HRESULT QueryGuFileLists(DWORD pdwServerPara, GUINFO guInfo, int nQueryType, int nType, SYSTEMTIME* pSysStartTime, SYSTEMTIME* pSysEndTime, GuFileInfo *pFileList, int nMaxCount, int *pCount);
	//��ѯ�豸IP��Ϣ
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
		char szCodeRate[10];	//����
		char szframeRate[10];	//֡��
	};
	//��ȡ�豸�˵�ʵ��������Ϣ
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
		char enableFlag;//0:������;  1:����.
		char conType;//0:UDP  1: TCP
		BOOL bSmoothFlag;
	};
	//��ȡ�豸�˵�ƽ̨������Ϣ
	CU_NET_API HRESULT GetPlatformInfo(DWORD pdwServerPara, GUINFO guInfo, PlatformInfo* pInfo);
	//�����豸�˵�ƽ̨������Ϣ
	CU_NET_API HRESULT SetPlatformInfo(DWORD pdwServerPara, GUINFO guInfo, PlatformInfo pInfo);
	//��ȡϵͳʱ��
	CU_NET_API HRESULT GetSystemTime(DWORD pdwServerPara, char* pTime, int nMaxLen);
	//У��ϵͳʱ��
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
	//��ȡ�豸��PPPOE��Ϣ
	CU_NET_API HRESULT GetPPPOEInfo(DWORD pdwServerPara, GUINFO guInfo, PPPOEInfo* pInfo);
	//�����豸��PPPOE��Ϣ
	CU_NET_API HRESULT SetPPPOEInfo(DWORD pdwServerPara, GUINFO guInfo, PPPOEInfo pInfo);

	//���������豸
	CU_NET_API HRESULT RestartPuDevice(DWORD pdwServerPara, GUINFO guInfo);
	//�ָ��豸�˵�Ĭ��ֵ
	CU_NET_API HRESULT SetPuDeviceDefult(DWORD pdwServerPara, GUINFO guInfo);
	//�ָ��豸�˵ĳ�������
	CU_NET_API HRESULT RecovePuDeviceFactory(DWORD pdwServerPara, GUINFO guInfo);
	//Ϊ�豸�ṩ�����ļ�
	struct UPDATE_FILE_INFO
	{
		char szUser[32];
		char szPwd[32];
		char szPath[256];
		char szName[128];
		int  nSize;
	};
	CU_NET_API HRESULT SetPuUpdateFile(DWORD pdwServerPara, GUINFO guInfo, UPDATE_FILE_INFO fileInfo);
	//��ȡGPS�켣��Ϣ
	struct GPS_TRACK_INFO 
	{
		char szTime[30];	
		char szLongitude[15];
		char szLatitude[15];
		char szSpeed[10];
	};
	//strStart, strEnd��ʽ: YYYYMMDD-HH:MM:SS
	//�����λ��, �㿴�������㷵�ص����һ����¼,������������ҷ���һ��ʲôֵ�����ǱߵĶ�λ��.
	//�㷵�صļ�¼��ʽ:	RECORD;RECORD;...;RECORD;
	//ÿ��RECODE���ݰ���:ʱ��,����,γ��,�ٶ�...
	CU_NET_API HRESULT GetGPSTrackInfo(DWORD pdwServerPara, GUINFO guInfo, LPCSTR strStart, LPCSTR strEnd,
		GPS_TRACK_INFO *pTrackInfo, int& nInfoNum, int nPos);
	//////////////////////////////////////////////////////////////////////////
	// ����ǽAPI
	// ���õ���ǽ
	//////////////////////////////////////////////////////////////////////////
	struct WINDOW_INFO	//������Ϣ
	{
		int     nMoniterNo;			//���������ĸ�������	�������κμ�������0;
		int		nWindNo;			//�������
		char	szDisplayName[32];
		char	szDisplayGUID[32];
		BOOL	bFullScreen;		//�Ƿ���ȫ��״̬
		BOOL	bWinLock;			//�Ƿ�������״̬
		BOOL	bPlaySound;			//�����Ƿ���
		UINT    uSwitchType;		//�л����ͣ���Чֵ��0��������1��Ѳ�أ�2��Ⱥ�飺3��
		BOOL	bState;
		char    szEncoderName[128];//������
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
	struct SEP_SCREEN_INFO	//������Ϣ
	{
		char	szSepID[10];	//�������ַ���ģʽ
		int		nWinNum;
		RECT   rectWnd[MAX_WINDOW_NUM];
	};
	struct MONITOR_INFO{
		int     iMonterNo;		//���������
		int		index;
		int		iLeft;			//ȷ������������ĵ��ĸ��߽�ֵ
		int		iTop;			//..2.
		int		iRight;			//..3.
		int		iBottom;		//..4.
		char	szTVID[32];				//��������ǽID		
		char	szDisplayName[32];		//��ʾͨ����
		char	szDisplayGUID[32];		//��ʾGUID�����ģʽ�ǰ���һ���	
		SEP_SCREEN_INFO  sepInfo;		//ָ�������Ϣ���޷�ֱ��ָ�������Ϣ���������Ϣ����ˢ�¡��ᵼ���ض��������⣩
		WINDOW_INFO*	 pWinInfo[MAX_WINDOW_NUM];	//���ݷ�����Ϣ��̬����������Ϣ
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
		MONITOR_INFO*  pMonitorInfo[MAX_MONITOR_NUM];	//���ݼ�����������̬������������Ϣ
	};
	//����Ѳ��
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
	//�˺�������ʹ��
	CU_NET_API HRESULT   TourConfigSet(DWORD pdwServerPara, TOURCONFIG_INFO *pTourInfo);

	//��ȡID
	CU_NET_API HRESULT   GetTVID(DWORD pdwServerPara, LPCTSTR lpDomain, LPCTSTR lpAreaID, LPCTSTR lpName, LPCTSTR lpID);
	CU_NET_API HRESULT   GetTourID(DWORD pdwServerPara, LPCTSTR lpDomain, LPCTSTR lpAreaID, LPCTSTR lpName, int iTourNo, BOOL bAutoJump, LPCTSTR lpID);
	CU_NET_API HRESULT   GetGroupID(DWORD pdwServerPara, LPCTSTR lpDomain, LPCTSTR lpAreaID, LPCTSTR lpName, LPCTSTR lpID, int iGroupNo);
	//ɾ������ǽ\Ѳ��\Ⱥ���б�	iModifyType 0-����ǽ 1-Ѳ�� 2-Ⱥ��
	CU_NET_API HRESULT   DeleteConfig(DWORD pdwServerPara, int iDeleteType, LPCTSTR lpID);
	//��ѯ����ǽ\Ѳ��\Ⱥ���б� iQueryType 0-����ǽ 1-Ѳ�� 2-Ⱥ��
	struct QUERY_INFO{
		char	szName[32];
		char	szID[32];
		char	szNo[32];
		char    szTVID[32];	//���������ֶΣ�ֻ����Ⱥ����Ϣ����Ч
		char    szTVName[32];
		int     nMonitorNum;
	};
	CU_NET_API HRESULT   QueryList(DWORD pdwServerPara, int iQueryType, LPCTSTR lpDomainID, LPCTSTR lpAreaID, QUERY_INFO *pInfo, int *pCount);
	//��ѯ����ǽ��ϸ����
	CU_NET_API HRESULT   QueryTWConfig(DWORD pdwServerPara, LPCTSTR lpTVID, int& nSplitX, int& nSplitY, int& nMonNum, MONITOR_INFO *pMonInfo);
	//��ѯ����ǽ������Ϣ
	CU_NET_API HRESULT   QuerySepScreenInfo(DWORD pdwServerPara, LPCTSTR lpScrModeID, SEP_SCREEN_INFO *pSepScrInfo);
	//��ѯ����ǽ����ģʽ
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
	//��ѯѲ����ϸ����
	CU_NET_API HRESULT   QueryTourConfig(DWORD pdwServerPara, LPCTSTR lpTourID, TOURCONFIG_INFO *pTourConfig);
	//Ⱥ��������Ϣ
#define MAX_GROUPSTEP_NUM	128
#define MAX_GROUPDECODER_NUM	128
	struct GROUP_WND{ //Ⱥ�鲽�ڣ�����ǽ����һ���������е�һ��������Ϣ
		int		nWndNo;
		char    szDomainID[10];
		char	szEncGuid[32];
		char	szEncName[32];
	};	
	struct STEP_DETAILED_INFO{
		int		nMonitorNo;
		char	szSepModeID[32];	//����ģʽID
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
	//��ѯȺ������
	CU_NET_API HRESULT   QueryGroupConfig(DWORD pdwServerPara, LPCTSTR lpGroupID, GROUPCONFIG_INFO *pGroupConfig);
	//��ѯȺ�鲽��Ϣ	
	CU_NET_API HRESULT   QueryGroupStepInfo(DWORD pdwServerPara, LPCTSTR lpStepID, GROUPSTEP_INFO *pGroupStep);
	//�����л�
	CU_NET_API HRESULT   StepRun(DWORD pdwServerPara, LPCTSTR lpTVID, LPCTSTR lpEncoderGUID, LPCTSTR lpDisplayGUID, LPCTSTR lpModeID, int nWndNo);
	//ֹͣ����		   
	CU_NET_API HRESULT   TvDisStop(DWORD pdwServerPara, LPCTSTR lpTVID, char* szDisGUID, int nMonNo, int nWndNo);
	//Ѳ���л�/����Ѳ��ֹͣ/��ͨ��Ѳ��ֹͣ iType(0-��ͨ��Ѳ��ֹͣ 1-����)
	CU_NET_API HRESULT   TourRun(DWORD pdwServerPara, LPCTSTR lpTourID, LPCTSTR lpTVID, LPCTSTR lpDisplayGUID, LPCTSTR lpModeID, int iWndNo);
	CU_NET_API HRESULT   TourRunAllStop(DWORD pdwServerPara, LPCTSTR lpTourID);
	//��ͨ��ֹͣѲ��/Ⱥ��
	CU_NET_API HRESULT   CHRunStop(DWORD pdwServerPara, LPCTSTR lpTVID, char* szDisGUID, char* szDecoderGUID, int nMonNo, int nWndNo);
	//Ⱥ���л�/ֹͣ/��ͣ/�ָ� iType(0-ֹͣ 1-���� 2-��ͣ 3-�ָ�)
	CU_NET_API HRESULT   GroupRun(DWORD pdwServerPara, int iType, LPCTSTR lpGroupID, LPCTSTR lpTVID);
	//����������ȫ��/ȡ��ȫ��
	CU_NET_API HRESULT   TWWindowIsFull(DWORD pdwServerPara, BOOL bFull, char* szDisGUID, int nMonNo, int nWndNo);
	//��������������
	CU_NET_API HRESULT   TWAudioPlay(DWORD pdwServerPara, BOOL bAudio, char* szDisGUID, int nMonNo, int nWndNo);
	//��ȡ����ǽĳ�����ڵ�״̬��Ϣ
struct TV_WALL_STATE
{
	char szWndModeID[32];
	int  nWIndNum;
	WINDOW_INFO WndInfo[MAX_WINDOW_NUM];
};
	CU_NET_API HRESULT   GetTWWindowState(DWORD pdwServerPara, TV_WALL_STATE* pTvWallState, LPCTSTR lpPuid, LPCTSTR lpDisplayid, int iWindowNo = 0);
	//������Ĭ������
	CU_NET_API HRESULT   TWDefaultConnect(DWORD pdwServerPara, char* szDecoderGUID, char* szDisGUID, int nMonNo, int nWndNo);
    //�����������л�����/ȡ������
    CU_NET_API HRESULT   TWWindowLock(DWORD pdwServerPara, BOOL bLock, char* szDisGUID, int nMonNo, int nWndNo);
    //Ⱥ�顢Ѳ������״̬��ѯ //1 Ѳ�أ�2 Ⱥ��
    CU_NET_API HRESULT   QueryRunStatus(DWORD pdwServerPara, int iType, LPCTSTR lpszID, BOOL *bStatus, LPCTSTR lpTVID = "");
	
	//���󵥲��л�
	CU_NET_API HRESULT   MatrixStepRun(DWORD pdwServerPara, LPCTSTR lpPuid, int iCameraNo, int iMonitorNo, LPCTSTR lpGuid);
	//����Ѳ���л�
	CU_NET_API HRESULT   MatrixTourRun(DWORD pdwServerPara, LPCTSTR lpPuid, int iMonitorNo, int iTourNo, LPCTSTR lpGuid);
	//����Ⱥ���л�
	CU_NET_API HRESULT   MatrixGroupRun(DWORD pdwServerPara, LPCTSTR lpPuid, int iGroupNo, LPCTSTR lpGuid);
	
	//��ѯ��ҵ��Ϣ
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
#define LOOKOVER_REALTIME_VIDEO 0//0-�鿴ʵʱ��Ƶ��1-�鿴��ʷ��Ƶ��2-�鿴������Ϣ��3-ȷ�ϡ�
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
	//��ѯ�豸�Ŀ������ļ��б�
	CU_NET_API HRESULT   QueryUpdateFile(DWORD pdwServerPara, UPDATE_FILE_INFO* pFileInfo, GUINFO guInfo, int nMax, int& nReCount);

	//��ؽӿ�
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

