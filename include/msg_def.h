#ifndef __MSG_DEF_H__
#define __MSG_DEF_H__

#define	PROTOCOL_TCP		0x01
#define	PROTOCOL_UDP		0x02
#define	PROTOCOL_MCAST		0x03

#define	ACK_ERROR_OTHER		0xff	//��������
#define	ACK_SUCCESS			0x00	//�ɹ�
#define	ACK_ERROR_NAME		0x01	//�û�������
#define	ACK_ERROR_PWD		0x02	//�������
#define	ACK_ERROR_RIGHT		0x03	//Ȩ�޲���
#define	ACK_ERROR_CHANNEL	0x04	//�����ͨ����
#define	ACK_ERROR_PTZ_BUSY	0x05	//��̨æ,��ʱ�޷�����
#define NET_EXCEPTION		0x06    //�����쳣
#define TRANSPARENT_SUCCESS 0x00	//͸������ɹ�
#define TRANSPARENT_EXCEPTION 0xF0  //͸�������쳣

#define	MSG_LOGIN			0x0001	//��½
#define	MSG_LOGOUT			0x0002	//ע��
#define	MSG_OPEN_CHANNEL	0x0003	//��ͨ��
#define	MSG_CLOSE_CHANNEL	0x0004	//�ر�ͨ��
#define	MSG_START_SEND_DATA	0x0005	//��ʼ��������
#define	MSG_STOP_SEND_DATA	0x0006	//ֹͣ��������
#define	MSG_PTZ_CONTROL		0x0007	//��̨����
#define	MSG_SESSION_ID		0x0009	//
#define	MSG_MATRIX_PROTOCOL	0x000a	
#define	MSG_SET_PARAM		0x0401	//���ò���
#define	MSG_GET_PARAM		0x0402	//��ȡ����
#define	MSG_RESET_VIDEO_PARAM	0x0403	//������Ƶ����Ĭ��ֵ
#define MSG_RESET_CMOS_PARAM  0x0404  //����CMOS����Ĭ��ֵ

#define	MSG_GET_RECORD_LIST	0x0801	//��ѯ¼��
#define	MSG_SET_TIME		0x0802	//����ʱ��
#define	MSG_GET_TIME		0x0803	//��ȡʱ��
#define	MSG_VERSION_INFO	0x0804	//�汾��Ϣ
#define	MSG_HARDDISK_INFO	0x0805	//Ӳ����Ϣ
#define	MSG_SYSTEM_STATUS	0x0806	//ϵͳ״̬
#define	MSG_GET_LOG			0x0807	//��ѯ��־
#define	MSG_DELETE_LOG		0x0808	//ɾ����־
#define	MSG_ALARM_INFO		0x0809	//�澯��Ϣ
#define	MSG_ALARM_CONTROL	0x080a	//�澯�ϴ�����
#define	MSG_UPGRADE_STATUS	0x080b	//����״̬
#define	MSG_HEARTBEAT		0x080c	//������
#define	MSG_HEARTBEAT_PORT	0x080d	//�������˿���Ϣ
#define MSG_GET_USERINFO	0x080e
#define MSG_ADD_USER		0x080f
#define MSG_DELETE_USER		0x0810
#define MSG_MODIFY_USER		0x0811

#define MSG_FORCE_KEYFRAME	0x0830	//ǿ��I֡

#define MSG_TRANSPARENT_CMD	0x0814  //����͸������
#define MSG_GET_AP_INFO		0x0815 //��������·������Ϣ
//#define MSG_JOIN_AP			0x0816 //��������·����
#define MSG_START_TRANSPARENT		0x0816 //��ʼ͸������
#define MSG_STOP_TRANSPARENT		0x0817 //ֹͣ͸������
#define MSG_SEND_TRANSPARENT		0x0818 //����͸����������
#define MSG_REV_TRANSPARENT			0x0819 //����͸����������
#define	MSG_BROADCAST	        	0x0f01	//�㲥̽����Ϣ


//͸���������������

//////////////////////////////////////////////////////////////////////////
#define MSG_REMOTE_START_HAND_RECORD	0x0840  //��ʼ�ֶ�¼��
#define MSG_REMOTE_STOP_HAND_RECORD		0x0841	//ֹͣ�ֶ�¼��
#define MSG_DELETE_RECORD_FILE			0x0842  //ɾ��¼���ļ�
#define	MSG_HAND_RESTART				0x0843	//�ֶ�����
#define	MSG_DEFAULT_SETTING				0x0844	//Ĭ�ϲ�������
#define MSG_PARTITION					0x0845	//����
#define MSG_FORMAT						0x0846	//��ʽ��
#define MSG_FORMAT_STATUS				0x0847  //��ʽ��״̬
#define MSG_FDISK_STATUS				0x0848  //
#define MSG_START_ALARM					0x0849  //�澯����	
#define MSG_STOP_ALARM					0x0850	//�澯����
#define	MSG_BROADCAST_DEVICE			0x0851	//�㲥�����豸
#define	MSG_BROADCAST_IP				0x0852	//�㲥�޸�IP
#define MSG_DEFAULTOUTPUT_SETING		0x0853	//��������	
#define MSG_VERSION_SETING				0x0854  //�汾���� 
#define MSG_INPUTFILE_CONFIG			0x0855  //�����ļ�
#define MSG_OUTPUTFILE_CONFIG			0x0856  //�����ļ�
#define MSG_CCD_DEFAULT					0x0857
#define MSG_ITU_DEFAULT					0x0858
#define MSG_START_BACK					0x0859
#define MSG_STOP_BACK					0x0860
#define MSG_RESET_3G_MODULE             0x0863
#define MSG_CMOS_DEFAULT				0x0864    //cmos�ָ�Ĭ��
#define MSG_3GCONFIG_DEFAULT			0x0865
#define MSG_IP2986_DEFAULT              0x0866    //IP2986
#define MSG_NVP2400_DEFAULT             0x0867    //NVP2400��ϢĬ��ֵ

#define MSG_ISP3518_DEFAULT             0x0868    // ISP3518��ϢĬ��ֵ Date: 2013-6-25 Author: yms

#define MSG_SEND_SMS					0x0870    //add by fengzx 2011-10-17 for note

//////////////////////////////////////////////////////////////////////////

//��������������
#define	PARAM_AUTO_POWEROFF        0x0001
#define	PARAM_AUTO_POWERON         0x0002
#define	PARAM_USER_INFO            0x0003
#define	PARAM_HAND_RECORD          0x0004
#define	PARAM_NETWORK_CONFIG       0x0005
#define	PARAM_MISC_CONFIG          0x0006
#define	PARAM_PROBER_ALRAM         0x0007
#define	PARAM_RECORD_PARAM         0x0008
#define	PARAM_TERM_CONFIG          0x0009
#define	PARAM_TIMER_RECORD         0x000A
#define	PARAM_VIDEO_LOSE           0x000B
#define	PARAM_VIDEO_MOVE           0x000C //MOTION
#define	PARAM_VIDEO_CONFIG         0x000D
#define	PARAM_VIDEO_ENCODE         0x000E
#define	PARAM_ALARM_PARAM          0x000F

