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

#define AVI_WRITE	1	//дģʽ

#ifndef NULL
#define NULL		0
#endif

typedef void* AVI_FILE;	//AVI�ļ����

/*
����: ��һ��AVI�ļ�
����:
	filename [I] �ļ���
	mode	 [I] �򿪷�ʽ��Ŀǰֻ֧��дģʽ(AVI_WRITE)
����ֵ:
	�򿪵��ļ����
*/
AVI_API AVI_FILE AVI_fopen(char* filename, int mode);

/*
����: ��򿪵��ļ���д��һ֡����
����:
	file	[I] Ҫд���Ŀ��AVI�ļ����������AVI_fopen����
	frm		[I] Ҫд���֡��������ַ
����ֵ:
	�ɹ�����0
	ʧ�ܷ��ظ�ֵ
*/
AVI_API int AVI_fwrite(AVI_FILE file, void* frm);

/*
����: �ر�һ��AVI�ļ������ͷ���Դ
����:
	file	[I] Ҫ�رյ�Ŀ��AVI�ļ����������AVI_fopen����
����ֵ:
	�ɹ�����0
	ʧ�ܷ��ظ�ֵ
*/
AVI_API int AVI_fclose(AVI_FILE file);

/*
����: �޸�һ��AVI�ļ�
����:
	filename	[I] Ҫ�޸���Ŀ���ļ���
����ֵ:
	�ɹ�����0
	ʧ�ܷ��ظ�ֵ
*/
AVI_API int AVI_frepair(char* filename);

#ifdef __cplusplus
}
#endif
#endif