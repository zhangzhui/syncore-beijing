#ifndef __PLAYLIB_H__
#define __PLAYLIB_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 自动为使用MFC的dll工程增加导出函数声明
#ifdef _WINDLL
#define PLAYLIB_SDK_EXPORTS
#endif

#ifdef __cplusplus
#define C_STYLE extern "C" 
#else
#define C_STYLE
#endif

// 导出所有接口函数.
// 包含此头文件的dll工程需要定义预编译宏
#ifdef PLAYLIB_SDK_EXPORTS
#define PLAYLIB_SDK_API C_STYLE __declspec(dllexport)
#else 
#define PLAYLIB_SDK_API C_STYLE __declspec(dllimport)
#endif

// 定义函数调用方式.
#define CALL_STYLE _stdcall

typedef long PSDKOBJECT;

//播放控制
#define PLAY_MODE_NORMAL			0x0001
#define PLAY_MODE_STOP				0x0002
#define PLAY_MODE_PAUSE				0x0003
#define PLAY_MODE_SLOW				0x0004
#define PLAY_MODE_SLOW4				0x0005	
#define PLAY_MODE_SLOW8				0x0006
#define PLAY_MODE_SLOW16			0x0007	
#define PLAY_MODE_FAST_FORWARD2		0x0010
#define PLAY_MODE_FAST_FORWARD4		0x0011
#define PLAY_MODE_FAST_FORWARD8		0x0012
#define PLAY_MODE_FAST_FORWARD16	0x0013
#define PLAY_MODE_FAST_FORWARD32	0x0014
#define PLAY_MODE_FAST_BACKWARD2	0x0020
#define PLAY_MODE_FAST_BACKWARD4	0x0021
#define PLAY_MODE_FAST_BACKWARD8	0x0022
#define PLAY_MODE_FAST_BACKWARD16	0x0023
#define PLAY_MODE_FAST_BACKWARD32	0x0024
#define PLAY_MODE_SINGLE_FRAME		0x0030

//常量定义
//厂商代码
const long TP_PLAY_SDK     =		0x50543030;
const long SANTACHI_PLAY_SDK =      0x54533030;	
const long HB_PLAY_SDK     =		0x42483030;
const long HK8016_PLAY_SDK =		0x4b483030;
const long HK8116_PLAY_SDK =		0x4b483130;
const long HK9000_PLAY_SDK =		0x4b483230;
const long DH_PLAY_SDK     =		0x48443030;
#define JB_PLAY_SDK				    0x424A3030                               //add by wenqinglin on 2010-11-30
const long LC_PLAY_SDK     =        0x434c3030;                          //add by fengzx 
//{ "00TP", "00HK", "01HK", "00DH", "00HB", "00JB", "02HK"};
//
 typedef int ( CALLBACK* DUAL_SPEAK_CALLBACK)(int size, const char* data, DWORD dwUser);
 typedef long( CALLBACK* DRAW_FUN_CALLBACK) ( long hHandle, HDC hDC, void* pUser);

typedef struct __osd_info_t
{
	char font[24];
	int font_width;
	int font_height;
	unsigned char osd_color_red;		//0-255
	unsigned char osd_color_green;		//0-255
	unsigned char osd_color_blue;		//0-255
	RECT osd_rect;
	
	char osd_string[128];
}osd_info_t;
typedef struct{
	int iRate;
	int iWidth;
	int iFormat;
	int iAmr_mode;
	int iAmr_format;
}AudioTalkConfig_t;


typedef struct __dec_data_t
{
	int		nType;		//数据类型
	unsigned char *pBuf;//数据
	int		nSize;		//数据大小
	int		nWidth;		//画面宽。如果是音频数据则表示采样频率(一般为固值8000Hz)；
	int		nHeight;	//画面高。如果是音频数据则为0；
	int     nFrameRate; //编码时产生的图像帧率,音频时表示采样位宽16
	unsigned long lStamp; //时标信息，单位毫秒。
	
}dec_data_t;
//************************************
// PSDKOBJECT lpSDKObject ------> CreatePlaySDKObject 的返回值
// long player_id ------>player_createPlayInstance 的返回值
// net stream播放流程 CreatePlaySDKObject -> player_createPlayInstance -> player_setPlayWnd ->player_startPlay ->player_inputNetFrame
// file播放流程 CreatePlaySDKObject -> player_createPlayInstance -> player_setPlayWnd ->player_openPlayFile -> player_startPlay
//************************************


