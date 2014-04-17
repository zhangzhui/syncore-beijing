// CuOcxPpg.cpp : Implementation of the CCuOcxPropPage property page class.

#include "stdafx.h"
#include "CuOcx.h"
#include "CuOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCuOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCuOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CCuOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCuOcxPropPage, "CUOCX.CuOcxPropPage.1",
	0xe5baa6ab, 0x288c, 0x4889, 0x94, 0x2f, 0x79, 0x4, 0xed, 0xd5, 0xd8, 0x17)


/////////////////////////////////////////////////////////////////////////////
// CCuOcxPropPage::CCuOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCuOcxPropPage

BOOL CCuOcxPropPage::CCuOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CUOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxPropPage::CCuOcxPropPage - Constructor

CCuOcxPropPage::CCuOcxPropPage() :
	COlePropertyPage(IDD, IDS_CUOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CCuOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxPropPage::DoDataExchange - Moves data between page and properties

void CCuOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CCuOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxPropPage message handlers