#define PARAM_COM_CONFIG		   0x0010
#define PARAM_OSD_SET			   0x0011
#define PARAM_OVERLAY_INFO		   0x0012
#define PARAM_MOTION_ZOOM		   0x0013
#define PARAM_PPPOE				   0x0014
#define	PARAM_RECORD_INFO	       0x0015
#define PARAM_WIRELESS_CONFIG	   0x0017
#define PARAM_MAIL_CONFIG		   0X0018
#define PARAM_FTP_CONFIG		   0X0019 
#define PARAM_SERIAL_INFO		   0x0022
#define PARAM_TRANSPARENCE_INFO	   0x0023
#define PARAM_SLAVE_ENCODE		   0x0024
#define PARAM_DEVICE_INFO		   0x0025
#define PARAM_AUDIO_INFO		   0x0026
#define PARAM_MEMBER_INFO		   0x0027
#define PARAM_CAMERA_INFO		   0x0028
#define PARAM_NAS_INFO			   0x0029
#define PARAM_ITU_INFO			   0x002A
#define PARAM_TIMER_COLOR2GREY     0x002B
#define PARAM_NA208_INFO		   0x001A
#define PARAM_MATRIX_INFO		   0x001B 
#define PARAM_TIMER_CAPTURE		   0x001C
#define PARMA_IMMEDIATE_CAPTURE	   0x001E
#define PARAM_USB_TYPE			   0x002F
#define PARAM_WSX_PLATFORM_CONFIG  0x0031

//CDMA
#define PARAM_CDMA_TIME			   0x1079 //2009.03.11
#define PARAM_CDMA_ALARM_ENABLE    0x1080 //������������
#define PARAM_CDMA_NONEGO_ENABLE   0x1081 //�ⲿ��������
#define PARAM_CDMA_ALARM_INFO      0x1082 //����������Ϣ
#define PARAM_CDMA_STREAM_ENABLE   0x1083 //CDMA�Զ�����


//��Ϊ
#define PARAM_CENTER_SERVER_CONFIG		   0x0020 
#define PARAM_LENS_INFO_CONFIG			   0x0021
//h3c
#define PARAM_H3C_PLATFORM_CONFIG		   0x0030
#define PARAM_H3C_NETCOM_CONFIG			   0x0031
#define PARAM_HANDIO_CONTROL               0x0038//�ֶ�IO���� 20091223
#define PARAM_TIMEIO_CONTROL		       0x0039//��ʱIO���� 20100114
//keda
#define PARAM_KEDA_PLATFORM_CONFIG		   0x0040
#define PARAM_CMOS_INFO                    0x0041 //add by fzx 2011-05-07
#define PARAM_3G_CONFIG_PARMA              0x0042//3G�����������
#define PARAM_IP2986_CONFIG                0x0044     //add by fengzx 2012-07-17
#define PARAM_NVP2400_CONFIG               0x0045

#define PARAM_ISP3518_CONFIG               0x0046 // ����3518������������ Date: 2013-6-15 Author: yms
//BELL
#define PARAM_BELL_PLATFORM_CONFIG		   0x0050
//ZTE
#define PARAM_ZTE_PLATFORM_CONFIG			0x0052
#define PARAM_ZTE_RECOVERDEF_CONFIG			0x0053	
//���Ż�ͨ
#define	PARAM_HXHT_PLATFORM_CONFIG			0X0062	//add by lch 2007-06-15
#define	PARAM_HXHT_ALARM_SCHEME				0X0063
#define PARAM_HXHT_NAT						0x0064
//���
#define PARAM_FENGH_NAT						0x0065
//����
#define PARAM_GONGX_NAT						0x0066
//����
#define PARAM_HAIDO_PARAM                   0x0067
//����
#define PARAM_LANGTAO_PARAM                 0x0068
//UT
#define PARAM_UT_PARAM						0x0069
#define PARAM_HAIDO_NAS						0x0070
//3511����
#define PARAM_H3C_INFO	   				    0x0071
//����
#define PARAM_SZ_INFO 					    0x0072
//Уʱ
#define PARAM_CHECK_TIME					0x0075 //--- add by wy 2009.05.06
  // ����DVR
#define PARAM_MOBILEDVR_PARAM	            0x0079

//������Ϣ����
#define PARAM_KEY_WEB_PWD					0x0080
#define PARAM_KEY_USER_PWD					0x0081
#define PARAM_KEY_SERVER_INFO				0x0082
#define PARAM_KEY_ENC_INFO					0x0083
#define PARAM_KEY_ENC_CHANNEL_INFO			0x0084
#define PARAM_KEY_DEC_INFO					0x0085
#define PARAM_KEY_TOUR_INFO					0x0086
#define PARAM_KEY_TOUR_STEP_INFO			0x0087
#define PARAM_KEY_GROUP_INFO				0x0088
#define PARAM_KEY_GROUP_STEP_INFO			0x0089
#define PARAM_3511_SYSINFO		            0x0090
#define PARAM_INTELLIGENCE_ALRAM            0x0091//�������ܲ���
#define PARAM_SPEED_ALRAM                   0x0092//���ó��ٲ���
#define PARAM_3515_SYSINFO		            0x0093
#define PARAM_PU_INFO                       0x0094



#define PARAM_NETSTAR_CONFIG	0x0201
#define PARAM_DECODE_NUM		0x0202
#define PARAM_DECODE_STAT		0x0203
#define PARAM_DEFAULT_ENCODER	0x0204
#define PARAM_DECODE_OSD		0x0205

//��̨����������

// Э������
#define PTZ_SANTACHI		0x01
#define PTZ_PELCO_D			0x02
#define PTZ_PELCO_P			0x03
#define PTZ_B01				0x04
#define PTZ_SANTACHI_IN		0x05

//��������
#define	MATRIX_LoginConnect          0x001 //1   Login connect
#define	MATRIX_LoginWithPassword     0x002 //2   Login with  operater-password
#define	MATRIX_LoginInAuto           0x003 //3   login-in Auto
#define	MATRIX_LoginOut              0x004 //4   login-out
#define	MATRIX_MonitorSelect         0x005 //5   Monitor select
#define	MATRIX_CameraSelect          0x006 //6   Camera select
#define	MATRIX_QuWeiSelect           0x007 //7   qu wei select
#define	MATRIX_TourSelect            0x008 //8   Tour  select
#define	MATRIX_GroupSelect           0x009 //9   Group select
#define	MATRIX_BackSeq               0x00a //10   Back Seq
#define	MATRIX_FowardSeq             0x00b //11   Foward Seq
#define	MATRIX_SEQ_DEC               0x00c //12   DEC -1 
#define	MATRIX_SEQ_INC               0x00d //13  INC +1 
#define	MATRIX_PAUSH                 0x00e //14  PAUSH 
#define	MATRIX_StopSeq               0x00f //15  Stop seq
#define	MATRIX_HoldON                0x010 //16  Hold ON
#define	MATRIX_HoldOFF    	         0x011 //17   Hold OFF
#define	MATRIX_DisplayALL   	     0x012 //18   Display  ALL
#define	MATRIX_DisplayTIME   	     0x013 //19   DISPLAY TIME
#define	MATRIX_DisplayTITLE          0x014 //20   Display TITLE
#define	MATRIX_DisplaySTATUS         0x015 //21   DISPLAY STATUS
#define	MATRIX_AlarmAreaStatus       0x016 //22   AlarmAreaStatus  ����״̬����ʾ
#define	MATRIX_DetectorStatus        0x017 //23   DetectorStatus   ̽����״̬����ʾ
#define	MATRIX_KeyJump                0x018 //24  JUMP
#define	MATRIX_MSsetupCommand  	      0x019 //25   MSsetupCommand   ���ܾ��������ɾ������
#define	MATRIX_DisplayStatus   	      0x01a //26  Display Status
#define	MATRIX_RequestMonitorStatus   0x01b //27  Request Monitor Status
#define	MATRIX_RequestMonitorMessage  0x01c //28  Request Monitor Message
#define	MATRIX_RequestCAMStatus       0x01d //29  Request CAM Status
#define	MATRIX_RequestCAMMessage      0x01e //30  Request CAM Message
#define	MATRIX_RequestAlamMessage     0x01f //31  Request Alam Message
#define	MATRIX_RequestControlsMessage 0x020 //32  Request Controls Message
#define	MATRIX_AlarmStatusMenu        0x021 //33  AlarmStatusMenu ����״̬�˵�����
#define	MATRIX_AlarmRecordMenu        0x022 //34  AlarmRecordMenu ������¼�˵�����
#define	MATRIX_SystemStatusMenu       0x023 //35  SystemStatusMenu ϵͳ״̬�˵�����
#define	MATRIX_MenuExit        	      0x024  //36  MenuExit �˵��˳�
#define	MATRIX_SubnetSelect    	      0x025  //37 SubnetSelect ����ѡ��
#define	MATRIX_SubnetExit     	      0x026  //38 SubnetExit �����˳�
#define	MATRIX_SystemTime             0x027  //39 transfer system time
#define	MATRIX_UserKey                0x028  //40 transfer user key   �û�����
#define	MATRIX_SystemSetup            0x029  //41 system setup   ϵͳ����
#define	MATRIX_SubnetMonSelect        0x02a  //42  Subnet Mon select
                                                                                
