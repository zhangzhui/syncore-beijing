#ifndef __sdkPlayer_h__
#define __sdkPlayer_h__

#ifdef PLAY_EXPORTS
#define PLAY_API __declspec(dllexport)
#else
#define PLAY_API __declspec(dllimport)
#endif
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
//audio setting
#define MAX_BUF_NUM					100
#define BIT_PER_SAMPLE				16
#define HI3510_DATABLOCK_SIZE		(1024)
#define PLAY_AUDIO_SAMPLE_POOR		8000
#define HI3510_TALK_DARABLOCK_SIZE	80
typedef struct{ 
	long nWidth; // 画面宽，单位为像素，如果是音频数据则为0
	long nHeight; // 画面高，单位为像素，如果是音频数据则为0
	long nStamp; // 时标信息，单位毫秒
	long nType; //数据类型
	long nFrameRate;// 编码时产生的图像帧率
}FRAME_INFO;
//音量
#define VOLUM_MIN	0
#define VOLUM_MAX	65535
//播放类型
#define PLAY_UNKNOW_TYPE     -1    //no file
#define PLAY_LOCALFILE_TYPE  0     //local file
#define PLAY_NETFILE_TYPE    1     //net file
#define PLAY_NETSTREAM_TYPE  2     //net stream
#define PLAY_DUALTALK_TYPE	 3	   //dual talk

//声音控制类型
#define DST_SPEAKERS		0	//主音量  
#define SRC_WAVEOUT			1   //波形
#define SRC_SYNTHESIZER		2	//软件合成器
#define SRC_COMPACTDISC     3	//CD音量
#define SRC_MICROPHONE		4   //麦克风

#define MAX_SET_OSD_NUM		5	//最多可设置OSD的数目

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

typedef int (CALLBACK* DUAL_SPEAK_CALLBACK)(int size, const char* data, DWORD dwUser);
typedef long(CALLBACK* DRAW_FUN_CALLBACK)( long hHandle, HDC hDC, void* pUser);
typedef long(CALLBACK* DecDataFun)( long hHandle, dec_data_t* dec_data, DWORD dwUser);

PLAY_API int _stdcall Player_initPlayLib(void);
PLAY_API int _stdcall Player_deinitPlayLib(void);

PLAY_API unsigned long _stdcall Player_createPlayInstance( int play_type); 
PLAY_API int _stdcall Player_destroyPlayInstance(unsigned long player_id);

PLAY_API int _stdcall Player_setNetPlayBufNum(unsigned long player_id, int num);
PLAY_API int _stdcall Player_setPlayWnd(unsigned long player_id, HWND hwnd);
PLAY_API int _stdcall Player_setPlayPicSize(unsigned long player_id, int width, int height);
PLAY_API int _stdcall Player_getNetPlayBufNum(unsigned long player_id);
PLAY_API HWND _stdcall Player_getPlayWnd(unsigned long player_id);
PLAY_API int _stdcall Player_getPlayPicSize(unsigned long player_id, int *width, int *height);

PLAY_API int _stdcall Player_openPlayFile(unsigned long player_id, char *file_name);
PLAY_API int _stdcall Player_closePlayFile(unsigned long player_id);
PLAY_API int _stdcall Player_getPlayFileTotalSize(unsigned long player_id);
PLAY_API int _stdcall Player_getPlayFileTotalTime(unsigned long player_id);
PLAY_API int _stdcall Player_getCurPlayFilePos(unsigned long player_id);
PLAY_API int _stdcall Player_setCurPlayFilePos(unsigned long player_id, int pos);
PLAY_API int _stdcall Player_getCurPlayedTime(unsigned long player_id);
PLAY_API int _stdcall Player_setCurPlayedTime(unsigned long player_id, int len);

