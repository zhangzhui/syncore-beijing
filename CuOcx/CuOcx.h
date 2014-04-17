#if !defined(AFX_CUOCX_H__12A9C604_DF4D_4E9B_B1F0_F38AB950E1F1__INCLUDED_)
#define AFX_CUOCX_H__12A9C604_DF4D_4E9B_B1F0_F38AB950E1F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CuOcx.h : main header file for CUOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCuOcxApp : See CuOcx.cpp for implementation.

class CCuOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUOCX_H__12A9C604_DF4D_4E9B_B1F0_F38AB950E1F1__INCLUDED)
