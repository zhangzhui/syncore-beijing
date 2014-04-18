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

#define NTIMEOUT 5000
#define WM_LOGIN (WM_USER + 1)
#define WM_GETDEVICELIST (WM_USER + 2)
#define WM_CLEARDEVICELIST (WM_USER + 3)
#define WM_CUNETLIB (WM_USER + 4)

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

// Dialog Data
	//{{AFX_DATA(CMainPage)
	enum { IDD = IDD_PROPPAGE_MAIN };
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
	void InsertChildNode(LPCTSTR lpszQueryID, int iType);
	void StartStream(CU_NET_LIB::DEVICE_NODE devInfo);
	void StopStream();
	BOOL CreatePlayInstance(CU_NET_LIB::GUINFO guInfo);
	void DestroyPlayInstance();
	BOOL StartVoice();
	void StopChart();
	BOOL GetYTControlCmd(int iMessage, char *szCmd, char *szParam);

	static UINT Thread_Status(LPVOID lParam);
	static UINT AFX_CDECL ptzControlThread(LPVOID lParam);
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strUserName;
	CString m_strPassWord;
	CString m_strServerIPAddr;
	long m_nServerPort;
	CString m_strWorkDir;
	CString m_strCameraID;

	BOOL m_bClientStartUp;
	BOOL m_bLoginFlag;

	CU_NET_LIB::GUINFO m_GuInfo;
	CU_NET_LIB::DEVICE_NODE *m_pDeviceNode;
	BOOL m_bOpenVideo;
	CEvent m_hNotiy;

	CVideoManage m_VideoMng;
	CVideoInstance *m_pVideoIns;

	long m_lManufactType;
	BOOL m_bStreamOpenFlag;

	HANDLE m_hEventQuit;
	CWinThread *m_pThread;

	CString m_strNotiy;
	BOOL m_bSoundAllow;
	BOOL m_bVoice;
public:
	unsigned long m_play_id;
	DWORD m_nCountTest;
	CU_NET_LIB::DEVICE_NODE m_DevInfo;
};

typedef struct _ptz_control_t
{
	char    csgIp[32];	
	char    cmd[32];
	char    param[32];
	char    msgtype[32];
	UINT    csgport;
	int     speed;
	CU_NET_LIB::GUINFO  guInfo;
}ptz_control_t;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_)
