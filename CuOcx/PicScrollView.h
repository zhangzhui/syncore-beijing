#if !defined(AFX_PICSCROLLVIEW_H__0BAB0228_8C0D_4A90_A5F2_91F370457F9E__INCLUDED_)
#define AFX_PICSCROLLVIEW_H__0BAB0228_8C0D_4A90_A5F2_91F370457F9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicScrollView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPicScrollView view

class CPicScrollView : public CScrollView
{
protected:
	CPicScrollView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPicScrollView)

// Attributes
public:
	IPicture *m_pPic;
	OLE_XSIZE_HIMETRIC m_hmWidth;     
	OLE_YSIZE_HIMETRIC m_hmHeight; 
	long m_cxPic;
	long m_cyPic;
	

// Operations
public:
	void LoadPic(CFile& file);
	void ReleasePic();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicScrollView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPicScrollView();

	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPicScrollView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICSCROLLVIEW_H__0BAB0228_8C0D_4A90_A5F2_91F370457F9E__INCLUDED_)
