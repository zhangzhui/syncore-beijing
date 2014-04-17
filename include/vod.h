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
 * �ص�����ԭ�ͣ�VOD_GUINFO�ݲ���������Ϣ������ʱlHandle��pGuInfoΪע��ص�����
 * ʱ�û������ֵ��lpBuf��ָ���ڴ�Ϊ�����ݣ�nLength��Ч���ݳ��ȣ���ͷ����nProgress
 * Ϊ��ǰ���Ž���[0,VOD_MAX_PROGRESS]����, > VOD_MAX_PROGRESS:�������, < 0:��ֹ
*/

typedef ULONG (*VOD_CALLBACKFUNC)(long lHandle, VOD_GUINFO* pGuInfo, char* lpBuf, 
								  int nLength, int nProgress);

struct CFileInfo
{
	//@{"FileName:/record/hd0/2008-02-28/guid12345678/09-22-00.dat"}
	char file[VOD_MAX_FILE_LEN];
	int type;	//@{Bit Set�� 0x01:�ֶ�¼��0x02:��ʱ¼��, 0x04:�澯¼��}
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
	struct in_addr	lLocalCsgAddr;			/*����CSG*/
	struct in_addr	lLocalMduAddr;			/*����MDU*/
	unsigned short	usLocalCsgPort;
	unsigned short	usLocalMduPort;
	struct in_addr	lRemoteCsgAddr;			/*����CSG*/
	struct in_addr	lRemoteMduAddr;			/*����MDU*/
	unsigned short	usRemoteCsgPort;		/*����������0*/
	unsigned short	usRemoteMduPort;		/*����������0*/
	char strLocalMduID[VOD_MAX_ID_LEN];		/*����MDU ID*/
	char strRemoteMduID[VOD_MAX_ID_LEN];	/*����MDU ID*/
	char strDevDomainID[VOD_MAX_ID_LEN];	/*�豸���������ID*/
};
//shc_alter �ļ����ص���Ϣ
struct DLFileInfo{
	CString fileName;
	CString fileSave;
	ULONGLONG fileSize;
};
/*
 * ���ƣ�st_vod_createSession()
 * ��;��������������ĻỰ
 * ������
 *			srv			[IN]: ��������ַ��Ϣ
 * ����ֵ�� ʧ��NULL���ɹ���NULL
*/
VOD_API HANDLE st_vod_createSession(const CSrvAddrInfo& srv);


/*
 * ���ƣ�st_vod_destroySession()
 * ��;��������������ĻỰ
 * ������
 *			hSession	[IN]: �Ự���
 * ����ֵ�� ʧ��FALSE���ɹ�TRUE
*/
VOD_API BOOL st_vod_destroySession(HANDLE hSession);



/*
 * ���ƣ�st_vod_getFileList()
 * ��;����ȡ�ļ��б�
 * ������
 *			hSession	[IN]: �Ự���
 *			guid		[IN]: ͨ��GUID
 *			wType		[IN]: �ļ����ͣ�0x01:�ֶ�¼��0x02:��ʱ¼��, 0x04:�澯¼��, 0x100:¼�������б�
 *										0x10:�ֶ�ץ�ģ�0x20:��ʱץ�ģ�0x40:�澯ץ��, 
 *			srvID		[IN]: ¼�������ID��MSU ID�����ĵ㲥�����豸ID(PUID, ǰ�˵㲥)
 *			pSysStartTime [IN]: ��ѯ����֮��ʼʱ��
 *			pSysEndTime	[IN]: ��ѯ����֮��ֹʱ��
 *			vFileList	[OUT]: ���صĲ�ѯ���
 * ����ֵ�� ʧ��FALSE���ɹ�TRUE
*/
VOD_API BOOL st_vod_getFileList(HANDLE hSession, const char* guid, int wType, 
	const char* srvID, SYSTEMTIME* pSysStartTime, SYSTEMTIME* pSysEndTime, vector<CFileInfo>& vFileList);


/*
 * ���ƣ�st_vod_openVideo()
 * ��;������ʷ��Ƶ��
 * ������
 *			hSession	[IN]: �Ự�����ͬһ���Ự���Դ򿪶�·��
 *			bVod		[IN]: �㲥����(TRUE: ���ĵ㲥��FALSE: ǰ�˵㲥)
 *			srvID		[IN]: ¼�������ID(MSU ID�����ĵ㲥)���豸ID(PUID, ǰ�˵㲥)
 *			file		[IN]: ԭʼ�ļ�·����ͨ��st_vod_getFileList()�ӷ��������
 *			nStreamType [IN]: �����ͣ�0x01��Ƶ��0x02��Ƶ��0x04 GPS, (0x00Ĭ��ȫ��)
 *								(������ʱ��Ч.)
 * ����ֵ�� �ɹ������������ʧ�ܷ���NULL
*/
VOD_API HANDLE st_vod_openVideo(HANDLE hSession, bool bVod, const char* srvID, 
								const char* file, int nStreamType = 0);


