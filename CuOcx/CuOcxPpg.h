#if !defined(AFX_CUOCXPPG_H__304D6AA4_1288_4E8A_A05C_B3F5DE2448DE__INCLUDED_)
#define AFX_CUOCXPPG_H__304D6AA4_1288_4E8A_A05C_B3F5DE2448DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CuOcxPpg.h : Declaration of the CCuOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CCuOcxPropPage : See CuOcxPpg.cpp.cpp for implementation.

class CCuOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCuOcxPropPage)
	DECLARE_OLECREATE_EX(CCuOcxPropPage)

// Constructor
public:
	CCuOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CCuOcxPropPage)
	enum { IDD = IDD_PROPPAGE_CUOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CCuOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUOCXPPG_H__304D6AA4_1288_4E8A_A05C_B3F5DE2448DE__INCLUDED)
