// CuOcxCtl.cpp : Implementation of the CCuOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "CuOcx.h"
#include "CuOcxCtl.h"
#include "CuOcxPpg.h"
#include "MainPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define KEY_SEPERATOR "\""
#define KEY_COLON ":"

#define KEY_PATH "-P"
#define KEY_CAMERA "-C"
#define KEY_CONNECT_STR "-N"
#define KEY_TASK_NO "-A"
#define KEY_TASK_TYPE "-B"
#define KEY_DEBUG "-D"
#define KEY_USERNAME "-U"

#define KEY_PATH_LOWER "-p"
#define KEY_CAMERA_LOWER "-c"
#define KEY_CONNECT_STR_LOWER "-n"
#define KEY_TASK_NO_LOWER "-a"
#define KEY_TASK_TYPE_LOWER "-b"
#define KEY_DEBUG_LOWER "-d"
#define KEY_USERNAME_LOWER "-u"


IMPLEMENT_DYNCREATE(CCuOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCuOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CCuOcxCtrl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CCuOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CCuOcxCtrl)
	DISP_FUNCTION(CCuOcxCtrl, "SetPassWord", SetPassWord, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CCuOcxCtrl, "SetUserName", SetUserName, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CCuOcxCtrl, "SetServerIPAddr", SetServerIPAddr, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CCuOcxCtrl, "SetServerPort", SetServerPort, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CCuOcxCtrl, "SetWorkDir", SetWorkDir, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CCuOcxCtrl, "SetCameraID", SetCameraID, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CCuOcxCtrl, "Init", Init, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CCuOcxCtrl, "SetDisplayMode", SetDisplayMode, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CCuOcxCtrl, "Excute", Excute, VT_EMPTY, VTS_BSTR)
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
	m_pMainPage = NULL;

	m_nServerPort = 0;
	m_nDisplayMode = eMode_Normal;

	m_bDebug = FALSE;
	m_time = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::~CCuOcxCtrl - Destructor

CCuOcxCtrl::~CCuOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
// 	if (m_pMainPage && m_pMainPage->GetSafeHwnd())
// 	{
// 		m_pMainPage->PostMessage(WM_DESTROY, NULL, NULL);
// 	}
}


/////////////////////////////////////////////////////////////////////////////
// CCuOcxCtrl::OnDraw - Drawing function

void CCuOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	CRect rc = rcBounds;
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(GRAY_BRUSH)));

#ifdef _DEBUG
	CString strDraw("This is a CuOcx control.");
#else
	CString strDraw("");
#endif
	pdc->DrawText(strDraw, &rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
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

void CCuOcxCtrl::SetPassWord(LPCTSTR strPassWord) 
{
	// TODO: Add your dispatch handler code here
	m_strPassWord = strPassWord;
}

void CCuOcxCtrl::SetUserName(LPCTSTR strUserName) 
{
	// TODO: Add your dispatch handler code here
	m_strUserName = strUserName;
}

void CCuOcxCtrl::SetServerIPAddr(LPCTSTR strIPAddr) 
{
	// TODO: Add your dispatch handler code here
	m_strServerIPAddr = strIPAddr;
}

void CCuOcxCtrl::SetServerPort(long nPort) 
{
	// TODO: Add your dispatch handler code here
	m_nServerPort = nPort;
}

void CCuOcxCtrl::SetWorkDir(LPCTSTR strWorkDir) 
{
	// TODO: Add your dispatch handler code here
	m_strWorkDir = strWorkDir;
}

void CCuOcxCtrl::SetCameraID(LPCTSTR strCameraID) 
{
	// TODO: Add your dispatch handler code here
	m_strCameraID = strCameraID;
	m_strCameraID.Replace(_T("0X2F"), _T(""));
}

void CCuOcxCtrl::Init() 
{
	// TODO: Add your dispatch handler code here
	m_pMainPage = new CMainPage;
	if (m_pMainPage == NULL)
	{
		MessageBox(_T("申请界面内存失败！"));
		return;
	}

	m_pMainPage->SetPassWord(m_strPassWord);
	m_pMainPage->SetUserName(m_strUserName);
	m_pMainPage->SetServerIPAddr(m_strServerIPAddr);
	m_pMainPage->SetServerPort(m_nServerPort);
	m_pMainPage->SetWorkDir(m_strWorkDir);
	m_pMainPage->SetCameraID(m_strCameraID);
	m_pMainPage->SetDisplayMode(m_nDisplayMode);
	m_pMainPage->SetPlaybackTime(m_time);
	m_pMainPage->SetDebugMode(m_bDebug);

	if (m_pMainPage->Create(IDD_PROPPAGE_MAIN, this))
	{
		CRect rc;
		GetClientRect(&rc);
		m_pMainPage->MoveWindow(&rc, TRUE);
		m_pMainPage->ShowWindow(SW_SHOW);
	}
	else
	{
		MessageBox(_T("创建界面失败！"));
	}
}

void CCuOcxCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_pMainPage && m_pMainPage->GetSafeHwnd())
	{
		m_pMainPage->MoveWindow(0, 0, cx, cy, TRUE);
	}
}

