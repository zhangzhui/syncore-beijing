#ifndef __VOD_H__
#define __VOD_H__

#include <vector>
using std::vector;

#define VOD_MAX_FILE_LEN			128
#define VOD_MAX_PROGRESS			10000
#define VOD_API						extern "C" __declspec(dllexport)
#define VOD_MAX_ID_LEN				32

#define VOD_DOWNLOADTOFILE			0x01
#define VOD_DOWNLOADTOBUFF			0x02

struct VOD_GUINFO
{};

/*
 * 回调函数原型，VOD_GUINFO暂不含有用信息，调用时lHandle和pGuInfo为注册回调函数
 * 时用户填入的值，lpBuf所指的内存为桢数据，nLength有效数据长度（含头），nProgress
 * 为当前播放进度[0,VOD_MAX_PROGRESS]正常, > VOD_MAX_PROGRESS:播放完成, < 0:中止
*/

typedef ULONG (*VOD_CALLBACKFUNC)(long lHandle, VOD_GUINFO* pGuInfo, char* lpBuf, 
								  int nLength, int nProgress);

struct CFileInfo
{
	//@{"FileName:/record/hd0/2008-02-28/guid12345678/09-22-00.dat"}
	char file[VOD_MAX_FILE_LEN];
	int type;	//@{Bit Set， 0x01:手动录像，0x02:定时录像, 0x04:告警录像}
	int size;	//@{Total Size Of The File}
};


struct VOD_CLIENTINFO
{
	long                lHandle;        //@{window handle}
	VOD_CALLBACKFUNC    lpFunc;         //@{call back}
	VOD_GUINFO          guInfo;         //@{extra}
};


struct CSrvAddrInfo
{
	struct in_addr	lLocalCsgAddr;			/*本域CSG*/
	struct in_addr	lLocalMduAddr;			/*本域MDU*/
	unsigned short	usLocalCsgPort;
	unsigned short	usLocalMduPort;
	struct in_addr	lRemoteCsgAddr;			/*子域CSG*/
	struct in_addr	lRemoteMduAddr;			/*子域MDU*/
	unsigned short	usRemoteCsgPort;		/*不跨域需清0*/
	unsigned short	usRemoteMduPort;		/*不跨域需清0*/
	char strLocalMduID[VOD_MAX_ID_LEN];		/*本域MDU ID*/
	char strRemoteMduID[VOD_MAX_ID_LEN];	/*子域MDU ID*/
	char strDevDomainID[VOD_MAX_ID_LEN];	/*设备所在域的域ID*/
};
//shc_alter 文件下载的信息
struct DLFileInfo{
	CString fileName;
	CString fileSave;
	ULONGLONG fileSize;
};
/*
 * 名称：st_vod_createSession()
 * 用途：创建与服务器的会话
 * 参数：
 *			srv			[IN]: 服务器地址信息
 * 返回值： 失败NULL，成功非NULL
*/
VOD_API HANDLE st_vod_createSession(const CSrvAddrInfo& srv);


/*
 * 名称：st_vod_destroySession()
 * 用途：销毁与服务器的会话
 * 参数：
 *			hSession	[IN]: 会话句柄
 * 返回值： 失败FALSE，成功TRUE
*/
VOD_API BOOL st_vod_destroySession(HANDLE hSession);



/*
 * 名称：st_vod_getFileList()
 * 用途：获取文件列表
 * 参数：
 *			hSession	[IN]: 会话句柄
 *			guid		[IN]: 通道GUID
 *			wType		[IN]: 文件类型：0x01:手动录像，0x02:定时录像, 0x04:告警录像, 0x100:录像日期列表
 *										0x10:手动抓拍，0x20:定时抓拍，0x40:告警抓拍, 
 *			srvID		[IN]: 录像服务器ID（MSU ID，中心点播）或设备ID(PUID, 前端点播)
 *			pSysStartTime [IN]: 查询条件之起始时间
 *			pSysEndTime	[IN]: 查询条件之终止时间
 *			vFileList	[OUT]: 返回的查询结果
 * 返回值： 失败FALSE，成功TRUE
*/
VOD_API BOOL st_vod_getFileList(HANDLE hSession, const char* guid, int wType, 
	const char* srvID, SYSTEMTIME* pSysStartTime, SYSTEMTIME* pSysEndTime, vector<CFileInfo>& vFileList);


/*
 * 名称：st_vod_openVideo()
 * 用途：打开历史视频流
 * 参数：
 *			hSession	[IN]: 会话句柄，同一个会话可以打开多路流
 *			bVod		[IN]: 点播类型(TRUE: 中心点播，FALSE: 前端点播)
 *			srvID		[IN]: 录像服务器ID(MSU ID，中心点播)或设备ID(PUID, 前端点播)
 *			file		[IN]: 原始文件路径，通过st_vod_getFileList()从服务器获得
 *			nStreamType [IN]: 流类型，0x01音频，0x02视频，0x04 GPS, (0x00默认全部)
 *								(仅下载时有效.)
 * 返回值： 成功返回流句柄，失败返回NULL
*/
VOD_API HANDLE st_vod_openVideo(HANDLE hSession, bool bVod, const char* srvID, 
								const char* file, int nStreamType = 0);