//SetupCommand �����������                                                                                                   
#define	MATRIX_SetupEnter             0x02b  //0  SetupEnter  
#define	MATRIX_SetupDATA1             0x02c  //1  SetupDATA1  
#define	MATRIX_SetupDATA2             0x02d  //2  SetupDATA2  
#define	MATRIX_SetupDATA3             0x02e  //3  SetupDATA3  
#define	MATRIX_SetupDATA4             0x02f  //4  SetupDATA4  
#define	MATRIX_SetupDATA5             0x030  //5  SetupDATA5  
#define	MATRIX_SetupDATA6             0x031  //6  SetupDATA6  
#define	MATRIX_SetupDATA7             0x032  //7  SetupDATA7  
#define	MATRIX_SetupDATA8             0x033  //8  SetupDATA8  
#define	MATRIX_SetupDATA9             0x034  //9  SetupDATA9  
#define	MATRIX_SetupDATA0             0x035  //10  SetupDATA0 
#define	MATRIX_SetupUP                0x036  //11  SetupUP    
#define	MATRIX_SetupDOWN              0x037  //12  SetupDOWN  
#define	MATRIX_SetupLEFT              0x038  //13  SetupLEFT  
#define	MATRIX_SetupRIGHT             0x039  //14  SetupRIGHT 
#define	MATRIX_SetupINC               0x03a  //15  SetupINC     
#define	MATRIX_SetupDEC               0x03b  //16  SetupDEC     
#define	MATRIX_SetupESC               0x03c  //17  SetupESC     
#define	MATRIX_SetupSET               0x03d  //18  SetupSET     
#define	MATRIX_SetupNEXT              0x03e  //19  SetupNEXT   
#define	MATRIX_SetupPRE               0x03f  //20  SetupPRE     
#define	MATRIX_SetupPOPUP             0x040  //21  SetupPOP-UP
#define	MATRIX_SetupPRINT             0x041  //22  SetupPRINT 
#define	MATRIX_SetupCLEAR             0x042  //23  SetupCLEAR 
#define	MATRIX_SetupSAVE              0x043  //24  SetupSAVE   
#define	MATRIX_SetupREAD              0x044  //25  SetupREAD   
#define	MATRIX_SetupDELE              0x045  //26  SetupDELE   


//AskAndAnswerѯ�ʺ��ʴ����
#define	MATRIX_AskDeveiceID           0x046  //0 AskDeveiceID  ѯ���豸����         		     
#define	MATRIX_AnswerDeveiceID        0x047 //1 AnswerDeveiceID  �ش��豸����               
#define	MATRIX_AskSoftwareVer         0x048 //2 AskSoftwareVer  ѯ������汾��Ϣ            
#define	MATRIX_AnswerSoftwareVer      0x049 //3 AnswerSoftwareVer  �ش�����汾��Ϣ         
#define	MATRIX_AskBoardStatus         0x04a //4 AskBoardStatus  ѯ�ʲ����Ϣ                
#define	MATRIX_AnswerBoardStatus      0x04b //5 AnswerBoardStatus  �ش�����Ϣ    

//AlarmControl �����������		
#define	MATRIX_DefendSetup            0x04c //0 Defend setup  ���              
#define	MATRIX_DefendSolve            0x04d //1  Defend solve����              	
#define	MATRIX_BellOFF   	          0x04e //2  Bell OFF  �����           	
#define	MATRIX_BellON                 0x04f //3  Bell ON���忪           		
#define	MATRIX_BRACHRODE              0x050 //4  BRACH RODE     ��·                         
#define	MATRIX_CLEARRODE              0x051 //5  CLEAR RODE     ����·                       
#define	MATRIX_RecordON               0x052 //6  Record ON       ¼��                        
#define	MATRIX_RecordOFF              0x053 //7  Record OFF      ͣ¼                        
#define	MATRIX_AlarmInc               0x054 //8  Alarm inc       ����Ѳ��+1                  
#define	MATRIX_ALarmDec               0x055 //9  ALarm dec       ����Ѳ��-1                  
#define	MATRIX_ResetOneRecord         0x056 //10  reset one record ������λ��1��ǰ           
#define	MATRIX_ResetAllRecord         0x057 //11  Reset all Record  ������λȫ��             
#define	MATRIX_RecordDisp             0x058 //12  Record disp       ������¼��ʾ             
#define	MATRIX_WarnModeBYHand         0x059 //13 Warn Mode BY hand ����ģʽ-�˹�             
#define	MATRIX_WarnModeTime           0x05a //14 Warn Mode Time    ����ģʽ-��ʱ            
#define	MATRIX_WaringRecordExit       0x05b //15 WARING RECORED EXIT   ������¼��ʾ�˳�  
//������������ţ�		
	//��̨ҡ�˿���		       
#define	MATRIX_PANUP				  0x05c //0 PAN UP (Speed 1-8)                             
#define	MATRIX_PANDOWN                0x05d //1  PAN DOWN(Speed 1-8)                                   
#define	MATRIX_PANRIGHT               0x05e //2  PAN RIGHT(Speed 1-8)                                 
#define	MATRIX_PANLEFT                0x05f  //3  PAN LEFT(Speed 1-8)                                   
#define	MATRIX_PANRIGHTUP             0x060 //4  PAN RIGHT UP(Speed 1-8)                            
#define	MATRIX_PANLEFTUP              0x061 //5  PAN LEFT UP(Speed 1-8)                              
#define	MATRIX_PANRIGHTDOWN           0x062 //6  PAN RIGHT DOWN(Speed 1-8)                        
#define	MATRIX_PANLEFTDOWN            0x063 //7  PAN LEFT DOWN(Speed 1-8)                          
#define	MATRIX_PANSTOP                0x064 //8  PAN STOP      
		
