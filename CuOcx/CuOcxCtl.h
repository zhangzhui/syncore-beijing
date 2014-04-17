#if !defined(AFX_CUOCXCTL_H__3E7358E7_DA17_4EB9_AEE9_5C66AA7A782C__INCLUDED_)
#define AFX_CUOCXCTL_H__3E7358E7_DA17_4EB9_AEE9_5C66AA7A782C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CuOcxCtl.h : Declaration of the CCuOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl : See CuOcxCtl.cpp for implementation.

class CCuOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCuOcxCtrl)

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
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CCuOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CCuOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CCuOcxCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUOCXCTL_H__3E7358E7_DA17_4EB9_AEE9_5C66AA7A782C__INCLUDED)