/*
 * ���ƣ�st_vod_closeVideo()
 * ��;���ر���ʷ��Ƶ��
 * ������
 *			hSession	[IN]: Ҫ�رյ�����Ӧ�ĻỰ���
 *			hVideo		[IN]: Ҫ�رյ������
 * ����ֵ�� �ɹ�����TRUE��ʧ�ܷ���FALSE
*/
VOD_API BOOL st_vod_closeVideo(HANDLE hSession, HANDLE hVideo);


/*
 * ���ƣ�st_vod_registerCallback()
 * ��;��ע��ص�����
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 *			Info		[IN]������, Info.lHandle�ڻص�ʱԭ���ͳ�,�ص�����ʱ����pGuInfo��ָ
 								�ڴ��к��е���Ϣ��Info.guInfo��������ͬ����ǳ����)��
 * ����ֵ�� ���ؾɵ�ע����Ϣ
*/
VOD_API VOD_CLIENTINFO st_vod_registerCallback(HANDLE hVideo, VOD_CLIENTINFO Info);


/*
 * ���ƣ�st_vod_attachToFile()
 * ��;�������ŵ������浽�ļ����ڹۿ���Ƶ����ͬʱ��������,����st_vod_play()���á�
 * ������
 *			nCompanyCode[IN]: ���̴���
 *			hVideo		[IN]: ��Ӧ�������
 *			file		[IN]: �ļ�·����
 * ����ֵ�� �ɹ�TRUE�� ʧ�ܣ�FALSE
*/
VOD_API BOOL st_vod_attachToFile(HANDLE hVideo, const int nCompanyCode, const char* file);


/*
 * ���ƣ�st_vod_setDownload()
 * ��;������Ϊ����ģʽ���ڴ�֮ǰ�����st_vod_attachToFile()�� ����st_vod_play()���á�
 * ������
 *			hVideo		[IN]: ��Ӧ���������
 * ����ֵ�� ��
*/
VOD_API void st_vod_setDownload(HANDLE hVideo, USHORT usMode = VOD_DOWNLOADTOFILE);

/*
 * ���ƣ�st_vod_setPlayPoint()
 * ��;�����ŵ����ã����ڲ��Ž��ȵ�����
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 *			rate		[IN]: Ϊ[0,VOD_MAX_PROGRESS]֮����һֵ��
 *							  ���ڲ��ŵĹ������������á�
 * ����ֵ�� �ɹ�TRUE��ʧ��FALSE
*/
VOD_API BOOL st_vod_setPlayPoint(HANDLE hVideo, ULONG rate);


/*
 * ���ƣ�st_vod_play()
 * ��;�����š�
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 * ����ֵ�� �ɹ�TRUE��ʧ��FALSE
*/
VOD_API BOOL st_vod_play(HANDLE hVideo);


/*
 * ���ƣ�st_vod_stop()
 * ��;��ֹͣ����������st_vod_play()���ָ���
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 * ����ֵ�� �ɹ�TRUE��ʧ��FALSE
*/
VOD_API BOOL st_vod_stop(HANDLE hVideo);


/*
 * ���ƣ�st_vod_pause()
 * ��;����ͣ������st_vod_play()���ָ���
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 * ����ֵ�� �ɹ�TRUE��ʧ��FALSE
*/
VOD_API BOOL st_vod_pause(HANDLE hVideo);


/*
 * ���ƣ�st_vod_getTimePro()
 * ��;����ѯ��ǰ���ŵ�ʱ����ȡ�
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 *			dwTotal		[OUT]: ��ʱ�䣬�����
 *			dwNow		[OUT]: ��ǰ���ǵڼ���
 * ����ֵ�� �ɹ�TRUE��ʧ��FALSE
*/
VOD_API BOOL st_vod_getTimePro(HANDLE hVideo, DWORD &dwTotal, DWORD &dwNow);


/*
 * ���ƣ�st_vod_speedDown()
 * ��;�����, ���ڲ��ŵĹ�������������
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 * ����ֵ�� +1�����ٶȣ�2��2���٣�4��4����
 *			-1�����ٶȣ�-2��1/2���٣�-4��1/4����
*/
VOD_API int st_vod_speedDown(HANDLE hVideo);


/*
 * ���ƣ�st_vod_speedUp()
 * ��;������, ���ڲ��ŵĹ�������������
 * ������
 *			hVideo		[IN]: ��Ӧ�������
 * ����ֵ�� +1�����ٶȣ�2�����2���٣�4�����4����
 *			-1�����ٶȣ�-2������1/2���٣�-4������1/4����
*/
VOD_API int st_vod_speedUp(HANDLE hVideo);


//@{Other utilities}
/*
 * ���ƣ�afx_addNDays()
 * ��;����ǰʱ�����N���Ľ��
 * ������
 *			pSysDate	[IN��OUT]: ʱ��ṹ��ָ��
 *			nDays		[IN]: N
 * ����ֵ�� ��
*/
VOD_API void afx_addNDays(SYSTEMTIME* pSysDate, int nDays);


#endif	//__VOD_H__