void CCuOcxCtrl::SetDisplayMode(long lDisplayMode) 
{
	// TODO: Add your dispatch handler code here
	m_nDisplayMode = lDisplayMode;
}

void CCuOcxCtrl::Excute(LPCTSTR strArgv) 
{
	// TODO: Add your dispatch handler code here
	TRACE(_T("Parameter recv: %s\n"), strArgv);
	ParseParameter(strArgv);

	Init();
}

void CCuOcxCtrl::ParseParameter(CString strParam)
{
	int iPos = strParam.Find(KEY_PATH);
	ASSERT(iPos != -1);
	if (iPos != -1)
	{
		int iParamBegin = strParam.Find(KEY_SEPERATOR, iPos);
		ASSERT(iParamBegin != -1);
		if (iParamBegin != -1)
		{
			int iParamEnd = strParam.Find(KEY_SEPERATOR, iParamBegin + 1);
			ASSERT(iParamEnd != -1);
			if (iParamEnd != -1)
			{
				SetWorkDir(strParam.Mid(iParamBegin + 1, iParamEnd - iParamBegin - 1));
			}
		}
	}

	iPos = strParam.Find(KEY_CAMERA);
	ASSERT(iPos != -1);
	if (iPos != -1)
	{
		int iParamBegin = strParam.Find(KEY_SEPERATOR, iPos);
		ASSERT(iParamBegin != -1);
		if (iParamBegin != -1)
		{
			int iParamEnd = strParam.Find(KEY_SEPERATOR, iParamBegin + 1);
			ASSERT(iParamEnd != -1);
			if (iParamEnd != -1)
			{
				SetCameraID(strParam.Mid(iParamBegin + 1, iParamEnd - iParamBegin - 1));
			}
		}
	}

	iPos = strParam.Find(KEY_CONNECT_STR);
	ASSERT(iPos != -1);
	if (iPos != -1)
	{
		int iParamBegin = strParam.Find(KEY_SEPERATOR, iPos);
		ASSERT(iParamBegin != -1);
		if (iParamBegin != -1)
		{
			int iParamEnd = strParam.Find(KEY_SEPERATOR, iParamBegin + 1);
			ASSERT(iParamEnd != -1);
			if (iParamEnd != -1)
			{
				CString str = strParam.Mid(iParamBegin + 1, iParamEnd - iParamBegin - 1);
				int iColonPos = str.Find(KEY_COLON);
				ASSERT(iColonPos != -1);
				if (iColonPos != -1)
				{
					SetServerPort(atoi(str.Mid(iColonPos + 1, str.GetLength() - iColonPos - 1)));
					SetServerIPAddr(str.Mid(0, iColonPos));
				}
			}
		}
	}

	iPos = strParam.Find(KEY_TASK_NO);
	ASSERT(iPos != -1);
	if (iPos != -1)
	{
		int iParamBegin = strParam.Find(KEY_SEPERATOR, iPos);
		ASSERT(iParamBegin != -1);
		if (iParamBegin != -1)
		{
			int iParamEnd = strParam.Find(KEY_SEPERATOR, iParamBegin + 1);
			ASSERT(iParamEnd != -1);
			if (iParamEnd != -1)
			{
				CString strTime = strParam.Mid(iParamBegin + 1, iParamEnd - iParamBegin - 1).Right(14);//YYYYMMDDHHMMSS = 14
				int iyear = atoi(strTime.Mid(0, 4));
				int imonth = atoi(strTime.Mid(4, 2));
				int iday = atoi(strTime.Mid(6, 2));
				int ihour = atoi(strTime.Mid(8, 2));
				int iminute = atoi(strTime.Mid(10, 2));
				int isecond = atoi(strTime.Mid(12, 2));
				m_time = CTime(iyear, imonth, iday, ihour, iminute, isecond);
			}
		}
	}

	iPos = strParam.Find(KEY_TASK_TYPE);
	ASSERT(iPos != -1);
	if (iPos != -1)
	{
		char cMode = strParam[iPos + 3];
		SetDisplayMode(atoi(&cMode));
	}

	iPos = strParam.Find(KEY_DEBUG);
	if (iPos != -1)
	{
		m_bDebug = TRUE;
	}

	iPos = strParam.Find(KEY_USERNAME);
	ASSERT(iPos != -1);
	if (iPos != -1)
	{
		int iParamBegin = strParam.Find(KEY_SEPERATOR, iPos);
		ASSERT(iParamBegin != -1);
		if (iParamBegin != -1)
		{
			int iParamEnd = strParam.Find(KEY_SEPERATOR, iParamBegin + 1);
			ASSERT(iParamEnd != -1);
			if (iParamEnd != -1)
			{
				SetUserName(strParam.Mid(iParamBegin + 1, iParamEnd - iParamBegin - 1));
			}
		}
	}
}