PLAY_API int _stdcall Player_getFrameRate(unsigned long player_id, BOOL bFrame_rate);
PLAY_API int _stdcall Player_getBitRate(unsigned long player_id, BOOL bBit_rate);
PLAY_API int _stdcall Player_startPlay(unsigned long player_id);
PLAY_API int _stdcall Player_stopPlay(unsigned long player_id);
PLAY_API int _stdcall Player_setPlayMode(unsigned long player_id, int play_mode);
PLAY_API int _stdcall Player_getPlayMode(unsigned long player_id);
PLAY_API int _stdcall Player_startlocalrecord(unsigned long player_id, char *recordfile_name);
PLAY_API int _stdcall Player_stoplocalrecord(unsigned long player_id);

PLAY_API int _stdcall Player_inputNetFrame(unsigned long player_id, char *buf, int size);
PLAY_API int _stdcall Player_getListFrameNum(unsigned long player_id);
PLAY_API int _stdcall Player_openSound(unsigned long player_id);
PLAY_API int _stdcall  Player_closeSound(unsigned long player_id);
PLAY_API int _stdcall Player_setPlayVolume(int volume);
PLAY_API int _stdcall Player_getPlayVolume();
PLAY_API int _stdcall Player_setMute(BOOL bMute);
PLAY_API BOOL _stdcall Player_getMute();
PLAY_API int _stdcall Player_setMicPlayVolume(int volume);
PLAY_API int _stdcall Player_getMicPlayVolume();
PLAY_API int _stdcall Player_setMicMute(BOOL bMute);
PLAY_API BOOL _stdcall Player_getMicMute();

PLAY_API int _stdcall Player_setOsdString(unsigned long player_id, int index, osd_info_t *p_osd_info);
PLAY_API int _stdcall Player_removeOsdstring(unsigned long player_id, int index);

PLAY_API int _stdcall Player_capturePicture(unsigned long player_id, char *file_name);
PLAY_API int _stdcall Player_capturePictureBuf(unsigned long player_id, int *pLen, char *buf);
PLAY_API int _stdcall Player_getSDKVesion(char *ver_string);
PLAY_API int _stdcall Player_getLastError(unsigned long player_id, char *err_string);

PLAY_API int _stdcall Player_startDualTalk(unsigned long player_id, AudioTalkConfig_t *pAudioTalk = NULL);
PLAY_API int _stdcall Player_stopDualTalk(unsigned long player_id);

PLAY_API int _stdcall Player_getCurrentFrameNo(unsigned long player_id); 
PLAY_API int _stdcall Player_adjustViewArea(unsigned long player_id, int left, int right, int top, int bottom);
PLAY_API int _stdcall Player_getVideoShowOffset(unsigned long player_id, int *left, int *right, int *top, int *bottom);

PLAY_API int _stdcall Player_registerSetDualCallback(unsigned long player_id, DUAL_SPEAK_CALLBACK callback, DWORD dwUser);
PLAY_API int _stdcall Player_registerDrawFun(unsigned long player_id, DRAW_FUN_CALLBACK DrawFun, void* pUser);
PLAY_API int _stdcall Player_registerDecCallback(unsigned long player_id, DecDataFun callback, DWORD dwUser);

//bEnable = 0, 实时
//bEnable = 1, iMax = 0，库将按帧数据的时间放，缓冲的帧要由你来控制，这也是net_file模式。
//bEnable = 1, iMax（150～5000）,iMax为缓冲多久的帧数据
PLAY_API int _stdcall  Player_setCushionRange(unsigned long player_id, BOOL bEnable, int iMin, int iMax);

#define RE_NORMAL			0
#define RE_MIRROR_LEFTRIGHT	1
#define RE_MIRROR_UPDOWN	2
PLAY_API int _stdcall Player_setRenderEffect(unsigned long player_id, int type);

//enable 0:平铺到整个窗口 其他：按实际图像比例显示，创建实例时默认为0
PLAY_API void _stdcall Player_renderActualProportion(unsigned long player_id, int enable); 
#endif // __PlayerSdkCu_h__