//��Ȧ����                                                                              
#define	MATRIX_IRISOPEN               0x065 //9  IRIS OPEN                                           
#define	MATRIX_IRISCLOSE              0x066 //10  IRIS CLOSE                                        
#define	MATRIX_FOCUSSTOP              0x067 //11  IRIS STOP                                         
#define	MATRIX_FOCUSNEAR              0x068 //12  FOCUS NEAR                                        
#define	MATRIX_FOCUSFAR               0x069 //13  FOCUS FAR                                          
#define	MATRIX_FOCUSTITLE             0x06a //14  FOCUS TITLE                                      
#define	MATRIX_FOCUSWIDE              0x06b //15  FOCUS WIDE                                        
#define	MATRIX_AUTOFOCUSENABLE        0x06c //16  AUTO focus enable   �Զ��Խ�������          
#define	MATRIX_AUTOFOCUSDISABLE       0x06d //17  AUTO focus disable  �Զ��Խ����ֹ         
#define	MATRIX_AUTOIRISENABLE         0x06e //18  auto iris  enable  �Զ���Ȧ����            
#define	MATRIX_AUTOIRISDISABLE        0x06f //19  auto iris  disable �Զ���Ȧ��ֹ           
#define	MATRIX_STOP                   0x070 //20   STOP (--NEAR WIDE FAR TELE) ��ͷ�˶�ͣ    
		
//��̨�Զ�����                                                                             
#define	MATRIX_AUTOHPAN               0x071 //21  AUTO H PAN     ��̨�Զ�ˮƽ�˶�                   
#define	MATRIX_AUTOPANSTOP            0x072 //22  AUTO PAN STOP  ��̨�Զ�ˮƽ�˶�ֹͣ            
#define	MATRIX_RANDMHPAN              0x073 //23  RANDM H PAN    ��̨���ˮƽ�˶�                  
#define	MATRIX__RANDMPANSTOP          0x074 //24  RANDM PAN STOP  ��̨���ˮƽ�˶�ֹͣ           
	//     
#define MATRIX_AUX1ON                 0x075 //25   AUX1 ON      �������ؿ�                             
#define	MATRIX_AUX1OFF                0x076 //26  AUX1 OFF              �������ع�                    
#define	MATRIX_RainBrushOpen          0x077 //27  Rain Brush Open ��ˢ���ؿ�                    
#define	MATRIX_RainBrushClose         0x078 //28  Rain Brush Close ��ˢ���ع�                  
#define	MATRIX_DeforstOpen            0x079 //29  Deforst Open    ��˪���ؿ�                      
#define	MATRIX_DeforstClose           0x07a //30  Deforst Close   ��˪���ع�                     
#define	MATRIX_HeartOn                0x07b //31  Heart On        ���ȿ�                              
#define	MATRIX_HeartClose             0x07c //32  Heart Close     ���ȹ�                           
#define	MATRIX_PowerOn                0x07d //33 Power On        ��Դ���ؿ�                           
#define	MATRIX_PowerClose             0x07e //34  Power Close     ��Դ���ع� 

//�����                                                                                   
#define	MATRIX_PCAMERPositioncall     0x07f //35   CAMER Position call 1-999    �����λ�õ���
#define	MATRIX_PresetCall     	      0x080	//36   Preset  call     Ԥ��λ�õ���                      
#define	MATRIX_PresetSet     	      0x081	//37   Preset  Set      Ԥ��λ������                      
#define	MATRIX_PresetReset    	      0x082	//38  Preset Reset     Ԥ��λ�ø�λ                     
#define	MATRIX_FunctionSelect 	      0x083	//39   Function select  ����ѡ��                     
#define	MATRIX_TURNOVER       	      0x084	//40  TURN OVER        ת��    
		                                             
#define	MATRIX_CAMENTERSETUPMENU      0x085 //41  CAM ENTER SETUP MENU  ��������ò˵�����   
#define	MATRIX_CURUP                  0x086 //42  CUR UP           ���������-��                        
#define	MATRIX_CURDN                  0x087 //43  CUR DN           ���������-��                        
#define	MATRIX_CURLF                  0x088 //44  CUR LF           ���������-��                        
#define	MATRIX_CURRT                  0x089 //45  CUR RT           ���������-��                         
#define	MATRIX_CONFIREM               0x08a //46  CONFIREM         ���������-ȷ��                   
#define	MATRIX_ESC                    0x08b //47  ESC              ���������-ȡ��                        
#define	MATRIX_INC                    0x08c //48  INC +1               ���������-��һ                    
#define	MATRIX_DEC                    0x08d //49  DEC -1               ���������-��һ  
                  
//����                                                                                     
#define	MATRIX_SMARTBegin             0x08e //50  SMART-Begin       ����-��ʼ                        
#define	MATRIX_SMARTEnd               0x08f //51  SMART_End                                            
#define	MATRIX_SMARTRepeat            0x090 //52  SMART_Repeat                                      
#define	MATRIX_SMART_Run              0x091 //53  SMART_Run 

//********************************************************************************************
// ��������
#define PTZ_UPSTART			0x01	
#define PTZ_UPSTOP			0x02   	
#define PTZ_DOWNSTART		0x03    
#define PTZ_DOWNSTOP		0x04    
#define PTZ_LEFTSTART		0x05    
#define PTZ_LEFTSTOP		0x06    
#define PTZ_RIGHTSTART		0x07    
#define PTZ_RIGHTSTOP		0x08    
#define PTZ_LEFTUPSTART		0x09    
#define PTZ_LEFTUPSTOP		0x0a    
#define PTZ_RIGHTUPSTART	0x0b    
#define PTZ_RIGHTUPSTOP		0x0c    
#define PTZ_LEFTDOWNSTART	0x0d    
#define PTZ_LEFTDOWNSTOP	0x0e    
#define PTZ_RIGHTDOWNSTART	0x0f    
#define PTZ_RITHTDOWNSTOP	0x10    

#define PTZ_PREVPOINTSET	0x11    
#define PTZ_PREVPOINTCALL	0x12    
#define PTZ_PREVPOINTDEL	0x13    
#define PTZ_ZOOMADDSTART	0x14    
#define PTZ_ZOOMADDSTOP		0x15    
#define PTZ_ZOOMSUBSTART	0x16    
#define PTZ_ZOOMSUBSTOP		0x17    
#define PTZ_FOCUSADDSTART	0x18    
#define PTZ_FOCUSADDSTOP	0x19    
#define PTZ_FOCUSSUBSTART	0x1a    
#define PTZ_FOCUSUBSTOP		0x1b    
#define PTZ_IRISADDSTART	0x1c    
#define PTZ_IRISADDSTOP		0x1d    
#define PTZ_IRISSUBSTART	0x1e    
#define PTZ_IRISSUBSTOP		0x1f    

#define PTZ_GOTOZEROPAN		0x20    
#define PTZ_FLIP180			0x21    
#define PTZ_SETPATTERNSTART	0x22    
#define PTZ_SETPATTERNSTOP	0x23    
#define PTZ_RUNPATTERN		0x24    
#define PTZ_SETAUXILIARY	0x25    
#define PTZ_CLEARAUXILIARY	0x26
#define PTZ_AUTOSCANSTART         0x27	//�Զ���ɨ-(��ʼ)
#define PTZ_AUTOSCANSTOP          0x28	//�Զ���ɨ-(ֹͣ)
#define PTZ_RANDOMSCANSTART       0x29	//�����ɨ-(��ʼ)
#define PTZ_RANDOMSCANSTOP        0x2a	//�����ɨ-(ֹͣ)