/*
 * 名称：st_vod_closeVideo()
 * 用途：关闭历史视频流
 * 参数：
 *			hSession	[IN]: 要关闭的流对应的会话句柄
 *			hVideo		[IN]: 要关闭的流句柄
 * 返回值： 成功返回TRUE，失败返回FALSE
*/
VOD_API BOOL st_vod_closeVideo(HANDLE hSession, HANDLE hVideo);


/*
 * 名称：st_vod_registerCallback()
 * 用途：注册回调函数
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 *			Info		[IN]：参数, Info.lHandle在回调时原样送出,回调函数时参数pGuInfo所指
 								内存中含有的信息与Info.guInfo的内容相同（被浅拷贝)。
 * 返回值： 返回旧的注册信息
*/
VOD_API VOD_CLIENTINFO st_vod_registerCallback(HANDLE hVideo, VOD_CLIENTINFO Info);


/*
 * 名称：st_vod_attachToFile()
 * 用途：将播放的流保存到文件，在观看视频流的同时将流保存,先于st_vod_play()调用。
 * 参数：
 *			nCompanyCode[IN]: 厂商代码
 *			hVideo		[IN]: 对应的流句柄
 *			file		[IN]: 文件路径名
 * 返回值： 成功TRUE， 失败：FALSE
*/
VOD_API BOOL st_vod_attachToFile(HANDLE hVideo, const int nCompanyCode, const char* file);


/*
 * 名称：st_vod_setDownload()
 * 用途：设置为下载模式，在此之前需调用st_vod_attachToFile()。 先于st_vod_play()调用。
 * 参数：
 *			hVideo		[IN]: 对应的流句柄，
 * 返回值： 无
*/
VOD_API void st_vod_setDownload(HANDLE hVideo, USHORT usMode = VOD_DOWNLOADTOFILE);

/*
 * 名称：st_vod_setPlayPoint()
 * 用途：播放点设置，用于播放进度调整。
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 *			rate		[IN]: 为[0,VOD_MAX_PROGRESS]之间任一值。
 *							  可在播放的过程中任意设置。
 * 返回值： 成功TRUE，失败FALSE
*/
VOD_API BOOL st_vod_setPlayPoint(HANDLE hVideo, ULONG rate);


/*
 * 名称：st_vod_play()
 * 用途：播放。
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 * 返回值： 成功TRUE，失败FALSE
*/
VOD_API BOOL st_vod_play(HANDLE hVideo);


/*
 * 名称：st_vod_stop()
 * 用途：停止，不可再用st_vod_play()来恢复。
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 * 返回值： 成功TRUE，失败FALSE
*/
VOD_API BOOL st_vod_stop(HANDLE hVideo);


/*
 * 名称：st_vod_pause()
 * 用途：暂停，可用st_vod_play()来恢复。
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 * 返回值： 成功TRUE，失败FALSE
*/
VOD_API BOOL st_vod_pause(HANDLE hVideo);


/*
 * 名称：st_vod_getTimePro()
 * 用途：查询当前播放的时间进度。
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 *			dwTotal		[OUT]: 总时间，以秒计
 *			dwNow		[OUT]: 当前桢是第几秒
 * 返回值： 成功TRUE，失败FALSE
*/
VOD_API BOOL st_vod_getTimePro(HANDLE hVideo, DWORD &dwTotal, DWORD &dwNow);


/*
 * 名称：st_vod_speedDown()
 * 用途：快放, 可在播放的过程中任意设置
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 * 返回值： +1正常速度，2：2倍速，4：4倍速
 *			-1正常速度，-2：1/2倍速，-4：1/4倍速
*/
VOD_API int st_vod_speedDown(HANDLE hVideo);


/*
 * 名称：st_vod_speedUp()
 * 用途：慢放, 可在播放的过程中任意设置
 * 参数：
 *			hVideo		[IN]: 对应的流句柄
 * 返回值： +1正常速度，2：快放2倍速，4：快放4倍速
 *			-1正常速度，-2：慢放1/2倍速，-4：慢放1/4倍速
*/
VOD_API int st_vod_speedUp(HANDLE hVideo);


//@{Other utilities}
/*
 * 名称：afx_addNDays()
 * 用途：当前时间加上N天后的结果
 * 参数：
 *			pSysDate	[IN｜OUT]: 时间结构体指针
 *			nDays		[IN]: N
 * 返回值： 无
*/
VOD_API void afx_addNDays(SYSTEMTIME* pSysDate, int nDays);


#endif	//__VOD_H__

