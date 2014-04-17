/***************************************************************************
 *
 * File name    : dev_type.h
 * Description  : define all interface of dev_type.h
 * Created      : 
 * Modified     : 
 *				  
 *				  
 ***************************************************************************/

#ifndef __DEV_TYPE_H__
#define __DEV_TYPE_H__


/******ADоƬ����******/
// �������ֱ�������� 
#define AD_NOCHIP		0
#define AD_TVP5150		1
#define AD_TW2815A 		2
#define AD_TW2815AB		3
#define AD_TW2815ABCD	4
#define AD_MT9D131		5
#define AD_SC110		6    //
#define AD_TW2867A      7
#define AD_TW2867AB     8
#define AD_NVP2400      9   //200W
#define AD_IP2986       10    //
#define AD_NVR          11   //

/*----------------------------device type-----------------------------*/
/* dvs device type define */
#define DEV_TYPE_VS3001E	0x54500200	/* h.264 1 channel encoder */
#define DEV_TYPE_VS3001D	0x54500201	/* h.264 1 channel decoder */
#define DEV_TYPE_VS3001R	0x54500203	/* h.264 1 channel encoder with hard disk */
#define DEV_TYPE_VS3004E	0x54500204	/* h.264 4 channel encoder */
#define DEV_TYPE_VS3004R	0x54500205	/* h.264 4 channel encoder with hard disk */
#define DEV_TYPE_VS3102R	0x54500206	/* h.264 2 channel encoder with hard disk */

/* ip camera device type define */
#define DEV_TYPE_VS5050X	0x54500306	/* h.264 1 channel D1 */
#define DEV_TYPE_VS5060X	0x54500304	/* h.264 1 channel D1 */

/* nvr device type define */
#define DEV_TYPE_NVR		0x54500400	/* powerpc 8245 nvr */

#define DEV_TYPE_HI3511	    0x54500600  /* Hi3511/3512 DVS&IPC */
#define DEV_TYPE_HI3515     0x54500700  // Hi3515
#define DEV_TYPE_HI3531     0x54500800  // Hi3531 /NVR/ 

#define DEV_TYPE_NT200HA	0x54530200	/* hi3510: h.264 1 channel encoder */
/* other device type define */

/*------------------------frame struct(//֡���ͣ��������£�)------------------------------*/
#define I_FRAME_TYPE			1 //I Frame
#define P_FRAME_TYPE			2 //P Frame
#define A_FRAME_TYPE			3 //Audio Frame
#define OSD_FRAME_TYPE		    4 // Osd Frame
#define PLATFORM_FRAME_TYPE	    6
#define GPS_FRAME_TYPE		    7//GPS Frame
#define PH_FRAME_TYPE			8//��ƽ��֡

/******��Ƶ�ֱ���(֡ͷʹ��)******/  
#define VIDEO_FORMAT_720P       0x00
#define VIDEO_FORMAT_D1		    0x01
#define VIDEO_FORMAT_HD1	    0x02
#define VIDEO_FORMAT_CIF	    0x03
#define VIDEO_FORMAT_QCIF	    0x04
#define VIDEO_FORMAT_960P  	    0x05
#define VIDEO_FORMAT_UXGA	    0x06
#define VIDEO_FORMAT_1080P      0x07

typedef struct __frame_head_t
{
        unsigned long	device_type;        //�豸���ͣ�����3511��3512ϵ�е�dvs��ipc����ֵΪ��0x54500600  ,3535Ϊ0x54500700    
        unsigned long	frame_size;         //֡��С��������֡ͷ��С
        unsigned long	frame_no;           //֡��ţ�3511��3512�ϵ�󣬴�0��ʼ����֡����
		unsigned char	video_format;       //��Ƶ�ֱ��ʣ�������ĺ궨��0x00(720P), 0x01(D1)...
        unsigned char	frame_type;         //֡���ͣ�1-I֡��2-P֡��3-��Ƶ֡...7-GPS֡�� 
		unsigned char	frame_rate;         //֡�ʣ�Ҳ����fps
		unsigned char	video_standard;     //��Ƶ��ʽ���������£�1-PAL,2-NTSC
		unsigned long	sec;                //֡������ʱ�䣬��1970��1��1�տ�ʼ����
        unsigned long	usec;
		_int64			pts;
}frame_head_t;

typedef struct __frame_t
{
	frame_head_t frame_head;
	unsigned char *frame_data;
}frame_t;


/*-----------------------file struct------------------------------*/
#define MAX_LOGO_SIZE	32
#define FLIE_VERSION01 0x00000001 
#define FLIE_VERSION02 0x00000002

typedef struct __file_head_t
{
	int file_version;
	int device_type;
	int record_type;
	char logo[MAX_LOGO_SIZE];
}file_head_t;

typedef struct __file_t
{
	file_head_t file_head;
	frame_t *p_frame;
}file_t;

#endif /* __DEV_TYPE_H__ */


