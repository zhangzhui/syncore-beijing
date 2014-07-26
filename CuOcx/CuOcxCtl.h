#if !defined(AFX_CUOCXCTL_H__3E7358E7_DA17_4EB9_AEE9_5C66AA7A782C__INCLUDED_)
#define AFX_CUOCXCTL_H__3E7358E7_DA17_4EB9_AEE9_5C66AA7A782C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CuOcxCtl.h : Declaration of the CCuOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl : See CuOcxCtl.cpp for implementation.

class CMainPage;
class CCuOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCuOcxCtrl)
private:
	CString m_strUserName;
	CString m_strPassWord;
	CString m_strServerIPAddr;
	long m_nServerPort;
	CString m_strWorkDir;
	CString m_strCameraID;
	long m_nDisplayMode;

	CMainPage *m_pMainPage;

// Constructor
public:
	CCuOcxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCuOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CCuOcxCtrl();

	DECLARE_OLECREATE_EX(CCuOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCuOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCuOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCuOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CCuOcxCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CCuOcxCtrl)
	afx_msg void SetPassWord(LPCTSTR strPassWord);
	afx_msg void SetUserName(LPCTSTR strUserName);
	afx_msg void SetServerIPAddr(LPCTSTR strIPAddr);
	afx_msg void SetServerPort(long nPort);
	afx_msg void SetWorkDir(LPCTSTR strWorkDir);
	afx_msg void SetCameraID(LPCTSTR strCameraID);
	afx_msg void Init();
	afx_msg void SetDisplayMode(long lDisplayMode);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CCuOcxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CCuOcxCtrl)
	dispidSetPassWord = 1L,
	dispidSetUserName = 2L,
	dispidSetServerIPAddr = 3L,
	dispidSetServerPort = 4L,
	dispidSetWorkDir = 5L,
	dispidSetCameraID = 6L,
	dispidInit = 7L,
	dispidSetDisplayMode = 8L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUOCXCTL_H__3E7358E7_DA17_4EB9_AEE9_5C66AA7A782C__INCLUDED)