// 创建SDK对象实例,失败返回0
PLAYLIB_SDK_API BOOL CALL_STYLE CreatePlaySDKObject();
// 注销SDK对象实例
PLAYLIB_SDK_API BOOL CALL_STYLE DestroyPlaySDKObject();


//************************************
// 网络，本地
//************************************
// 创建播放实例,返回player_id
// Parameter: int play_type---------
// 播放类型
#define PLAY_UNKNOW_TYPE     -1    //no file
#define PLAY_LOCALFILE_TYPE  0     //local file
#define PLAY_NETFILE_TYPE    1     //net file
#define PLAY_NETSTREAM_TYPE  2     //net stream
#define PLAY_DUALTALK_TYPE	 3	   //dual talk
// Parameter: int nContext----------附加参数
PLAYLIB_SDK_API long CALL_STYLE player_createPlayInstance(const int nCompanyCode,int play_type,int nContext);
PLAYLIB_SDK_API int CALL_STYLE player_destroyPlayInstance(long player_id);
// Play Wnd
PLAYLIB_SDK_API int CALL_STYLE player_setPlayWnd(long player_id, HWND hwnd);
PLAYLIB_SDK_API HWND CALL_STYLE player_getPlayWnd(long player_id);
// Play
PLAYLIB_SDK_API int CALL_STYLE player_startPlay(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_stopPlay(long player_id);
// open Sound
PLAYLIB_SDK_API int CALL_STYLE player_openSound(long player_id);
PLAYLIB_SDK_API int CALL_STYLE  player_closeSound(long player_id);



//############# file, net file, net stream #############
// localrecord
PLAYLIB_SDK_API int CALL_STYLE player_startlocalrecord(long player_id, char *recordfile_name);
PLAYLIB_SDK_API int CALL_STYLE player_stoplocalrecord(long player_id);
// OSD
PLAYLIB_SDK_API int CALL_STYLE player_setOsdString(long player_id, int index, osd_info_t  *osd_info);
PLAYLIB_SDK_API int CALL_STYLE player_removeOsdstring(long player_id, int index);
// capturePicture
PLAYLIB_SDK_API int CALL_STYLE player_capturePicture(long player_id, char *file_name);
PLAYLIB_SDK_API int CALL_STYLE player_capturePictureBuf(long player_id, int *pLen, char *buf);
// SDKVesion
PLAYLIB_SDK_API int CALL_STYLE player_getSDKVesion(long player_id, char *ver_string);
// LastError
PLAYLIB_SDK_API int CALL_STYLE player_getLastError(long player_id, char *err_string);




//############# net file, net stream #############
// input Frame
PLAYLIB_SDK_API int CALL_STYLE player_inputNetFrame(long player_id, char *buf, int size);
// Buf Num
PLAYLIB_SDK_API int CALL_STYLE player_setNetPlayBufNum(long player_id, int num);
PLAYLIB_SDK_API int CALL_STYLE player_getNetPlayBufNum(long player_id);
// Frame Rate
PLAYLIB_SDK_API int CALL_STYLE player_getFrameRate(long player_id, BOOL bFrame_rate);
// BitRate
PLAYLIB_SDK_API int CALL_STYLE player_getBitRate(long player_id, BOOL bBit_rate);
// List Frame Num
PLAYLIB_SDK_API int CALL_STYLE player_getListFrameNum(long player_id);
// Dual Talk
PLAYLIB_SDK_API int CALL_STYLE player_startDualTalk(long player_id, AudioTalkConfig_t *pAudioTalk = NULL);
PLAYLIB_SDK_API int CALL_STYLE player_stopDualTalk(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_registerSetDualCallback(long player_id, DUAL_SPEAK_CALLBACK callback, DWORD dwUser);


//############# file #############
PLAYLIB_SDK_API int CALL_STYLE player_openPlayFile(long player_id, char *file_name);
PLAYLIB_SDK_API int CALL_STYLE player_closePlayFile(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_getPlayFileTotalSize(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_getPlayFileTotalTime(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_getCurPlayFilePos(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_setCurPlayFilePos(long player_id, int pos);
PLAYLIB_SDK_API int CALL_STYLE player_getCurPlayedTime(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_setCurPlayedTime(long player_id, int len);




//############# Volume #############
PLAYLIB_SDK_API int CALL_STYLE player_setPlayVolume(long player_id,int volume);
PLAYLIB_SDK_API int CALL_STYLE player_getPlayVolume(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_setMute(long player_id,BOOL bMute);
PLAYLIB_SDK_API BOOL CALL_STYLE player_getMute(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_setMicPlayVolume(long player_id,int volume);
PLAYLIB_SDK_API int CALL_STYLE player_getMicPlayVolume(long player_id);
PLAYLIB_SDK_API int CALL_STYLE player_setMicMute(long player_id,BOOL bMute);
PLAYLIB_SDK_API BOOL CALL_STYLE player_getMicMute(long player_id);




//############# other #############
// 播放模式（本地，远程点播 快进。。。）
PLAYLIB_SDK_API int CALL_STYLE player_setPlayMode(long player_id, int play_mode);
PLAYLIB_SDK_API int CALL_STYLE player_getPlayMode(long player_id);

// （点播）
PLAYLIB_SDK_API int CALL_STYLE player_getCurrentFrameNo(long player_id); 

//剪裁
PLAYLIB_SDK_API int CALL_STYLE player_adjustViewArea(long player_id, int left, int right, int top, int bottom);
PLAYLIB_SDK_API int CALL_STYLE player_registerDrawFun(long player_id, DRAW_FUN_CALLBACK DrawFun, void* pUser);


PLAYLIB_SDK_API int CALL_STYLE player_setPlayPicSize(long player_id, int width, int height);
PLAYLIB_SDK_API int CALL_STYLE player_getPlayPicSize(long player_id, int *width, int *height);



//bEnable = 0, 实时
//bEnable = 1, iMax = 0，库将按帧数据的时间放，缓冲的帧要由你来控制，这也是net_file模式。
//bEnable = 1, iMax（150～5000）,iMax为缓冲多久的帧数据
PLAYLIB_SDK_API int CALL_STYLE  player_setCushionRange(long player_id, BOOL bEnable, int iMin , int iMax);



// typedef struct{ 
// 	long nWidth; // 画面宽，单位为像素，如果是音频数据则为0
// 	long nHeight; // 画面高，单位为像素，如果是音频数据则为0
// 	long nStamp; // 时标信息，单位毫秒
// 	long nType; //数据类型
// 	long nFrameRate;// 编码时产生的图像帧率
// }FRAME_INFO;
//typedef int (CALLBACK *DECODE_CALLBACK) (long hHandle, char *pData, long lSize, FRAME_INFO *pInfo, DWORD dwUser);
typedef long (CALLBACK *DECODE_CALLBACK)(long hHandle, dec_data_t* dec_data, DWORD dwUser); 
PLAYLIB_SDK_API int CALL_STYLE player_registerDecCallback(unsigned long player_id, DECODE_CALLBACK DecCallback, DWORD dwUser);

#define RE_NORMAL			0
#define RE_MIRROR_LEFTRIGHT	1
#define RE_MIRROR_UPDOWN	2
PLAYLIB_SDK_API int CALL_STYLE player_setRenderEffect(unsigned long player_id, int type);
PLAYLIB_SDK_API int CALL_STYLE player_renderActualProportion(unsigned long player_id, int enable); 



#endif
