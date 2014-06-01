// FileDownloadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CuOcx.h"
#include "FileDownloadDlg.h"
#include "DlgPlayList.h"
#include "MainPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ULONG CallBack_VodDownLaod(long lHandle, VOD_GUINFO* pGuInfo, char* lpBuf, int nLength, int nProgress)
{
	CFileDownloadDlg* pDlg = (CFileDownloadDlg*)lHandle;
	if(pDlg == NULL)
		return -1;
	::PostMessage(pDlg->m_hWnd, WM_DOWNLOADMSG, (WPARAM)nProgress, (LPARAM)0);
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CFileDownloadDlg dialog
IMPLEMENT_DYNAMIC(CFileDownloadDlg, CDialog)

CFileDownloadDlg::CFileDownloadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDownloadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileDownloadDlg)
	m_bAutoClose = FALSE;
	m_strDstFileName = _T("");
	m_strFileSize = _T("");
	m_strDownloadInfo = _T("");
	m_strScrFileName = _T("");
	//}}AFX_DATA_INIT

	m_hVideo = NULL;
	m_hSession = NULL;
	m_strFile = _T("");
	m_lSize   = 0;
	m_strFileSave = _T("");
	m_dwLastTime = 0;
	m_strPuid.Empty();
}


void CFileDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDownloadDlg)
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_ctrlDownloadProgress);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_ctrlCancel);
	DDX_Check(pDX, IDC_CHECK_AUTO_CLOSE, m_bAutoClose);
	DDX_Text(pDX, IDC_STATIC_DST_FILENAME, m_strDstFileName);
	DDX_Text(pDX, IDC_STATIC_FILE_SIZE, m_strFileSize);
	DDX_Text(pDX, IDC_STATIC_INFO, m_strDownloadInfo);
	DDX_Text(pDX, IDC_STATIC_SCR_FILENAME, m_strScrFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileDownloadDlg, CDialog)
	//{{AFX_MSG_MAP(CFileDownloadDlg)
	ON_MESSAGE(WM_DOWNLOADMSG, ProcessNotify)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDownloadDlg message handlers

