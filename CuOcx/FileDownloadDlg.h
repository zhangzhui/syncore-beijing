#if !defined(AFX_FILEDOWNLOADDLG_H__EAB613C0_2AB7_4E2B_B004_B150DE0FD601__INCLUDED_)
#define AFX_FILEDOWNLOADDLG_H__EAB613C0_2AB7_4E2B_B004_B150DE0FD601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDownloadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDownloadDlg dialog

class CFileDownloadDlg : public CDialog
{
// Construction
public:
	void  StopMission();
	CFileDownloadDlg(CWnd* pParent = NULL);   // standard constructor

	DECLARE_DYNAMIC(CFileDownloadDlg)
// Dialog Data
	//{{AFX_DATA(CFileDownloadDlg)
	enum { IDD = IDD_DIALOG_DOWNLOAD };
	CProgressCtrl	m_ctrlDownloadProgress;
	CButton	m_ctrlCancel;
	BOOL	m_bAutoClose;
	CString	m_strDstFileName;
	CString	m_strFileSize;
	CString	m_strDownloadInfo;
	CString	m_strScrFileName;
	//}}AFX_DATA
public:
	HANDLE			   m_hVideo;             // vod video
	HANDLE			   m_hSession;           // vod session
	CString            m_strFile;            // File to download
	ULONGLONG          m_lSize;    
	CString            m_strFileSave;        // File to save
	CString			   m_strPuid;
	DWORD              m_dwLastTime;

	CU_NET_LIB::MDU_ROUTE_INFO	m_mduInfo;
	int 		m_nFrontOrCen;
	CU_NET_LIB::GUINFO		m_guInfo;
	CString		m_strMsuDomainID;
	CString		m_strMsuID;




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDownloadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileDownloadDlg)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT  ProcessNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDOWNLOADDLG_H__EAB613C0_2AB7_4E2B_B004_B150DE0FD601__INCLUDED_)