#define PTZ_POINCENTER			  0x30
#define PTZ_VIEWCENTER			  0x31

//#define PTZ_TYPE_TRANSPARENCE			0x0100  //͸������(�豸�˲���Э��ת����ֱ�Ӵ�����������) //add by wb
typedef	struct	_msg_time_t
{
	int	year;	
	int	month;
	int	day;
	int	hour;
	int	minute;
	int	second;
}msg_time_t;

#define	MSG_USER_NAME_LEN	24
#define	MSG_PASSWD_LEN		24
typedef struct __msg_login_t
{
	char user_name[MSG_USER_NAME_LEN];
	char user_pwd[MSG_PASSWD_LEN];
	int	local_right;
	int	remote_right;
	int	device_type;
	msg_time_t local_time;
}msg_login_t;

typedef struct __msg_open_channel_t
{
	int	channel_no;
	int	protocol_type;
	struct sockaddr_in client_sockAddr;

	unsigned char channel_type;
	unsigned char unused[3];
}msg_open_channel_t;

typedef struct __msg_close_channel_t
{
	int	channel_no;

	unsigned char channel_type;
	unsigned char unused[3];
}msg_close_channel_t;

typedef struct __msg_preview_t
{
	int channel;
	unsigned char channel_type;//0:������   1:������
	unsigned char unused[3];
}msg_preview_t;

#define MAX_PTX_CMD_BUM	128
typedef	struct	_msg_ptz_control_t
{
	int	channel;					//ͨ����
	int	param;						//Ԥ�õ��
}msg_ptz_control_t;

#define MAX_TRANSPARENT_CMD_NUM	1024
typedef struct __msg_transparent_cmd_t
{
	int com_no;
	int cmd_size;
	char cmd_buf[MAX_TRANSPARENT_CMD_NUM];
}msg_transparent_cmd_t;

#define	MSG_RECORD_FILENAME_LEN		48
#define	MSG_VERSION_LEN				24
#define	MSG_DISK_NAME_LEN			12	
#define	MSG_MAX_PART_NUM			4		
#define	MSG_MAX_HARDDISK_NUM		8	
#define	MSG_MAX_LOG_DESC_LEN		48
#define	MSG_ADDR_LEN				16
#define	MSG_ALARM_INFO_LEN			48
	
#define	MOVE_JPEG_FLAG		0x00000081	//�ƶ�����ͼƬ
#define	LOSE_JPEG_FLAG		0x00000082	//��ʧ����ͼƬ
#define	PROBER_JPEG_FLAG	0x00000083	//̽ͷ����ͼƬ
#define	ALL_JPEG_FLAG		0x00000084	//���б���ͼƬ
#define	HAND_RECORD_FLAG	0x00000001	//�ֶ�¼��
#define	MOVE_RECORD_FLAG	0x00000002	//�ƶ�¼��
#define	LOST_RECORD_FLAG	0x00000004	//��ʧ¼��
#define	INPUT_RECORD_FLAG	0x00000008	//̽ͷ¼��
#define	TIMER_RECORD_FLAG	0x00000010	//��ʱ¼��
#define	ALL_RECORD_FLAG		0x0000001f	//����¼��

typedef	struct	_msg_search_file_t
{
	int	channel;		//ͨ����
	int	record_type;	//¼������
	int	flag;			//������־,0:¼�����,1:���ݷ���
	msg_time_t	s_tm;	//��ʼʱ��
	msg_time_t	e_tm;	//����ʱ��
}msg_search_file_t;

typedef	struct	_msg_file_info_t
{
	char	filename[MSG_RECORD_FILENAME_LEN];
	unsigned long	filesize;					//�ļ���С
//	msg_time_t	s_tm;							//�ļ���ʼʱ��
//	msg_time_t	e_tm;							//�ļ�����ʱ��
}msg_file_info_t;

typedef struct __msg_fragment_t
{
    msg_time_t   start_time;     /*�ο�ʼʱ��*/
    msg_time_t   end_time;       /*�ν���ʱ��*/
    unsigned int data_start_offset;   /*������ʼλ��*/
    unsigned int data_end_offset;     /*���ݽ���λ��*/
    unsigned int index_start_offset;  /*֡������ʼλ��*/
    unsigned int index_end_offset;    /*֡��������λ��*/
    unsigned int record_type;         /*��¼������*/
    char    file_name[MSG_RECORD_FILENAME_LEN];/*�ļ���*/
}msg_fragment_t;

typedef	struct	__msg_record_list_t
{
	msg_file_info_t	msg_record_info;
	struct	__msg_record_list_t *next;
}msg_record_list_t;

typedef struct  _msg_version_info_t
{
	char	version_number[MSG_VERSION_LEN];	//�汾��
	char	version_author[MSG_VERSION_LEN];	//�汾����
	char	version_date[MSG_VERSION_LEN];		//�汾����
	unsigned int device_type;
}msg_version_info_t;

typedef struct sys_config_t
{
	unsigned int    dev_type;
	unsigned int    sub_type;
	unsigned char         chip_num;
	unsigned char         channel_num;
	unsigned char         prober_num;
	unsigned char         output_num;
	unsigned char         serial_num;
	unsigned char         ccd_enable:1;           /* ccd��ͷʹ����� */
	unsigned char         ptz_type:1;             /* 0:ptz�������� 1��ptz�����̶������ڸ����� */
	unsigned char         ptz_serial_no:6;        /* ��̨����ʹ�õĹ̶����ں� *///add20090723
	unsigned char         adchip_type;            /* 0:no ad chip 1:tvp5150  2:TW2815 */
	unsigned char         flat_type;
	unsigned char         resolv_capable_m[16];
	/*      �豸��ͨ�������� ������ 
	*      bit0:HI_QCIF bit1:HI_CIF bit2:HI_HD1 bit3:HI_D1 
	*      bit4:HI_MD1 bit5:HI_QVGA bit6:HI_VGA bit7:HI_SXGA */
	unsigned char         resolv_capable_s[16];
	/*      �豸��ͨ�������� ������ 
	*      bit0:HI_QCIF bit1:HI_CIF bit2:HI_HD1 bit3:HI_D1 
	*      bit4:HI_MD1 bit5:HI_QVGA bit6:HI_VGA bit7:HI_SXGA */
	unsigned char         ds_enable_flag:1;       /* ˫����ʹ�� */
	unsigned char         D1_type:7;              /* 0:704*576 1:720*576 */
	unsigned char         resolv_capable_m1[16];
	/*      �豸��ͨ�������� ������ 
	*      bit0:720P bit1:960P bit2:HI_UXGA  
	*      bit4:HI_MD1 bit5:HI_QVGA bit6:HI_VGA bit7:HI_SXGA */
	unsigned char         resolv_capable_s1[16];
	/*      �豸��ͨ�������� ������ 
	*      bit0:720P bit1:960P bit2:HI_UXGA  
	*      bit4:HI_MD1 bit5:HI_QVGA bit6:HI_VGA bit7:HI_SXGA */
	unsigned char		cmos_enable;/*cmos��ͷʹ�����*/
	unsigned char		encode_format;/*�����ʽ  0��PAL  1��N*/
	unsigned char		language;/*����  0������  1��Ӣ��*/
    
	unsigned char		alarm_num;
	unsigned char		itlgc_alarm_num:6;    //intelligence
  unsigned char		speed_alarm_num:2;    //���١�����	
	unsigned char   nvr_resolution;
	unsigned char   unused[1];

}sys_config_t;