BOOL CFileDownloadDlg::OnInitDialog() 
{
	CString strOut;

	CDialog::OnInitDialog();
	CString strLoadText;

// 	SetDlgItemText(IDC_STATIC1,IDS_WINTEXT_1026);
// 	SetDlgItemText(IDC_STATIC2,IDS_WINTEXT_1027);
// 	SetDlgItemText(IDC_STATIC3,IDS_WINTEXT_1028);
// 	SetDlgItemText(IDC_STATIC4,IDS_WINTEXT_1029);
// 	SetDlgItemText(IDC_STATIC_SCR_FILENAME,IDS_WINTEXT_1030);
// 	SetDlgItemText(IDC_STATIC_DST_FILENAME,IDS_WINTEXT_1030);
// 	SetDlgItemText(IDC_CHECK_AUTO_CLOSE,IDS_WINTEXT_1031);
//  SetDlgItemText(IDC_BUTTON_CANCEL,IDS_WINTEXT_1032);


	// TODO: Add extra initialization here
	SetWindowText(_T("正在下载..."));
	
	m_ctrlDownloadProgress.SetRange(0, 10000);
	CString strText = _T("");
	strText.Format(_T("%s"), m_strFile);
	if(strText.GetLength() > 50)
		strText.Insert(50, _T("\n"));
	GetDlgItem(IDC_STATIC_SCR_FILENAME)->SetWindowText(strText);
	
	strText.Format(_T("%d KB"), m_lSize);
	GetDlgItem(IDC_STATIC_FILE_SIZE)->SetWindowText(strText);
	
	CString strMsg = _T("");
	if( strlen(m_mduInfo.szLocalMduId) >= 64)
	{
		strMsg.Format(_T("未启动下载, MDU ID格式不正确:%s"), m_mduInfo.szLocalMduId);

		GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strMsg);
	}
	else
	{		
		//HANDLE hSession = st_vod_createSession(szVodIp, m_uPort);
		CSrvAddrInfo srvAddrinfo;	//6
		memset(&srvAddrinfo, 0, sizeof(CSrvAddrInfo));
		char szServerIp[256]={0};
		//sprintf(szServerIp, (LPSTR)(LPCSTR)theApp.m_szServerIP);
        
		CDlgPlayList* pPlayList = (CDlgPlayList*)GetParent();
		CMainPage* pSDKDlg = (CMainPage*)pPlayList->GetMainPage();
		sprintf(szServerIp,(LPSTR)(LPCSTR)pSDKDlg->m_strServerIPAddr.GetBuffer(pSDKDlg->m_strServerIPAddr.GetLength()));
		pPlayList->ParseDomain(szServerIp);

		//theApp.ParseDomain(szServerIp);
		srvAddrinfo.lLocalCsgAddr.S_un.S_addr = inet_addr(szServerIp);

		//srvAddrinfo.usLocalCsgPort = htons(theApp.m_iLoginPort+PORT_CSG_INCREASE_NUM);
		srvAddrinfo.usLocalCsgPort = htons(pSDKDlg->m_nServerPort + PORT_CSG_INCREASE_NUM);

		srvAddrinfo.lLocalMduAddr.S_un.S_addr = inet_addr(m_mduInfo.szLocalMduIp);
		srvAddrinfo.usLocalMduPort = htons(m_mduInfo.uLocalPort+VOD_BASE_MDU_OFFSET);
		strncpy(srvAddrinfo.strLocalMduID, m_mduInfo.szLocalMduId, VOD_MAX_ID_LEN);
		strncpy(srvAddrinfo.strRemoteMduID, m_mduInfo.szRemoteMduId, VOD_MAX_ID_LEN);
		memset(srvAddrinfo.strDevDomainID, 0, sizeof(srvAddrinfo.strDevDomainID));
		if(FILETYPE_REC_PU == m_nFrontOrCen|| FILETYPE_PIC_PU == m_nFrontOrCen)
		{
			strncpy(srvAddrinfo.strDevDomainID, m_guInfo.DomainID, VOD_MAX_ID_LEN);
		}
		else if(FILETYPE_REC_VOD == m_nFrontOrCen || FILETYPE_PIC_VOD == m_nFrontOrCen)
		{
			strncpy(srvAddrinfo.strDevDomainID, (LPSTR)(LPCSTR)m_strMsuDomainID.GetBuffer(m_strMsuDomainID.GetLength()), VOD_MAX_ID_LEN);
		}


		if(m_guInfo.DomainType != 0)
		{
			//还需要远程的CSGIP与端口，在查询路由时，需要得到。
			srvAddrinfo.lRemoteCsgAddr.S_un.S_addr = inet_addr(m_mduInfo.szRemoteCsgIp);
			srvAddrinfo.usRemoteCsgPort = htons(m_mduInfo.uRemoteCsgPort+PORT_CSG_INCREASE_NUM);
			srvAddrinfo.lRemoteMduAddr.S_un.S_addr = inet_addr(m_mduInfo.szRemoteMduIp);
			srvAddrinfo.usRemoteMduPort = htons(m_mduInfo.uRemoteMduPort+VOD_BASE_MDU_OFFSET);
		}
		
		HANDLE hSession = st_vod_createSession(srvAddrinfo);
		if(hSession == NULL)
		{
			strMsg.Format(_T("创建会话失败, MDU IP:%s"), m_mduInfo.szLocalMduIp);
			GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strMsg);
		}
		else
		{
			HANDLE hVideo = NULL;
			if(FILETYPE_REC_PU == m_nFrontOrCen|| FILETYPE_PIC_PU == m_nFrontOrCen)
			{
				hVideo = st_vod_openVideo(hSession, FALSE, LPCSTR(m_strPuid.GetBuffer(m_strPuid.GetLength())), LPCSTR(m_strFile.GetBuffer(m_strFile.GetLength())));
			}
			else if(FILETYPE_REC_VOD == m_nFrontOrCen || FILETYPE_PIC_VOD == m_nFrontOrCen )
			{
				hVideo = st_vod_openVideo(hSession, TRUE, LPCSTR(m_strMsuID.GetBuffer(m_strMsuID.GetLength())), LPCSTR(m_strFile.GetBuffer(m_strFile.GetLength())));
			}
			else
			{
				AfxMessageBox(_T("下载类型错误！"));
				return TRUE;
			}


			if(hVideo == NULL)
			{	
				//strMsg.Format("打开文件失败:%s", (LPCTSTR)m_strFile);
				strMsg = "打开文件失败,";
				strMsg += m_strFile;
				GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strMsg);
				st_vod_destroySession(hSession);
			}
			else
			{
				m_hSession = hSession;
				m_hVideo   = hVideo;
				
				VOD_CLIENTINFO Info;
				Info.lHandle = (long)this;
				Info.lpFunc  = CallBack_VodDownLaod;

				st_vod_attachToFile(m_hVideo, m_guInfo.lManufactType, LPCSTR(m_strFileSave.GetBuffer(m_strFileSave.GetLength())));
				st_vod_registerCallback(hVideo, Info);
				st_vod_setDownload(hVideo);
				st_vod_play(hVideo);
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDownloadDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}

LRESULT CFileDownloadDlg::ProcessNotify(WPARAM wParam, LPARAM lParam)
{
	CString strLoadText;
	int nPos = (int)wParam;  // 进度值(0--10000)
	if(GetTickCount() - m_dwLastTime < 1000  && nPos < 10001 )
		return 0;

	m_dwLastTime = GetTickCount();
	if(nPos >= 0 && nPos <= 10000)
	{
		m_ctrlDownloadProgress.SetPos(nPos);
		char szText[32] = {0};
		sprintf(szText, "%3d%%", nPos*100/10000);
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText(/*(const unsigned short *)*/szText);
	}

	if( nPos > 10000) // finished
	{
		m_ctrlDownloadProgress.SetPos(10000);
		SetWindowText(_T("已完成！"));

        GetDlgItem(IDC_BUTTON_CANCEL)->SetWindowText(_T("确定"));
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("100%"));
        if (((CButton *)GetDlgItem(IDC_CHECK_AUTO_CLOSE))->GetCheck() == 1)
        {
           OnButtonCancel();
        }
        
	}
	else if(nPos < 0)
	{
		SetWindowText(_T("下载失败，请重试！"));
        GetDlgItem(IDC_BUTTON_CANCEL)->SetWindowText(_T("确定"));

	}

	return 0;
}

void CFileDownloadDlg::StopMission()
{
	if(m_hSession)
	{
		if(m_hVideo)
		{
			st_vod_stop(m_hVideo);
			st_vod_closeVideo(m_hSession, m_hVideo);
			m_hVideo = NULL;
		}
		st_vod_destroySession(m_hSession);
		m_hSession = NULL;
	}
}

void CFileDownloadDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	StopMission();
 	CDialog::OnCancel();
	DestroyWindow();
}
