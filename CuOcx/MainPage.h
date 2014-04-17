#if !defined(AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_)
#define AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainPage dialog

class CMainPage : public CDialog
{
// Construction
public:
	CMainPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainPage)
	enum { IDD = IDD_PROPPAGE_MAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINPAGE_H__448E9F8F_487C_4101_9CD8_FEA74D55FA60__INCLUDED_)
