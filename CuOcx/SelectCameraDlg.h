#if !defined(AFX_SELECTCAMERADLG_H__41E0CF3B_600D_4A58_9D5A_2E897602979E__INCLUDED_)
#define AFX_SELECTCAMERADLG_H__41E0CF3B_600D_4A58_9D5A_2E897602979E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectCameraDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectCameraDlg dialog

class CSelectCameraDlg : public CDialog
{
// Construction
public:
	void Init();
	CSelectCameraDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectCameraDlg)
	enum { IDD = IDD_DIALOG_SELECT_CAMERA };
	CListCtrl	m_DeviceList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectCameraDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectCameraDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTCAMERADLG_H__41E0CF3B_600D_4A58_9D5A_2E897602979E__INCLUDED_)
