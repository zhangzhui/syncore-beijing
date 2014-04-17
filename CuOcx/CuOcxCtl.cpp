// CuOcxCtl.cpp : Implementation of the CCuOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "CuOcx.h"
#include "CuOcxCtl.h"
#include "CuOcxPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCuOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCuOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CCuOcxCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CCuOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CCuOcxCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CCuOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CCuOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CCuOcxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCuOcxCtrl, 1)
	PROPPAGEID(CCuOcxPropPage::guid)
END_PROPPAGEIDS(CCuOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCuOcxCtrl, "CUOCX.CuOcxCtrl.1",
	0xa0fbeffb, 0x146c, 0x4174, 0x85, 0x8b, 0x3b, 0xb5, 0x36, 0x7c, 0x2, 0x7)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CCuOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DCuOcx =
		{ 0x8a5b809, 0x274, 0x4f5e, { 0xa6, 0x88, 0xb6, 0x60, 0x9f, 0x9d, 0x73, 0x7d } };
const IID BASED_CODE IID_DCuOcxEvents =
		{ 0x971cd979, 0xaf9d, 0x4ccd, { 0x80, 0xe8, 0x86, 0xcf, 0x9d, 0x31, 0x73, 0x6f } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwCuOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCuOcxCtrl, IDS_CUOCX, _dwCuOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::CCuOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCuOcxCtrl

BOOL CCuOcxCtrl::CCuOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CUOCX,
			IDB_CUOCX,
			afxRegApartmentThreading,
			_dwCuOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::CCuOcxCtrl - Constructor

CCuOcxCtrl::CCuOcxCtrl()
{
	InitializeIIDs(&IID_DCuOcx, &IID_DCuOcxEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::~CCuOcxCtrl - Destructor

CCuOcxCtrl::~CCuOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::OnDraw - Drawing function

void CCuOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::DoPropExchange - Persistence support

void CCuOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::OnResetState - Reset control to default state

void CCuOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::AboutBox - Display an "About" box to the user

void CCuOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CUOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl message handlers
