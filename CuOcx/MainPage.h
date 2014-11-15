#if !defined(AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_)
#define AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainPage dialog
#include "VideoManage.h"
#include "DlgPlayList.h"

#define WM_LOGIN (WM_USER + 1)
#define WM_GETDEVICELIST (WM_USER + 2)
#define WM_CLEARDEVICELIST (WM_USER + 3)
#define WM_CUNETLIB (WM_USER + 4)
#define WM_SHOWCAPTUREPIC (WM_USER + 5)
#define WM_TEXTOUTOPERATION (WM_USER + 6)
#define WM_DISPLAYALLDEVICEMATCHCAMERAID (WM_USER + 7)
#define WM_BEGIN_MONITOR (WM_USER + 8)

enum eDISPLAYMODE
{
	eMode_Normal,
	eMode_OnlyReplayBtn,
};

class CVideoInstance;
class CMainPage : public CDialog
{
// Construction
public:
	CMainPage(CWnd* pParent = NULL);   // standard constructor
	void SetPassWord(LPCTSTR strPassWord);
	void SetUserName(LPCTSTR strUserName);
	void SetServerIPAddr(LPCTSTR strIPAddr);
	void SetServerPort(long nPort);
	void SetWorkDir(LPCTSTR strWorkDir);
	void SetCameraID(LPCTSTR strCameraID);
	void SetDisplayMode(long nMode);
	void SetDebugMode(BOOL bDebug);
	void SetPlaybackTime(CTime t);
	BOOL MakeDir(char* filePath);

	BOOL CreateRecordFile();
	void TextOutOperation(CString &str);

// Dialog Data
	//{{AFX_DATA(CMainPage)
	enum { IDD = IDD_PROPPAGE_MAIN };
	CSliderCtrl	m_sliderSaturation;
	CSliderCtrl	m_sliderHue;
	CSliderCtrl	m_sliderBright;
	CSliderCtrl	m_sliderContrast;
	CStatic	m_staticPreview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitSDK();
	void InsertChildNode(LPCTSTR lpszQueryID, int iType, CString strMidPath);
	void StartStream(CU_NET_LIB::DEVICE_NODE devInfo);
	void StopStream();
	BOOL CreatePlayInstance(CU_NET_LIB::GUINFO guInfo);
	void DestroyPlayInstance();
	BOOL StartVoice();
	void StopChart();
	BOOL GetYTControlCmd(int iMessage, char *szCmd, char *szParam);
	void  WaitForThreadStatus();
	void ProcessCameraDirection();
	void SetVideoParam();
	void DoRecord();//录像
	void CloseRecordFile();//关闭录像文件
	void DoSoundRecord();//录音
	void CloseSoundRecordFile();//关闭录音文件
	CString GetRecFileExt(long lCompanyCode);

	static UINT Thread_Status(LPVOID lParam);

	void InVisibleCtrls();
	void DisplayDebugInfo();
	// Generated message map functions
	//{{AFX_MSG(CMainPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnLogin(WPARAM wParam, LPARAM lParam);
	afx_msg void OnGetDeviceList(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClearDeviceList(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnOpenVideo();
	afx_msg void OnBtnCloseVideo();
	afx_msg void OnBtnOpensound();
	afx_msg void OnBtnOpenvoice();
	afx_msg void OnBtnReplay();
	afx_msg void OnDestroy();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnRight();
	afx_msg void OnBtnLeft();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnAuto();
	afx_msg void OnBtnRemotePic();
	afx_msg void OnButtonFocus1();
	afx_msg void OnButtonFocus2();
	afx_msg void OnButtonLens1();
	afx_msg void OnButtonLens2();
	afx_msg void OnButtonZoom1();
	afx_msg void OnButtonZoom2();
	afx_msg void OnReleasedcaptureSliderBright(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderContrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderHue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderSaturation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnLocalpic();
	afx_msg void OnBtnLocalrecord();
	afx_msg void OnShowCapturePic(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTextOutOperation(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDisplayAllDeviceMatchCameraID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBeginMonitor(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnLocalsoundrecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_strUserName;
	CString m_strPassWord;
	CString m_strServerIPAddr;
	long m_nServerPort;
	CString m_strWorkDir;
	CString m_strCameraID;
	long m_nDisplayMode;
	BOOL m_bDebug;//调试模式
	CTime m_time;//回放用的时间

	CString m_strMidPath;//保存本地录像的中间目录

	BOOL m_bClientStartUp;//启动客户端
	BOOL m_bLoginFlag;

	CU_NET_LIB::GUINFO m_GuInfo;
	CU_NET_LIB::DEVICE_NODE *m_pDeviceNode;
	BOOL m_bOpenVideo;
	CEvent m_hNotiy;

	CVideoInstance *m_pVideoIns;

	long m_lManufactType;
	BOOL m_bStreamOpenFlag;

	HANDLE m_hEventQuit;//Thread_Status线程的等待退出事件
	CWinThread *m_pThread;

	CString m_strNotiy;
	BOOL m_bSoundAllow;
	BOOL m_bVoice;

	unsigned long m_play_id;
	DWORD m_nCountTest;
	CU_NET_LIB::DEVICE_NODE m_DevInfo;

	CString m_strVodIp;
    int m_nVodPort;
	CDlgPlayList m_dlgPlayList;

	CCameraControlThread m_CameraCtrl;

	BOOL m_bRecord;//记录有没有在录像
	BOOL m_bSwitchRecordFile;//切换录像文件，用在关闭录音的时候
	FILE *m_Recordfile;//录像文件
	AVI_FILE m_hRecordFileRec;

	BOOL m_bSoundRecord;//记录有没有在录音
	BOOL m_bSwitchSoundFile;//切换录音文件，用在关闭录音的时候
	FILE *m_SoundFile;//录音文件
	AVI_FILE m_hSoundFileRec;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_)
