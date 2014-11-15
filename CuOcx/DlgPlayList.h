#if !defined(AFX_DLGPLAYLIST_H__7FF02C90_3436_46BD_A234_5A8121FFBB6D__INCLUDED_)
#define AFX_DLGPLAYLIST_H__7FF02C90_3436_46BD_A234_5A8121FFBB6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayList.h : header file
//
#include "StdAfx.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPlayList dialog
class CMainPage;
class CDlgPlayList : public CDialog
{
// Construction
public:
	CDlgPlayList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlayList)
	enum { IDD = IDD_DLG_PLAYLIST };
	CListCtrl	m_ctrlListRecord;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CComboBox m_ctrlRecordType;
	CComboBox m_ctrlRecordSrc;
	CComboBox m_ctrlRecordServer;
	
	CButton m_ctrlQueryPic;
	CButton m_ctrlQuery;
	CString m_szPuid;
	CString m_szGuName;
	CString m_szGuid;
	
	CTime m_tStartTime;
	CTime m_tEndTime;
	CTime m_tDate;
	
	CString m_strVodIp;
	int m_nVodPort;
	int m_iRecordSrcType;
	int m_iSearchType;
	int	m_iVodServerNum;
	CU_NET_LIB::GUINFO *m_pGuInfo;
	CU_NET_LIB::VODSERVER_INFO m_vodServerInfo[16];

	//operations -------
	void InitCmbCtrls();
	void QueryList(int nQueryType,CU_NET_LIB::VODSERVER_INFO *pInfo, int iRecordSrcType, int iSearchType,
		      CTime tDate, CTime tStartTime, CTime tEndTime);
	void SetBaseInfo(int nType, CU_NET_LIB::GUINFO *pGuInfo, CU_NET_LIB::VODSERVER_INFO *pVodInfo);
	BOOL ParseDomain(char* szDomainName);
	void InitListCtrlHeaders();
	void SetGuInfo(CU_NET_LIB::GUINFO *pGuInfo);
	int GetSearchType();
	int GetSearchTypePic();

	void SetMainPage(CMainPage *pMainPage);
	CMainPage* GetMainPage();

	void SetWorkDir(CString& dir);
	void SetWorkMiddlePath(CString& midPath);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SearchFileToList(LPCTSTR lpszID, LPCTSTR lpszPath,COleDateTime StartDate,
		COleDateTime EndDate);
	void ResetFileName(int iType, LPCTSTR lpszPathName, CString &strFileName);
	void ShowRBMenu();

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayList)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonQuery();
	afx_msg void OnButtonQueryPic();
	afx_msg void OnSelchangeComboRecordServer();
	afx_msg void OnSelchangeComboRecordSrc();
	afx_msg void OnRclickListFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuPlay();
	afx_msg void OnMenuDownLoad();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int	m_nType;
	CU_NET_LIB::GUINFO m_guInfo;
	CU_NET_LIB::VODSERVER_INFO m_vod_info;

	CMainPage *m_pMainPage;
	CString m_workDir;
	CString m_workMiddlePath;
};


///=== MyComp ¿‡ ============================================///
class MyComp
{
public:
	bool operator()(CFileInfo& o1, CFileInfo& o2)
	{
		char *p_str1 = getCorrectPos(o1);
		char *p_str2 = getCorrectPos(o2);
		
		if(p_str1 && p_str2)
			return strcmp(p_str1, p_str2) < 0;
		
		return false;
	}
	
private:
	char *getCorrectPos(CFileInfo& o)
	{
		int index = strlen(o.file) - 1;
		int count = 0;
		while(index > 0)
		{
			if(o.file[index] == '/')
			{
				++count;
				if(count == 3)
				{
					return &o.file[index];
				}
			}
			
			--index;
		}
		
		return NULL;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYLIST_H__7FF02C90_3436_46BD_A234_5A8121FFBB6D__INCLUDED_)
