#ifndef STCH_AVI_H
#define STCH_AVI_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef	_WINDOWS
#ifdef	AVI_EXPORTS
#define	AVI_API	__declspec(dllexport)
#else
#define	AVI_API	__declspec(dllimport)
#endif
#endif

#define AVI_WRITE	1	//写模式

#ifndef NULL
#define NULL		0
#endif

typedef void* AVI_FILE;	//AVI文件句柄

/*
功能: 打开一个AVI文件
参数:
	filename [I] 文件名
	mode	 [I] 打开方式，目前只支持写模式(AVI_WRITE)
返回值:
	打开的文件句柄
*/
AVI_API AVI_FILE AVI_fopen(char* filename, int mode);

/*
功能: 向打开的文件中写入一帧数据
参数:
	file	[I] 要写入的目标AVI文件句柄，调用AVI_fopen生成
	frm		[I] 要写入的帧缓冲区地址
返回值:
	成功返回0
	失败返回负值
*/
AVI_API int AVI_fwrite(AVI_FILE file, void* frm);

/*
功能: 关闭一个AVI文件，并释放资源
参数:
	file	[I] 要关闭的目标AVI文件句柄，调用AVI_fopen生成
返回值:
	成功返回0
	失败返回负值
*/
AVI_API int AVI_fclose(AVI_FILE file);

/*
功能: 修复一个AVI文件
参数:
	filename	[I] 要修复的目标文件名
返回值:
	成功返回0
	失败返回负值
*/
AVI_API int AVI_frepair(char* filename);

#ifdef __cplusplus
}
#endif
#endif