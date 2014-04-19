#if !defined(AFX_DLGPICVIEW_H__69F0599F_14B7_4D7C_BF96_6A8D23576A07__INCLUDED_)
#define AFX_DLGPICVIEW_H__69F0599F_14B7_4D7C_BF96_6A8D23576A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPicView.h : header file
//
#include "CuOcx.h"
#include "PicScrollView.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPicView dialog
class CPicScrollView;

class CDlgPicView : public CDialog
{
// Construction
public:
	CDlgPicView(CWnd* pParent = NULL);   // standard constructor
	
	//Data
	OLE_XSIZE_HIMETRIC m_Width;
	OLE_YSIZE_HIMETRIC m_Height;
	long m_cxPic;
	long m_cyPic;
	CPicScrollView *m_pPicView;

	void GetFilePath(CString& str);
	void SetFilePath(CString value);
	void LoadPic();

// Dialog Data
	//{{AFX_DATA(CDlgPicView)
	enum { IDD = IDD_PIC_VIEW };
	CStatic	m_sInterval;
	CEdit	m_edit;
	CButton	m_btnAuto;
	CButton	m_btnNext;
	CButton	m_btnPre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPicView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL m_bInsideUpdate;
	// Generated message map functions
	//{{AFX_MSG(CDlgPicView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strFileName;
	IPicture* m_iPicture;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPICVIEW_H__69F0599F_14B7_4D7C_BF96_6A8D23576A07__INCLUDED_)
