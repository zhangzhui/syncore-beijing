

#ifndef __ST_GLOBAL_H__
#define __ST_GLOBAL_H__

inline void TESTHR( HRESULT _hr ) 
{ if FAILED(_hr) throw(_hr); }

inline int MaxValue(int a, int b)
{	return (a >= b)?a:b; }
inline int MinValue(int a, int b)
{   return (a > b)?b:a;  }

#define SAFE_DELETE(p)  { if(p != NULL) { delete (p);     (p) = NULL; } }   //Delete object by New create 
#define SAFE_DELETEA(p) { if(p != NULL) { delete[] (p);   (p) = NULL; } }   //Delete Arrary
#define SAFE_RELEASE(p) { if(p != NULL) { (p)->Release(); (p) = NULL; } }
#define SAFE_FREE(p)	{ if(p != NULL) { free(p); (p) = NULL; } }

#define MAX_NUM_TO_PREVIEW   16

#define DIALOG_MONITOR_BK	(RGB(255,255,255))
#define VIDEO_SELECT_FRAME	(RGB(0,255,255))

#define DIALOG_BKCOLOR1      (RGB(128,159,196))   
#define DIALOG_BKCOLOR2      (RGB(141,180,240)) //(RGB(236,233,216))    
#define DIALOG_BKCOLOR3      (RGB(146,196,250))  
#define DIALOG_BKCOLOR4      (RGB(255,255,255))//(RGB(209,214,233))   //(RGB(157,164,219))   

#define TREECTRL_BKCOLOR     (RGB(170,174,217))
#define TREECTRL_TEXTCOLOR   (RGB(0,0,0))
#define TREE_IMAGE_MASK      (RGB(255,0,255))
//#define DLGSWITCH_STATICBK   (RGB(170,170,170))

#define CMDSTATUS_BKCOLOR    (TRANSPARENT)
#define CMDSTATUS_TEXTCOLOR  (RGB(0,0,220))

#define VIDEO_RECT_PENCOLOR         (RGB(255,255,255))
//#define VIDEO_TITLE_BKCOLOR_HOT     (RGB(255,142,0))   //RGB(149,184,233) (RGB(119,149,215)) // select(hot)
#define VIDEO_TITLE_BKCOLOR_HOT		(RGB(57,157,200))
#define VIDEO_TITLE_BKCOLOR_NORMAL  (RGB(153,153,153))  // normal
#define VIDOO_TITLE_BKCOLOR_LCLICK	(RGB(153,153,255))
#define VIDOO_TITLE_FGCOLOR_HOT     (RGB(255,255,255))
#define VIDOO_TITLE_FGCOLOR_NORMAL  (RGB(47,62,170))
#define VIDEO_SHOW_BKCOLOR          (RGB(73,73,73))        // video show bk
#define VIDEO_MNG_BKCOLOR           (RGB(30,30,30))        // video mng bk


#define  XML_FILENAME    "Systemcfg.xml"
#define  XML_SERVER      "server"
#define  XML_USEDOMAIN   "userdomain"
#define  XML_SEVDOMAIN   "serverdomain"
#define  XML_SEVIP       "serverip"
#define  XML_SEVPORT     "serverport"
#define  XML_TIMEDOUT    "timedout"
#define  XML_USERID      "userid"
#define  XML_PASSWND     "password"
#define  XML_SAVEPWD     "savepassword"

#define  XML_PICTURE     "picture"
#define  XML_RECORD      "record"
#define  XML_DOWNPIC     "downpic"
#define  XML_DOWNRECORD  "downrecord"


#include "dev_type.h"
typedef frame_head_t FRAMHEAD_T;

//定时录像机构
typedef struct			
{
	char	WeekName[32];		//星期名称；
	char	time_seg1[32];		//时间段1；
	char	time_seg2[32];		//时间段1；
	char	time_seg3[32];		//时间段1；
	char	time_seg4[32];		//时间段1；
	char    alarm_time1[32];    //布防时段1；
	char    alarm_time2[32];    //布防时段2；
	char    alarm_time3[32];    //布防时段3；
	char    alarm_time4[32];    //布防时段4；
	long    alarm_per_time1;    //预录时间1；
	long    alarm_per_time2;    //预录时间2；
	long    alarm_per_time3;    //预录时间3；
	long    alarm_per_time4;    //预录时间4；
	long    alarm_length1;      //录像时间1；
	long    alarm_length2;      //录像时间2；
	long    alarm_length3;      //录像时间3；
	long    alarm_length4;      //录像时间4；

	long 	reserve1;           //保留
	char    reserve2[32];       //保留
}WEEKINFO, *PWEEKINFO;
//特殊日机构
typedef struct			
{
	char	DayName[32];		//日期名称；
	char	time_seg1[32];		//时间段1；
	char	time_seg2[32];		//时间段1；
	char	time_seg3[32];		//时间段1；
	char	time_seg4[32];		//时间段1；
	char    alarm_time1[32];    //布防时段1；
	char    alarm_time2[32];    //布防时段2；
	char    alarm_time3[32];    //布防时段3；
	char    alarm_time4[32];    //布防时段4；
	long    alarm_per_time1;    //预录时间1；
	long    alarm_per_time2;    //预录时间2；
	long    alarm_per_time3;    //预录时间3；
	long    alarm_per_time4;    //预录时间4；
	long    alarm_length1;      //录像时间1；
	long    alarm_length2;      //录像时间2；
	long    alarm_length3;      //录像时间3；
	long    alarm_length4;      //录像时间4；

	long 	reserve1;           //保留
	char    reserve2[32];       //保留
}DAYINFO, *PDAYINFO;


#endif  // #ifndef __ST_GLOBAL_H__