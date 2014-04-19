#if !defined(AFX_NETVODDLG_H__B74EDACA_3B0F_4052_9D3C_D9435C1F3C4F__INCLUDED_)
#define AFX_NETVODDLG_H__B74EDACA_3B0F_4052_9D3C_D9435C1F3C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetVodDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetVodDlg dialog
//#include "ColorStatic.h"

class CNetVodDlg : public CDialog
{
// Construction
public:
	BOOL HideAllButton(BOOL bFlag);
	BOOL m_bFullScreen;
	void DoFullScreen();
	BOOL m_bPuase;
	HANDLE m_hSession;
	HANDLE m_hVideo;
	unsigned long m_play_id;
	CString m_strFileName;
	BOOL		m_bLBtDownFlag;
	int         m_nSliderFlag;
	int			m_nPos;
	CNetVodDlg(CWnd* pParent = NULL);   // standard constructor

	bool m_bVodType; //TRUE-vod, FALSE-pu
	CU_NET_LIB::GUINFO m_guInfo;
	CU_NET_LIB::VODSERVER_INFO m_vod_info;
	void SetBaseInfo(bool bVodType, CU_NET_LIB::GUINFO *pGuInfo, CU_NET_LIB::VODSERVER_INFO *pVodInfo, CString strFileName);

	BOOL m_bFileType;
	CString m_strPreSpeed;

	BOOL m_bInit;
// Dialog Data
	//{{AFX_DATA(CNetVodDlg)
	enum { IDD = IDD_DIALOG_NET_PLAY };
// 	CXPButton	m_btnSnap;
// 	CSliderCtrl	m_Slider;
// 	CXPButton	m_ctrlStop;
// 	CXPButton	m_ctrlSlow;
// 	CXPButton	m_ctrlPlay;
// 	CXPButton	m_ctrlPause;
// 	CXPButton	m_ctrlFast;
// 	CColorStatic	m_static_play;

	CButton	m_btnSnap;
	CSliderCtrl	m_Slider;
	CButton	m_ctrlStop;
	CButton	m_ctrlSlow;
	CButton	m_ctrlPlay;
	CButton	m_ctrlPause;
	CButton	m_ctrlFast;
	CEdit	m_static_play;


	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetVodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetVodDlg)
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonFast();
	afx_msg void OnButtonSlow();
	afx_msg void OnButtonStop();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT  OnNitify_PlayBack(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETVODDLG_H__B74EDACA_3B0F_4052_9D3C_D9435C1F3C4F__INCLUDED_)