#pragma pack(4)
typedef struct  _msg_part_info_t
{
	unsigned char   part_no;                //������
	unsigned char   part_type;              //��������,0:¼�����,1:���ݷ���
	unsigned char   cur_status;             //��ǰ״̬,0:δ����,1:δ��,2:����ʹ��
	unsigned char   reserved;               //����λ
	unsigned char   reserved1[4];
	LONGLONG     total_size;             //����������
	LONGLONG    free_size;              //����ʣ������
}msg_part_info_t;
typedef struct  _msg_hardisk_info_t
{
	unsigned char   disk_no;                //Ӳ�̺�
	unsigned char   part_num;               //������
	unsigned char   filesystem;             //�ļ�ϵͳ,0:δ֪,1:EXT3,2:FAT32
	unsigned char   part_status;            //����״̬,0:δ����,1:�ѷ���
	char    diskname[MSG_DISK_NAME_LEN];    //Ӳ����
	LONGLONG    harddisk_size;          //Ӳ��������
	msg_part_info_t partinfo[MSG_MAX_PART_NUM];
}msg_harddisk_info_t;
typedef struct  _msg_harddisk_data_t
{
	int     disk_num;                       //Ӳ����
	int     reserved;
	msg_harddisk_info_t   hdinfo[MSG_MAX_HARDDISK_NUM];
}msg_harddisk_data_t;

typedef struct  _msg_system_status_t
{
	int     cpu_percent;		//CPU������
	int     run_hour;			//����Сʱ��
	int     run_minute;			//���з�����
	int     mem_percent;
	int     flash_size;
	msg_harddisk_data_t disk_info;  //disk info
	int		unused[64];
}msg_system_status_t;
#pragma pack()

#define	LOG_ALL                 0	//������־
#define	LOG_SYSTEM              1	//ϵͳ��־
#define	LOG_ALARM               2	//������־
#define	LOG_OPERATE             3	//������־
#define	LOG_NETWORK             4	//������־
typedef	struct	_msg_search_log_t
{
	int	log_type;		//��־����
	msg_time_t	s_tm;
	msg_time_t	e_tm;
}msg_search_log_t;

typedef	struct	_msg_delete_log_t
{
	int	log_type;		//��־����
	msg_time_t	s_tm;
	msg_time_t	e_tm;
}msg_delete_log_t;

typedef struct  _msg_log_info_t
{
	int     log_type;						//��־����
	msg_time_t       tm;					//��־ʱ��
	char    log_desc[MSG_MAX_LOG_DESC_LEN];
}msg_log_info_t;

typedef	struct	__msg_log_list_t
{
	msg_log_info_t	msg_log_info;
	struct	__msg_log_list_t *next;
}msg_log_list_t;

#define ALARM_ALL 0
#define	ALARM_PROBER 1
#define ALARM_VIDEO_LOSE 2
#define ALARM_VIDEO_MOTION 3
#define ALARM_OSD 4
#define ALARM_DATE 5
#define ALARM_VIDEO_LOSE_STOP 6
#define ALARM_VIDEO_MOTION_STOP 7
#define	ALARM_PROBER_STOP 8

//���PTK��˾�ı�������
#define ALARM_PTK_IO_START	0x10
#define ALARM_PTK_IO_STOP	0x11

typedef	struct	_msg_alarm_info_t
{
	unsigned int alarm_ack;
	msg_time_t	tm;
	unsigned int alarm_id;	
	unsigned int alarm_channel;	
	unsigned int alarm_type;
	char	ip[MSG_ADDR_LEN];
	char	alarm_info[MSG_ALARM_INFO_LEN];
}msg_alarm_info_t;

typedef struct __msg_alarm_ack_t
{
	msg_time_t tm;
	unsigned int alarm_id;
}msg_alarm_ack_t;

typedef	struct	_msg_alarm_control_t
{
	int	status;		//�ͷŶ��Ƹ澯��Ϣ,0:������,1:����
}msg_alarm_control_t;

typedef	struct	_msg_upgrade_status_t
{
	int	percent;
}msg_upgrade_status_t;

typedef struct  _msg_user_info_t
{
        char    user_name[MSG_USER_NAME_LEN];
        char    user_pwd[MSG_PASSWD_LEN];
        int     local_right;
        int     remote_right;
}msg_user_info_t;

typedef	struct	__msg_user_list_t
{
	msg_user_info_t	msg_user_info;
	struct	__msg_user_list_t *next;
}msg_user_list_t;

typedef struct __msg_force_keyframe_t
{
	int channel;
}msg_force_keyframe_t;

//////////////////////////////////////////////////////////
#if 1
#define SEARCH_PORT				12300
#define PC_SEARCH_PORT			12301
#else 
#define SEARCH_PORT				13451
#define PC_SEARCH_PORT			13452
#endif

#define	MSG_HOSTNAME_LEN		24
#define	MSG_MAC_ADDR_SIZE		24
#define	MSG_IP_SIZE				16
typedef struct __dev_ip_info_t
{
	int		server_type;				//�豸����
	int		port_no;					//�����˿�
	int		net_type;					//��������
	char	host_name[MSG_HOSTNAME_LEN];//�豸��
	char	mac_addr[MSG_MAC_ADDR_SIZE];//MAC��ַ
	char	ip_addr[MSG_IP_SIZE];		//IP��ַ
	char	net_mask[MSG_IP_SIZE];		//��������
	char	gw_addr[MSG_IP_SIZE];		//���ص�ַ
	char	version_no[MSG_VERSION_LEN];//�汾��
	unsigned int port_offset;			//�˿�ƫ��
}dev_ip_info_t;

typedef struct __dev_dns_info_t
{
	char		dns_addr1[MSG_IP_SIZE];	//��DNS
	char		dns_addr2[MSG_IP_SIZE];	//����DNS
	unsigned short	dns_manu_flag;		//dns �ֶ���ñ�־,0: �Զ����, 1: �ֶ����
	unsigned short	web_port;			//web �˿�����
}dev_dns_info_t;

typedef	struct	_msg_broadcast_t
{
	dev_ip_info_t ip_info;
	dev_dns_info_t dns_info;

	char dhcp_flag;//0:disable
	char unused[3];

	char device_type[MSG_VERSION_LEN];                //��Ʒ�ͺ�
	sys_config_t    sys_config;                     //���ýṹ��
}msg_broadcast_t;

typedef	struct	_msg_broadcast_default_t
{
	dev_ip_info_t ip_info;
	dev_dns_info_t dns_info;

// 	char dhcp_flag;//0:disable
// 	char unused[3];
}msg_broadcast_default_t;

typedef	struct	_msg_broadcast_setnetinfo_t
{
	dev_ip_info_t src_ip_info;
	dev_ip_info_t dst_ip_info;
	dev_dns_info_t src_dns_info;
	dev_dns_info_t dst_dns_info;
	
	char dhcp_flag;//0:disable
	char unused[3];
}msg_broadcast_setnetinfo_t;

typedef	struct	_msg_wireless_info_t
{
	int current_used;//�Ƿ�ʹ��  1:ʹ��   0:δʹ��
	char essid[64];
	int signalStrength;//�ź�ǿ��
	int isEncrypt;//�Ƿ����  1:����  0:δ����
	int safety_type;//1:WEP   2:WPA   3:WPA-PSK
	int safety_option;//��ȫѡ��  1:�Զ�ѡ��   2:����ϵͳ   3:������Կ
	int key_numb;
	char password[96];					//web �˿�����
}msg_wireless_info_t;

//////////////////////////////////////////////////////////
#define	TCP_TYPE_PREVIEW			0x0000		//ʵʱԤ��
#define	TCP_TYPE_DOWNLOAD_RECORD	0x0001	//¼������
#define	TCP_TYPE_PLAY_RECORD		0x0002	//¼��㲥
#define	TCP_TYPE_ASK_DATA			0x0003		//��������(�㲥ʹ��)
#define	TCP_TYPE_UPGRADE_SYSTEM		0x0004		//����
#define	TCP_TYPE_UPGRADE_RESULT		0x0005		//�������
#define	TCP_TYPE_START_DUAL_TALK	0x0006		//��ʼ�����Խ�
#define	TCP_TYPE_STOP_DUAL_TALK		0x0007		//���������Խ�
#define	TCP_TYPE_START_DOWNLOAD_PIC 0x0008	//��ʼͼƬ����
#define TCP_TYPE_3G_INFO          0x0011    //3Gģ����Ϣ

#define	SERVER_LISTEN_PORT 9660 //�����ʹ��
#define UDP_BASE_PORT 9880		//�ͻ���ʹ��

typedef	struct	_msg_download_pic_t
{
	int		channel_no;
	unsigned  int	pic_len;
}msg_download_pic_t;

typedef	struct	_msg_download_t
{
	char	filename[MSG_RECORD_FILENAME_LEN];
}msg_download_t;

typedef	struct	_msg_filesize_t
{
	unsigned	long	filesize;
}msg_filesize_t;

typedef	struct	_msg_play_record_t
{
	char	file_name[MSG_RECORD_FILENAME_LEN];
}msg_play_record_t;

typedef	struct	_msg_ask_data_t
{
	int	datalen;	//�������ݳ��Ȼ�������
}msg_ask_data_t;

////////////////////////////////////////////2007-03-21
typedef struct __msg_send_data_t
{
	int channel;
	int data_type;//����Ƶ 0 ,��Ƶ1,��Ƶ2

	unsigned char channel_type;
	unsigned char unusd[3];
}msg_send_data_t;

typedef struct __msg_upgrade_info_t
{
	unsigned long filesize;
}msg_upgrade_info_t;

#define MSG_GET_COM_INFO 0x08000018
#define MSG_SET_COM_INFO 0x08000019

typedef struct __msg_com_info_t
{
	unsigned int com_index;
	unsigned int baudrate;
	unsigned int data_bit;
	unsigned int stop_bit;
	unsigned int parity;
}msg_com_info_t;

#define OSD_LOGO_LEN 64
typedef struct __msg_osd_info_t
{
	unsigned int x_pos;
	unsigned int y_pos;
	char logo[OSD_LOGO_LEN];
}msg_osd_info_t;

#define MSG_OSD_SET 0x08000012			//OSD����
#define MSG_OSD_QUETY 0x08000013		//OSD��ѯ
#define MSG_OSD_ENABLE 0x08000014		//OSD��ʾ״̬
#define MSG_OSD_ENABLE_QUERY 0x08000015	//OSD��ʾ״̬��ѯ

typedef struct __msg_osd_enable_t
{
	unsigned int logo_enable;
	unsigned int time_enable;
}msg_osd_enable_t;

#define MSG_COM_TRANSMIT 0x08000017
#define COM_DATA_LEN 512
typedef struct _msg_com_transmit_t
{
	unsigned int index;
	unsigned int len;
	char data[COM_DATA_LEN];
}msg_com_transmit_t;

#define MSG_GET_USERLOGIN_STATE 0x08000016
typedef struct __msg_user_login_state_query_t
{
	unsigned int channel_no; //0xffffffff ����ͨ��
}msg_user_login_state_query_t;

typedef struct __msg_user_login_state_t
{
	unsigned int channel_no;
	char user_name[MSG_USER_NAME_LEN];
	char user_ip[MSG_IP_SIZE];
	unsigned protocol_type;
	msg_time_t tm;
	unsigned int seconds;
	unsigned int net_state;
}msg_user_login_state_t;

typedef struct __msg_user_login_list_t
{
	msg_user_login_state_t msg_user_login_state;
	struct __msg_user_login_list_t *next; 
}msg_user_login_list_t;

typedef struct __msg_heart_t
{
	unsigned int heart_seq;
	unsigned int heart_ack;
}msg_heart_t;

typedef struct __msg_heartbeat_port_t
{
	int port;
}msg_heartbeat_port_t;

typedef struct __msg_remote_hand_record_t
{
	int				channel;
	unsigned char	record_hour_len;
	unsigned char	record_minute_len;
	unsigned char	record_status;
	unsigned char	reserve;

}msg_remote_hand_record_t;

typedef	struct	_msg_delete_file_t
{
	char	filename[MSG_RECORD_FILENAME_LEN];
}msg_delete_file_t;

typedef struct _msg_file_down_Status
{	
	int iSocket;
//	int iConnectStatus;				//0 ����ʧ��;1 ���ӳɹ�;
//	int iTransfersStatus;			//0 ֹͣ����;1 ��ʼ����;
	int iFileSize;				
	int iTransfersSize;
}msg_file_down_Status;

typedef struct _msg_session_id_t
{	
	int session_id;
}msg_session_id_t;

typedef struct _msg_recordplay_t
{	
	int total_frame_num;
	int first_frame_no;
	int total_time;
}msg_recordplay_t;

typedef struct _msg_remote_play_position_t
{	
	int flag;
	int play_position;
}msg_remote_play_position_t;

//���� ��ʽ��
typedef struct _msg_hard_fdisk_t
{
	unsigned int disk_id;
	unsigned int part_num;
}msg_hard_fdisk_t;
typedef struct _msg_hard_fdisk_status_t
{
	unsigned int disk_id;
	unsigned int fdisk_status;
}msg_hard_fdisk_status_t;
typedef struct _msg_part_format_t
{
	unsigned int disk_id;
	unsigned int part_id;
	unsigned int part_type; // 0 ¼�����; 1 ���ݷ���
}msg_part_format_t;
typedef struct _msg_hard_format_status_t
{
	unsigned int disk_id;
	unsigned int part_id;
	unsigned int format_status;
}msg_hard_format_status_t;

//˫��͸������
typedef struct __serial_info_t
{
	char	serial_no;		//���ں�,ֵ��Ϊ0
	char	data_bit;		//����λ,ֵ:5/6/7/8 Ĭ��8
	char	stop_bit;		//ֹͣλ,ֵ:0/1/2 Ĭ��1
	char	unuserd;
	int 	verify_rule;    //��֤����,-1:��,0:żУ��,1:��У�� Ĭ��-1
	int		baut_rate;      //������,Э���ض� Ĭ��9600
}serial_info_t;
typedef struct __msg_transparent_start_t
{
	serial_info_t	searial_info;
}msg_transparent_start_t;		
typedef struct __msg_transparent_send_t
{
	int		cmd_size;
	char	cmd_buf[MAX_TRANSPARENT_CMD_NUM];
}msg_transparent_send_t;
typedef struct __msg_transparent_rev_t
{
	int		cmd_size;
	char	cmd_buf[MAX_TRANSPARENT_CMD_NUM];
}msg_transparent_rev_t;

typedef struct __decode_channel_num_t //����ͨ����
{       
	int channel_num;
}decode_channel_num_t;

typedef struct __msg_3G_module_info_t
{
	int signal;//�ź�ǿ��
	int module_exist;//ģ���Ƿ���� 0:������ 1:����
	int sim_exist;	//�ֻ����Ƿ���� 0:������ 1:����
	int sys_mode;//����ģʽ//0�޷���1:AMPSģʽ(��ʱ����)��2��CDMAģʽ��3��GSM/GPRSģʽ��4��HDRģʽ��5��WCDMAģʽ
	//6:GPSģʽ��7��GSM/WCDMA��8��CDMA/HDR HYBRID
	int ppp_ip[16];	//����IP �ɹ�Ϊ��ȷIP,���ɹ�Ϊ 0.0.0.0
	int flat_status;//ƽ̨״̬ 0:������ 1:���� 2��CSG���ó��� 3��mdu���ó���
	
}msg_3G_module_info_t;

typedef struct  _msg_3g_default_t
{
	unsigned int server_type;
}msg_3g_default_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//add by liuqs on 2010-10-13
#define MAX_DEVICE_NAME_LEN 24
typedef struct __device_info_t
{
	unsigned char device_name[MAX_DEVICE_NAME_LEN];		//�豸����
	unsigned char channel_name[16][MAX_DEVICE_NAME_LEN];	//ͨ������
	unsigned char unused[32];	//����

}device_info_t;


typedef struct _msg_sms_t
{
	char rec_phone[32]; //
	char content[48];	//
}msg_sms_t;



// 200W��������ṹ  Date: 2013-6-5 Author: yms

typedef struct __nvp2400_config_t
{
	unsigned char agc_mode;//�Զ�����0x00 : ��ֹ, 0x01 : ��, 0x02 : �� 0x03 : ��
	unsigned char frame_accumulation;//֡�ۻ�,0:��ֹ��1ʹ��
	unsigned char wide_dynamic;//��̬0:��ֹ, 1:��, 2:��, 3:��
	unsigned char defog;//ȥ��0:��ֹ, 1:��, 2:��, 3:��
	unsigned char backlight_mode;//���ⲹ��0 : �ر�, 1 : ���ⲹ��, 2 : ǿ������
	unsigned char shutter;//����
	//0x00 : eShutter_AUTO, 0x01 : eShutter_1_30s
	//0x02 : eShutter_1_50s , 0x03 : eShutter_FLK(1/100)
	//0x04 : eShutter_1_250s, 0x05 : eShutter_1_500s
	//0x06 : eShutter_1_1000s, 0x07 : eShutter_1_2000s
	//0x08 : eShutter_1_5000s, 0x09 : eShutter_1_10000s
	//0x0A : eShutter_1_100000s, 0x0B : eShutter_x02
	//0x0C : eShutter_x04, 0x0D : eShutter_x06
	//0x0E : eShutter_x08, 0x0F : eShutter_x10
	//0x10 : eShutter_x15, 0x11 : eShutter_x20
	//0x12 : eShutter_x25, 0x13 : eShutter_x30
	unsigned char brightness;//����0-255
	
	
	//ȥ��
	unsigned char res1;// 2dȥ�� 0 : ��ֹ, 1 : ����
	unsigned char d3nr_mode;// 3dȥ�� 0 : ��ֹ, 1 : ����
	unsigned char smart_nr_mode;//���ܽ���0 : ��ֹ, 1 : ����
	unsigned char d3nr_level;//���뼶��0x00 ~ 0xff
	
	unsigned char res2;//���ģʽ0 : ��ֹ, 1 : ����
	unsigned char lsc_correct;//��ͷ���Ƚ���0 : ��ֹ, 1 : ����
	unsigned char sharpness;//���ֵ0-255
	
	unsigned char res3;//��ƽ��ģʽ0 : ATW , 1 : AWC , 2 : INDOOR , 3 : OUTDOOR		
	unsigned char color_type;//��ɫģʽ0:�Զ�, 1:��ɫ, 2:�ڰף�3:�ⲿ
	
	//unsigned char unused[8];
	unsigned char contrast;//�Աȶ�0-255
	unsigned char saturation;//���Ͷ�0-255
	unsigned char red_plus;//��ɫ����0-255
	unsigned char blue_plus;//��ɫ����0-255
	
	unsigned char lsc_type:2;//��ͷ���ͣ�0:���Զ���Ȧ��1:�Զ���Ȧ
	unsigned char deflicker:2;//0:50hz,1:60hz	
	
	unsigned char mirror:2;//����0������1ˮƽ����2��ֱ���� ��3��ת
	unsigned char light_inhibition_block:1;//ǿ�����ƺ�ǿ�ⲿ�֣��Ƿ�Ϊ�ڿ�,0:�޺ڿ飬1�кڿ�
	unsigned char res4:1;//
	
	unsigned char unused[3];	
}nvp2400_config_t;

// ����3518��Ƶ�������ýṹ�� Date: 2013-6-25 Author: yms
typedef struct __isp3518_config_t
{
	unsigned char brightness;//����0-255
	unsigned char contrast;//�Աȶ�0-255
	unsigned char saturation;//���Ͷ�0-255
	unsigned char colortone; //ɫ�� 0-255
	
	unsigned char exposure;  //0:�Զ��ع� 1:�ֶ��ع�
	unsigned char d_agc;  //����AGC  0-255
	unsigned char s_agc;  //ģ��AGC 0-255 
	unsigned char awb_rg;  //��ƽ��rg  0-255 
	unsigned char awb_bg;  //��ƽ��bg  0-255 
	
	unsigned char sharp_enable;//�ֶ���� 0:��ֹ 1:����
	unsigned char sharpness;//���ֵ0-255
	
	unsigned char denoise_enable;//�ֶ����� 0:��ֹ 1:����	
	unsigned char denoise;//����ֵ 0-255
	
	unsigned char anti_di;//������ 0:��ֹ 1:����	
	
	unsigned char wide_enable; //��̬ 0:��ֹ 1:����
	unsigned char wide_dynamic;//��̬ 0-255
	
	unsigned char defog;//ȥ�� 0:��ֹ  1:����
	unsigned char dis_white_dot; //�����׵� 0:��ֹ 1:���� 
	
	unsigned char shading; //��ͷ���� 0::��ֹ  1: ����		
	unsigned char deflicker2;//����˸ʹ�� 0����ֹ 1������
	unsigned char def_mode;//����˸ 0��	�̶��ع�ģʽ  1���Զ��ع�ģʽ	
	
	unsigned char lsc_type:2;//��ͷ���ͣ�0:�Զ� ��1:�ֶ�
	unsigned char deflicker:2;//����˸ 0:50hz,1:60hz	   	
	unsigned char rotate:2;//��ת 0-3
	unsigned char mirror:1;//���� 0 ::��ֹ 1:���� 
	unsigned char turn:1;//��ת 0::��ֹ 1:���� 
	
	unsigned char unused[2];	
}isp3518_config_t;


#endif /* __MSG_DEF_H__ */








