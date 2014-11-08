// DlgPlayList.cpp : implementation file
//

#include "stdafx.h"
#include "cuocx.h"
#include "DlgPlayList.h"
#include "MainPage.h"
#include "NetVodDlg.h"
#include "DlgPicView.h"
#include "FileDownloadDlg.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayList dialog

#define IDM_PLAY (WM_USER + 1)
#define IDM_DOWNLOAD (WM_USER + 2)

CDlgPlayList::CDlgPlayList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlayList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pGuInfo = NULL;
	m_szPuid = "";
	m_szGuName = "";
	m_szGuid = "";

	m_pMainPage = NULL;
}


void CDlgPlayList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayList)
	DDX_Control(pDX, IDC_LIST_FILES, m_ctrlListRecord);
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_ctrlRecordType);
	DDX_Control(pDX, IDC_COMBO_RECORD_SRC, m_ctrlRecordSrc);
	DDX_Control(pDX, IDC_COMBO_RECORD_SERVER, m_ctrlRecordServer);
	DDX_Control(pDX, IDC_BUTTON_QUERY_PIC, m_ctrlQueryPic);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_ctrlQuery);
	DDX_Text(pDX, IDC_EDIT_PUID, m_szPuid);
	DDX_Text(pDX, IDC_EDIT_GUNAME, m_szGuName);
	DDX_Text(pDX, IDC_EDIT_GUID, m_szGuid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_tStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_tEndTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE, m_tDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayList, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayList)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_PIC, OnButtonQueryPic)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORD_SERVER, OnSelchangeComboRecordServer)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORD_SRC, OnSelchangeComboRecordSrc)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FILES, OnRclickListFiles)
	ON_COMMAND(IDM_PLAY,OnMenuPlay)
	ON_COMMAND(IDM_DOWNLOAD,OnMenuDownLoad)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayList message handlers

///=== ��ʼ�� Combobox =====================================================///
void CDlgPlayList::InitCmbCtrls()
{
	//---------------------------------------
	// ¼����Դ
	//---------------------------------------
	m_ctrlRecordSrc.AddString(_T("����"));
	m_ctrlRecordSrc.AddString(_T("ǰ���豸"));
	m_ctrlRecordSrc.AddString(_T("��������"));
	
	m_ctrlRecordSrc.SetCurSel(2);
	SendMessage(WM_COMMAND, MAKEWPARAM(m_ctrlRecordSrc.GetDlgCtrlID(), CBN_SELCHANGE), (LPARAM)m_ctrlRecordSrc.GetSafeHwnd());
	
	
    //----------------------------------------
	// ¼������
	//----------------------------------------
	m_ctrlRecordType.AddString(_T("����¼��"));
	m_ctrlRecordType.AddString(_T("��ʱ¼��"));
	m_ctrlRecordType.AddString(_T("����¼��"));
	m_ctrlRecordType.AddString(_T("�ֶ�¼��"));
	
	m_ctrlRecordType.SetCurSel(0);
	SendMessage(WM_COMMAND, MAKEWPARAM(m_ctrlRecordType.GetDlgCtrlID(), CBN_SELCHANGE), (LPARAM)m_ctrlRecordType.GetSafeHwnd());
	
}

BOOL CDlgPlayList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// 	InitCmbCtrls();
	
	if ( m_pGuInfo != NULL )
	{
		m_szPuid = m_pGuInfo->PUID;
		m_szGuid = m_pGuInfo->GUID;
		m_szGuName = m_pGuInfo->GUName;
	}
	
	InitListCtrlHeaders();
	
	CTime time = CTime::GetCurrentTime();
	m_tDate = time;
	m_tStartTime = CTime(time.GetYear(),time.GetMonth(), time.GetDay(), 0, 0, 0);
	m_tEndTime = CTime(time.GetYear(),time.GetMonth(), time.GetDay(), 23, 59, 59);
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPlayList::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int nConnt = m_ctrlListRecord.GetItemCount();
	if ( nConnt > 0)
	{
		m_ctrlListRecord.DeleteAllItems();
	}
	
	if(m_szPuid.IsEmpty() || m_szGuid.IsEmpty() || m_szGuName.IsEmpty())
	{
		return;
	}

	  //��������Ϣ,��������Դ��
    int iIndex = m_ctrlRecordServer.GetCurSel();
	if ( iIndex != -1 )
	{
		m_vod_info = m_vodServerInfo[iIndex];
	}
	

    CString strLoadText;
	SYSTEMTIME stStart, stEnd;       // ��ѯ��ʼʱ��ͽ���ʱ��
	stStart.wYear = m_tDate.GetYear();
	stStart.wMonth = m_tDate.GetMonth();
	stStart.wDay = m_tDate.GetDay();
	stStart.wHour = m_tStartTime.GetHour();
	stStart.wMinute = m_tStartTime.GetMinute();
	stStart.wSecond = m_tStartTime.GetSecond();

	stEnd.wYear = m_tDate.GetYear();
	stEnd.wMonth = m_tDate.GetMonth ();
	stEnd.wDay = m_tDate.GetDay();
	stEnd.wHour = m_tEndTime.GetHour();
	stEnd.wMinute = m_tEndTime.GetMinute();
	stEnd.wSecond = m_tEndTime.GetSecond();

	m_iRecordSrcType = m_ctrlRecordSrc.GetCurSel();



#if 1
	// TODO: Add your control notification handler code here

	  //¼����Դ---
	int iRecordSrc = m_iRecordSrcType; 
	switch(iRecordSrc) 
	{
	case 0: //���ؼ����
		{
			CString strPath = _T("");
			char strTemp[MAX_PATH];
			GetCurrentDirectory(MAX_PATH,/*(unsigned short *)*/strTemp);
			strPath.Format(_T("%s\\%s\\Record\\%04d%02d%02d"),  strTemp,m_szGuName,
				m_tDate.GetYear(),m_tDate.GetMonth (),m_tDate.GetDay());  // ¼���ļ�λ��
			
			if ( m_szPuid == _T("") || m_szGuid ==_T(""))
			{
				return;
			}
			
			SearchFileToList(m_szGuName,strPath,stStart,stEnd);

			m_ctrlListRecord.SetColumnWidth(1, 150);
			m_ctrlListRecord.SetColumnWidth(2, 150);
			m_ctrlListRecord.SetColumnWidth(3, 150);
			m_ctrlListRecord.SetColumnWidth(4, 150);
			m_ctrlListRecord.SetColumnWidth(5, 100);
			m_ctrlListRecord.SetColumnWidth(6, 100);
			m_ctrlListRecord.SetColumnWidth(7, 0);
			m_ctrlListRecord.SetColumnWidth(8, 0);

			SetBaseInfo(FILETYPE_REC_LOCAL, m_pGuInfo, &m_vod_info);
			
		}
		break;
	case 1: //ǰ���豸
		{
			if( m_szPuid == _T("") || m_szGuid ==_T(""))
			{
				return;
			}
			
			m_iSearchType = m_ctrlRecordType.GetCurSel();
			int nSearchType = m_iSearchType;
			CU_NET_LIB::GuFileInfo FileInfo[256]={0};
			int iFileCount=0;
			if (CU_NET_LIB::QueryGuFileLists(g_dwServerId, *m_pGuInfo, 0, nSearchType,&stStart,&stEnd,FileInfo,256,&iFileCount) < 0)
			{
				AfxMessageBox(_T("��ѯʧ��, ���糬ʱ����������ԣ�"));
				return;
			}
			else
			{
				int nFileIndex = iFileCount; //��������
				m_ctrlListRecord.SetRedraw(FALSE);
				for (int i = 0 ; i < iFileCount ; i ++)
				{
					nFileIndex--;
					CString strFile = FileInfo[nFileIndex].file;
					CString strSize;
					strSize.Format(_T("%u KB"), FileInfo[nFileIndex].size/1024);
					
					char szIndex[32];
					int nCount = m_ctrlListRecord.GetItemCount();
					sprintf(szIndex, (const char *)_T("%05d"), nCount);
					
					m_ctrlListRecord.InsertItem(nCount, /*(unsigned short *)*/szIndex, 0);
					m_ctrlListRecord.SetItemState(nCount, INDEXTOSTATEIMAGEMASK(1),  LVIS_STATEIMAGEMASK);

					m_ctrlListRecord.SetColumnWidth(1, 0);
					m_ctrlListRecord.SetColumnWidth(2, 0);
					m_ctrlListRecord.SetColumnWidth(3, 0);	
					m_ctrlListRecord.SetColumnWidth(4, 200);
					m_ctrlListRecord.SetColumnWidth(5, 80);
					m_ctrlListRecord.SetColumnWidth(6, 100);
					m_ctrlListRecord.SetColumnWidth(7, 200);
					m_ctrlListRecord.SetColumnWidth(8, 0);
					
					CString strModify;
					ResetFileName(1, strFile, strModify);
					m_ctrlListRecord.SetItemText(nCount, 8, strFile);		// �ļ�ȫ·��
					m_ctrlListRecord.SetItemText(nCount, 4, strModify);     // �ļ���
					m_ctrlListRecord.SetItemText(nCount, 5, strSize);       // �ļ���С
					m_ctrlListRecord.SetItemText(nCount, 6, _T("PU"));          // ��ѯλ��
					int iType1 = FileInfo[i].type & 0x00000001;
					int iType2 = (FileInfo[i].type & 0x00000002)>>1;
					int iType3 = (FileInfo[i].type & 0x00000004)>>2;
					CString strFileType, strTmpType;
					strFileType.Empty();
					if (iType1 == 1)
					{
						strFileType.Format(_T(" %s"), _T("�ֶ�"));
						//strLoadText.LoadString(IDS_STRING_MANUAL);
						//strLoadText=IDS_WINTEXT_1524;
                        //strFileType.Format(" %s", strLoadText);
					}
					if (iType2 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), _T("��ʱ"));
							//strLoadText.LoadString(IDS_STRING_REGULAR);
							//strLoadText=IDS_WINTEXT_1525;
                            //strFileType.Format(" %s", strLoadText);
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							//strFileType.Format("%s/%s", strTmpType, "��ʱ");
							//strLoadText.LoadString(IDS_STRING_REGULAR);
							//strLoadText=IDS_WINTEXT_1525;
                            //strFileType.Format("%s/%s", strTmpType, strLoadText);
						}
					}
					if (iType3 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), _T("����"));
							//strLoadText.LoadString(IDS_STRING_ALARM);
							//strLoadText=IDS_WINTEXT_1526;
                            //strFileType.Format(" %s", strLoadText);
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							//strFileType.Format("%s/%s", strTmpType, "�澯");
                            //strLoadText.LoadString(IDS_STRING_ALARM);
							//strLoadText=IDS_WINTEXT_1526;
							//strFileType.Format("%s/%s", strTmpType, strLoadText);
						}
					}
					m_ctrlListRecord.SetItemText(nCount, 7, strFileType);            // ����
				}
				m_ctrlListRecord.SetRedraw(TRUE);
			}
			SetBaseInfo(FILETYPE_REC_PU, m_pGuInfo, &m_vod_info);
		}
		break;
	case 2: //��������
		{	
			HRESULT hr;
			CU_NET_LIB::MDU_ROUTE_INFO mduInfo;
			memset(&mduInfo, 0, sizeof(CU_NET_LIB::MDU_ROUTE_INFO));
			ASSERT(m_pGuInfo);

			hr = CU_NET_LIB::QueryPuRealRoute(g_dwServerId, *m_pGuInfo, mduInfo);
			if( ST_OK != hr)
			{
				AfxMessageBox(_T("��ѯPU·��ʧ��"));
				return;
			}

			//////////////////////////////////////////////////////////////////////////
			CSrvAddrInfo srvAddrinfo;	//3
			memset(&srvAddrinfo, 0, sizeof(CSrvAddrInfo));
			char szServerIp[256]={0};

			  //��ַ
			CMainPage* pMainDlg = m_pMainPage;
			sprintf(szServerIp, (const char *)pMainDlg->m_strServerIPAddr);

			ParseDomain(szServerIp);

			  //�׽��ֵ�ַ,�˿�
			srvAddrinfo.lLocalCsgAddr.S_un.S_addr = inet_addr(szServerIp);
			srvAddrinfo.usLocalCsgPort = htons(pMainDlg->m_nServerPort+PORT_CSG_INCREASE_NUM);

			srvAddrinfo.lLocalMduAddr.S_un.S_addr = inet_addr(mduInfo.szLocalMduIp);
			srvAddrinfo.usLocalMduPort = htons(mduInfo.uLocalPort+VOD_BASE_MDU_OFFSET);		

			strncpy(srvAddrinfo.strLocalMduID, mduInfo.szLocalMduId, VOD_MAX_ID_LEN);
			strncpy(srvAddrinfo.strRemoteMduID, mduInfo.szRemoteMduId, VOD_MAX_ID_LEN);

			memset(srvAddrinfo.strDevDomainID, 0, sizeof(srvAddrinfo.strDevDomainID));		
			strncpy(srvAddrinfo.strDevDomainID, m_vod_info.szDomainID, VOD_MAX_ID_LEN);

			if(m_pGuInfo->DomainType != 0)
			{
				//����ҪԶ�̵�CSGIP��˿ڣ��ڲ�ѯ·��ʱ����Ҫ�õ���
				srvAddrinfo.lRemoteCsgAddr.S_un.S_addr = inet_addr(mduInfo.szRemoteCsgIp);
				srvAddrinfo.usRemoteCsgPort = htons(mduInfo.uRemoteCsgPort+PORT_CSG_INCREASE_NUM);
				srvAddrinfo.lRemoteMduAddr.S_un.S_addr = inet_addr(mduInfo.szRemoteMduIp);
				srvAddrinfo.usRemoteMduPort = htons(mduInfo.uRemoteMduPort+VOD_BASE_MDU_OFFSET);
			}


			//////////////////////////////////////////////////////////////////////////
			HANDLE hSession = st_vod_createSession(srvAddrinfo);
			if(hSession == NULL)
			{
				return;
			}
					
			vector<CFileInfo> vectList;
			vectList.reserve(1000);
			
			  //¼������
			m_iSearchType = GetSearchType();
			int nSearchType = m_iSearchType; 	

			BOOL bOK = st_vod_getFileList(hSession, (const char *)m_szGuid.GetBuffer(m_szGuid.GetLength()), nSearchType, m_vod_info.szVodID, &stStart, &stEnd, vectList);
			if ( !bOK ) 
			{
				AfxMessageBox(_T("��ѯʧ��,�����ԣ�"));

				return;
			}
			else
			{
				m_ctrlListRecord.SetRedraw(FALSE);
				std::sort(vectList.begin(), vectList.end(), MyComp());
				ULONG64 nSize = vectList.size();
				for(int i=0; i< nSize; i++)
				{        
					CString strFile = vectList[i].file;
					CString strSize;
					strSize.Format(_T("%u KB"), vectList[i].size/1024);
					
					char szIndex[32];
					int nCount = m_ctrlListRecord.GetItemCount();
					sprintf(szIndex, (const char *)_T("%05d"), nCount);
					
					m_ctrlListRecord.InsertItem(nCount, /*(unsigned short *)*/szIndex, 0);
					m_ctrlListRecord.SetItemState(nCount, INDEXTOSTATEIMAGEMASK(1),  LVIS_STATEIMAGEMASK);

					m_ctrlListRecord.SetColumnWidth(1, 0);
					m_ctrlListRecord.SetColumnWidth(2, 0);
					m_ctrlListRecord.SetColumnWidth(3, 0);	
					m_ctrlListRecord.SetColumnWidth(4, 200);
					m_ctrlListRecord.SetColumnWidth(5, 80);
					m_ctrlListRecord.SetColumnWidth(6, 100);
					m_ctrlListRecord.SetColumnWidth(7, 200);
					m_ctrlListRecord.SetColumnWidth(8, 0);
					
					CString strModify;
					ResetFileName(1, strFile, strModify);
					m_ctrlListRecord.SetItemText(nCount, 8, strFile);		  // �ļ�ȫ·��
					m_ctrlListRecord.SetItemText(nCount, 4, strModify);     // �ļ���
					m_ctrlListRecord.SetItemText(nCount, 5, strSize);       // �ļ���С
					m_ctrlListRecord.SetItemText(nCount, 6, _T("VOD"));         // ��ѯλ��
					int iType1 = vectList[i].type & 0x00000001;
					int iType2 = (vectList[i].type & 0x00000002)>>1;
					int iType3 = (vectList[i].type & 0x00000004)>>2;
					CString strFileType, strTmpType;
					strFileType.Empty();
					if (iType1 == 1)
					{
						strFileType.Format(_T(" %s"), _T("�ֶ�"));

					}
					if (iType2 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), _T("��ʱ"));
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							strFileType.Format(_T("%s/%s"), strTmpType, _T("��ʱ"));
						}
					}
					if (iType3 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), _T("�澯"));
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							strFileType.Format(_T("%s/%s"), strTmpType, _T("����"));
						}
					}
					m_ctrlListRecord.SetItemText(nCount, 7, strFileType);            // ����
				}
				m_ctrlListRecord.SetRedraw();

			}
			st_vod_destroySession(hSession);

			SetBaseInfo(FILETYPE_REC_VOD, m_pGuInfo, &m_vod_info);
		}
		break;
	default:
		break;
	}

#endif	
}

void CDlgPlayList::SearchFileToList(LPCTSTR lpszID, LPCTSTR lpszPath,COleDateTime StartDate,
									  COleDateTime EndDate)
{
	//���Ȳ�ѯ�ֶ�¼���ļ�
	CString  strPath = lpszPath;
	CFileFind  finder;
	CString strLoadText;
	if(strPath.Right(1) != _T("\\"))
	{
		strPath += "\\*.*";
	}
	else
		strPath += "*.*";
	
	m_ctrlListRecord.SetRedraw(FALSE);
	int bWorking = finder.FindFile(strPath, 0);
	//int iRtn = GetLastError();
	

	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDots())
			continue;
		if(finder.IsDirectory())
		{
			//CString strPath = finder.GetFilePath();
			//SearchFileToList(lpszID, strPath);
			continue;
		}
		else
		{
			CString strFile = finder.GetFilePath();
			CString strPostfix;
			strPostfix = strFile.Right(3);
			if (strPostfix.CompareNoCase(_T("bmp")) == 0 || strPostfix.CompareNoCase(_T("jpg")) == 0 || 
				strPostfix.CompareNoCase(_T("dat")) == 0 || strPostfix.CompareNoCase(_T("avi")) == 0 ||
				strPostfix.CompareNoCase(_T(".hk")) == 0)
			{		
				CString strSize;
				strSize.Format(_T("%u KB"), finder.GetLength()/1024);
				
				char szIndex[32];
				int nCount = m_ctrlListRecord.GetItemCount();
				sprintf(szIndex, (const char *)_T("%05d"), nCount);
				
				CTime time1, time2;
				CString strStartTime, strEndTime;
				finder.GetCreationTime(time1);
				finder.GetLastWriteTime(time2);
				strStartTime = time1.Format(_T("%Y-%m-%d %H:%M:%S"));
				strEndTime = time2.Format(_T("%Y-%m-%d %H:%M:%S"));
				
				int iStart = time1.GetHour()*3600 + time1.GetMinute()*60 + time1.GetSecond() - StartDate.GetHour()*3600 - StartDate.GetMinute()*60 - StartDate.GetSecond();
				int iEnd = time1.GetHour()*3600 + time1.GetMinute()*60 + time1.GetSecond() - EndDate.GetHour()*3600 - EndDate.GetMinute()*60 - EndDate.GetSecond();
				if (iStart>=0 && iEnd<=0)
				{
					m_ctrlListRecord.InsertItem(nCount, /*(unsigned short *)*/szIndex, 0);
					m_ctrlListRecord.SetItemState(nCount, INDEXTOSTATEIMAGEMASK(1),  LVIS_STATEIMAGEMASK);
					
					CString strModify;
					ResetFileName(0, strFile, strModify);
					m_ctrlListRecord.SetItemText(nCount, 8, strFile);		  // �ļ�ȫ·��
					m_ctrlListRecord.SetItemText(nCount, 1, lpszID);
					m_ctrlListRecord.SetItemText(nCount, 2, strStartTime);  // ��ʼʱ��
					m_ctrlListRecord.SetItemText(nCount, 3, strEndTime);    // ֹͣʱ��
					m_ctrlListRecord.SetItemText(nCount, 4, strModify);     // �ļ���
					m_ctrlListRecord.SetItemText(nCount, 5, strSize);       // �ļ���С
					m_ctrlListRecord.SetItemText(nCount, 6, _T("����"));        // ��ѯλ��
					//strLoadText.LoadString(IDS_STRING_LOCAL);
					//strLoadText=IDS_WINTEXT_1528;
                    //m_ctrlListRecord.SetItemText(nCount, 6, strLoadText);        // ��ѯλ��
					m_ctrlListRecord.SetItemText(nCount, 7, _T(""));            // ����
					//m_ListFile.SetItemText(nCount, 8, strFile);     // �ļ���
				}
			}
		}
	}
	m_ctrlListRecord.SetRedraw();
	finder.Close();
	//��ѯ��ʱ¼���ļ�
	TimeRec_FileInfo_t FileInfo[1024];
	int nTimeFileCount = 0;
	ZeroMemory(FileInfo, sizeof(TimeRec_FileInfo_t)*1024);

	TimeRec_Day_t yymmdd;
	yymmdd.year = StartDate.GetYear();
	yymmdd.month = StartDate.GetMonth();
	yymmdd.day = StartDate.GetDay();

	TimeRec_Time_t startTime,endTime;
	ZeroMemory(&startTime, sizeof(TimeRec_Time_t));
	startTime.hour = StartDate.GetHour();
	startTime.minute = StartDate.GetMinute();
	startTime.second = StartDate.GetSecond();
	ZeroMemory(&endTime, sizeof(TimeRec_Time_t));
	endTime.hour = EndDate.GetHour();
	endTime.minute = EndDate.GetMinute();
	endTime.second = EndDate.GetSecond();

	//((CMainFrame *)AfxGetMainWnd())->m_pTimeRec->FindFile((LPTSTR)(LPCTSTR)m_szGuName, yymmdd, startTime, endTime, FileInfo, &nTimeFileCount);
    if (nTimeFileCount > 0)
    {
		int nHaveFileCount = m_ctrlListRecord.GetItemCount();
		for (int i = nHaveFileCount; i < nTimeFileCount + nHaveFileCount; i++)
		{
			CString strSize;
			strSize.Format(_T("%u KB"), FileInfo[i-nHaveFileCount].dwFileSize/1024);

			char szIndex[32];
			sprintf(szIndex, "%05d", i);
			m_ctrlListRecord.InsertItem(i, /*(const unsigned short *)*/szIndex, 0);
			m_ctrlListRecord.SetItemState(i, INDEXTOSTATEIMAGEMASK(1),  LVIS_STATEIMAGEMASK);
			
			CString strModify;
			ResetFileName(0, /*(const unsigned short *)*/FileInfo[i-nHaveFileCount].filepath, strModify);
			m_ctrlListRecord.SetItemText(i, 8, /*(const unsigned short *)*/FileInfo[i-nHaveFileCount].filepath);		  // �ļ�ȫ·��
			m_ctrlListRecord.SetItemText(i, 1, lpszID);
			m_ctrlListRecord.SetItemText(i, 2, /*(const unsigned short *)*/FileInfo[i-nHaveFileCount].szCreateTime);  // ��ʼʱ��
			m_ctrlListRecord.SetItemText(i, 3, /*(const unsigned short *)*/FileInfo[i-nHaveFileCount].szLastWriteTime);    // ֹͣʱ��
			m_ctrlListRecord.SetItemText(i, 4, strModify);     // �ļ���
 			m_ctrlListRecord.SetItemText(i, 5, strSize);       // �ļ���С
			m_ctrlListRecord.SetItemText(i, 6, _T("����"));        // ��ѯλ��
			//strLoadText.LoadString(IDS_STRING_LOCAL);
			//strLoadText=IDS_WINTEXT_1528;
            //m_ctrlListRecord.SetItemText(i, 6, strLoadText);        // ��ѯλ��
			m_ctrlListRecord.SetItemText(i, 7, _T(""));            // ����
		}
    }
}

///=== ���������Ϣ =================================================================///
//
void CDlgPlayList::SetBaseInfo(int nType, CU_NET_LIB::GUINFO *pGuInfo, CU_NET_LIB::VODSERVER_INFO *pVodInfo)
{
	m_nType = nType;
	//ZeroMemory(&m_guInfo, sizeof(GUINFO));
	//ZeroMemory(&m_vod_info, sizeof(VODSERVER_INFO));
	memcpy(&m_guInfo, pGuInfo, sizeof(CU_NET_LIB::GUINFO));
	memcpy(&m_vod_info, pVodInfo, sizeof(CU_NET_LIB::VODSERVER_INFO));
}

///=== �����ļ��� ==================================================================///
//
void CDlgPlayList::ResetFileName(int iType, LPCTSTR lpszPathName, CString &strFileName)
{
	CString str;
	str.Format(_T("%s"), lpszPathName);
	int iLen;
	if (iType == 0)
	{
		iLen = strlen((const char *)lpszPathName)-str.ReverseFind('\\')-1;
	}
	else
	{
		iLen = strlen((const char *)lpszPathName)-str.ReverseFind('/')-1;
	}
	
	if ( iLen < 5)
		return;
	
	strFileName = str.Right(iLen);
	if (strFileName.Right(3).Compare(_T("dat")) == 0)
	{
		strFileName.Delete(strFileName.GetLength() - 3, 3);
		strFileName += _T("avi");
	}
}





///=== ��������ת�ɵ�ַ ============================================///
//
BOOL CDlgPlayList::ParseDomain(char* szDomainName)
{ 
	CString strIP;
	struct hostent * hp;
	char szIP[128] = {0};
	if ((hp = gethostbyname(szDomainName)) != NULL)//������������ip��ȡ��Ӧ��IP��ַ
	{
		struct in_addr inAddr;
		LPSTR  lpAddr = hp->h_addr_list[0];
		if(lpAddr)     
		{
			//struct in_addr inAddr;   
			memmove(&inAddr, lpAddr, 4);   
			strIP = inet_ntoa(inAddr);   
			if(strIP.IsEmpty())
			{
				strIP =  _T("Not available");
			}
			sprintf(szIP, "%s", strIP);
		}
	}
	else
	{
		int nRes = WSAGetLastError();
		return FALSE;
	}
	
	//this->m_strServerIP.Format("%s", szIP);
	sprintf(szDomainName, szIP);
	
	return TRUE;
}






///===��ѯͼƬ=============================================================///
//
void CDlgPlayList::OnButtonQueryPic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	// ��ȡ��������Ϣ---
    int iIndex = m_ctrlRecordServer.GetCurSel();
	if ( iIndex != -1 )
	{
		m_vod_info = m_vodServerInfo[iIndex];
	}
	
	
	if(m_szPuid.IsEmpty() || m_szGuid.IsEmpty() || m_szGuName.IsEmpty())
	{
		return;
	}

	
	m_ctrlListRecord.DeleteAllItems(); //���²�ѯ
    CString  strLoadText;
	SYSTEMTIME stStart, stEnd;   // ��ѯ��ʼʱ��ͽ���ʱ��
	stStart.wYear = m_tDate.GetYear();
	stStart.wMonth = m_tDate.GetMonth();
	stStart.wDay = m_tDate.GetDay();
	stStart.wHour = m_tStartTime.GetHour();
	stStart.wMinute = m_tStartTime.GetMinute();
	stStart.wSecond = m_tStartTime.GetSecond();

	stEnd.wYear = m_tDate.GetYear();
	stEnd.wMonth = m_tDate.GetMonth ();
	stEnd.wDay = m_tDate.GetDay();
	stEnd.wHour = m_tEndTime.GetHour();
	stEnd.wMinute = m_tEndTime.GetMinute();
	stEnd.wSecond = m_tEndTime.GetSecond();

	// TODO: Add your control notification handler code here
	int iRecordSrc = m_ctrlRecordSrc.GetCurSel();
	switch(iRecordSrc) 
	{
	case 0: //���ص���
		{
			CString strPath = _T("");
			strPath.Format(_T(".\\%s\\Picture\\%04d%02d%02d"), m_szGuName,
				m_tDate.GetYear(),m_tDate.GetMonth (),m_tDate.GetDay());  // ͼƬ�ļ�λ��
			
			if ( m_szPuid == _T("") || m_szGuid ==_T(""))
			{
				return;
			}
			
			SearchFileToList(m_szGuName,strPath,stStart,stEnd);

			m_ctrlListRecord.SetColumnWidth(1, 300);
			m_ctrlListRecord.SetColumnWidth(2, 150);
			m_ctrlListRecord.SetColumnWidth(3, 150);
			m_ctrlListRecord.SetColumnWidth(4, 350);
			m_ctrlListRecord.SetColumnWidth(5, 0);
			m_ctrlListRecord.SetColumnWidth(6, 0);
			m_ctrlListRecord.SetColumnWidth(7, 0);
			m_ctrlListRecord.SetColumnWidth(8, 0);
						
			SetBaseInfo(FILETYPE_PIC_LOCAL, m_pGuInfo, &m_vod_info);
		}
		break;
	case 1: //ǰ���豸
		{
			if( m_szPuid == _T("") || m_szGuid ==_T(""))
			{
				return;
			}
			
			int nSearchType = m_iSearchType;
			CU_NET_LIB::GuFileInfo FileInfo[256]={0};
			int iFileCount=0;
			if (CU_NET_LIB::QueryGuFileLists(g_dwServerId, *m_pGuInfo, 1, 7/*archType*/, &stStart,&stEnd,FileInfo,256,&iFileCount) < 0)
			{
				AfxMessageBox(_T("��ѯ����� ��ѯ�б�ʧ�ܣ����糬ʱ����������ԣ�"));
				return;
			}
			else
			{
				m_ctrlListRecord.SetRedraw(FALSE);
				for (int i = 0 ; i < iFileCount ; i ++)
				{
					CString strFile = FileInfo[i].file;
					CString strSize;
					strSize.Format(_T("%u KB"), FileInfo[i].size/1024);
					
					char szIndex[32];
					int nCount = m_ctrlListRecord.GetItemCount();
					sprintf(szIndex, "%05d", nCount);
					
					m_ctrlListRecord.InsertItem(nCount, /*(const unsigned short *)*/szIndex, 0);
					m_ctrlListRecord.SetItemState(nCount, INDEXTOSTATEIMAGEMASK(1),  LVIS_STATEIMAGEMASK);

					m_ctrlListRecord.SetColumnWidth(1, 0);
					m_ctrlListRecord.SetColumnWidth(2, 0);
					m_ctrlListRecord.SetColumnWidth(3, 0);	
					m_ctrlListRecord.SetColumnWidth(4, 200);
					m_ctrlListRecord.SetColumnWidth(5, 80);
					m_ctrlListRecord.SetColumnWidth(6, 80);
					m_ctrlListRecord.SetColumnWidth(7, 80);
					m_ctrlListRecord.SetColumnWidth(8, 0);
					
					CString strModify;
					ResetFileName(1, strFile, strModify);
					m_ctrlListRecord.SetItemText(nCount, 8, strFile);		  // �ļ�ȫ·��
					m_ctrlListRecord.SetItemText(nCount, 4, strModify);     // �ļ���
					m_ctrlListRecord.SetItemText(nCount, 5, strSize);       // �ļ���С
					m_ctrlListRecord.SetItemText(nCount, 6, _T("PU"));         // ��ѯλ��
					int iType1 = FileInfo[i].type & 0x00000001;
					int iType2 = (FileInfo[i].type & 0x00000002)>>1;
					int iType3 = (FileInfo[i].type & 0x00000004)>>2;
					CString strFileType, strTmpType;
					strFileType.Empty();
					if (iType1 == 1)
					{
						strFileType.Format(_T(" %s"), "�ֶ�");
					}
					if (iType2 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), "��ʱ");
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							strFileType.Format(_T("%s/%s"), strTmpType, "��ʱ");
						}
					}
					if (iType3 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), "����");
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							strFileType.Format(_T("%s/%s"), strTmpType, "�澯");
						}
					}
					m_ctrlListRecord.SetItemText(nCount, 7, strFileType);            // ����
				}
				m_ctrlListRecord.SetRedraw(TRUE);

				//SetBaseInfo(FILETYPE_PIC_PU, m_pGuInfo, &m_vod_info);
			}
		}
		break;
	case 2: //��������
		{	
		//	m_ctrlListRecord.SetBaseInfo(FILETYPE_PIC_VOD, m_pGuInfo, &m_vod_info);
			if( m_szPuid == _T("") || m_szGuid ==_T(""))
			{
				return;
			}

			CU_NET_LIB::MDU_ROUTE_INFO mduInfo;
			memset(&mduInfo, 0, sizeof(CU_NET_LIB::MDU_ROUTE_INFO));
			HRESULT hr = CU_NET_LIB::QueryPuRealRoute(g_dwServerId, *m_pGuInfo, mduInfo);
			if( ST_OK != hr)
			{
				AfxMessageBox(_T("��ѯPU·��ʧ�ܣ�������"));
				return;
			}

			// ����ѡ����Ʋ�ѯʱ��
			SYSTEMTIME stTemp;
			stTemp = stStart;
			afx_addNDays(&stTemp, 7);
					
			// ��ѯGU��Ӧ��VOD Server
			char szVodIp[64] = {0};
			if( _T("") == m_strVodIp)
			{
				return;
			}	
			strncpy(szVodIp, (const char *)m_strVodIp.GetBuffer(m_strVodIp.GetLength()), sizeof(szVodIp) - 1);

			//////////////////////////////////////////////////////////////////////////
			CSrvAddrInfo srvAddrinfo;	//3
			memset(&srvAddrinfo, 0, sizeof(CSrvAddrInfo));
			char szServerIp[256]={0};

			CMainPage* pDlg = m_pMainPage;
			sprintf(szServerIp, (LPSTR)(LPCSTR)pDlg->m_strServerIPAddr.GetBuffer(pDlg->m_strServerIPAddr.GetLength()));

			ParseDomain(szServerIp);
			srvAddrinfo.lLocalCsgAddr.S_un.S_addr = inet_addr(szServerIp);

			srvAddrinfo.usLocalCsgPort = htons(pDlg->m_nServerPort+PORT_CSG_INCREASE_NUM);

			srvAddrinfo.lLocalMduAddr.S_un.S_addr = inet_addr(mduInfo.szLocalMduIp);
			srvAddrinfo.usLocalMduPort = htons(mduInfo.uLocalPort+VOD_BASE_MDU_OFFSET);
			strncpy(srvAddrinfo.strLocalMduID, mduInfo.szLocalMduId, VOD_MAX_ID_LEN);
			strncpy(srvAddrinfo.strRemoteMduID, mduInfo.szRemoteMduId, VOD_MAX_ID_LEN);
			memset(srvAddrinfo.strDevDomainID, 0, sizeof(srvAddrinfo.strDevDomainID));
			strncpy(srvAddrinfo.strDevDomainID, m_vod_info.szDomainID, VOD_MAX_ID_LEN);
			if(m_pGuInfo->DomainType != 0)
			{
				//����ҪԶ�̵�CSGIP��˿ڣ��ڲ�ѯ·��ʱ����Ҫ�õ���
				srvAddrinfo.lRemoteCsgAddr.S_un.S_addr = inet_addr(mduInfo.szRemoteCsgIp);
				srvAddrinfo.usRemoteCsgPort = htons(mduInfo.uRemoteCsgPort+PORT_CSG_INCREASE_NUM);
				srvAddrinfo.lRemoteMduAddr.S_un.S_addr = inet_addr(mduInfo.szRemoteMduIp);
				srvAddrinfo.usRemoteMduPort = htons(mduInfo.uRemoteMduPort+VOD_BASE_MDU_OFFSET);
			}
			//////////////////////////////////////////////////////////////////////////
			HANDLE hSession = st_vod_createSession(srvAddrinfo);
			if(hSession == NULL)
			{
				return;
			}
			
			vector<CFileInfo> vectList;
#ifdef _DEBUG
			vectList.reserve(100000);
#endif // _DEBUG
			m_iSearchType = GetSearchTypePic();
			
			int nSearchType = m_iSearchType;//GetSearchType();
			BOOL bOK = st_vod_getFileList(hSession, (const char *)m_szGuid.GetBuffer(m_szGuid.GetLength()), nSearchType, m_vod_info.szVodID, &stStart, &stEnd, vectList);
			//BOOL bOK = st_vod_getFileList(hSession, m_szGuid, nSearchType, &stStart, &stEnd, vectList);
			if(!bOK)
			{
				int nRet = WSAGetLastError();;
				AfxMessageBox(_T("��ѯ�������ѯ�б�ʧ�ܣ����糬ʱ����������ԣ�"));
				return;
			}
			else
			{
				m_ctrlListRecord.SetRedraw(FALSE);
				std::sort(vectList.begin(), vectList.end(), MyComp());
				ULONG64 nSize = vectList.size();
				for(int i=0; i< nSize; i++)
				{        
					CString strFile = vectList[i].file;
					CString strSize;
					strSize.Format(_T("%u KB"), vectList[i].size/1024);
					
					char szIndex[32];
					int nCount = m_ctrlListRecord.GetItemCount();
					sprintf(szIndex, "%05d", nCount);
					
					m_ctrlListRecord.InsertItem(nCount, /*(const unsigned short *)*/szIndex, 0);
					m_ctrlListRecord.SetItemState(nCount, INDEXTOSTATEIMAGEMASK(1),  LVIS_STATEIMAGEMASK);
					
					m_ctrlListRecord.SetColumnWidth(1, 0);
					m_ctrlListRecord.SetColumnWidth(2, 0);
					m_ctrlListRecord.SetColumnWidth(3, 0);	
					m_ctrlListRecord.SetColumnWidth(4, 200);
					m_ctrlListRecord.SetColumnWidth(5, 80);
					m_ctrlListRecord.SetColumnWidth(6, 100);
					m_ctrlListRecord.SetColumnWidth(7, 200);
					m_ctrlListRecord.SetColumnWidth(8, 0);
					
					CString strModify;
					ResetFileName(1, strFile, strModify);
					m_ctrlListRecord.SetItemText(nCount, 8, strFile);		  // �ļ�ȫ·��
					m_ctrlListRecord.SetItemText(nCount, 4, strModify);     // �ļ���
					m_ctrlListRecord.SetItemText(nCount, 5, strSize);       // �ļ���С
					m_ctrlListRecord.SetItemText(nCount, 6, _T("VOD"));         // ��ѯλ��
					int iType1 = (vectList[i].type & 0x00000010)>>4;
					int iType2 = (vectList[i].type & 0x00000020)>>5;
					int iType3 = (vectList[i].type & 0x00000040)>>6;
					CString strFileType, strTmpType;
					strFileType.Empty();
					if (iType1 == 1)
					{
						strFileType.Format(_T(" %s"), _T("�ֶ�"));;
					}
					if (iType2 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), _T("��ʱ"));
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							strFileType.Format(_T("%s/%s"), strTmpType, _T("��ʱ"));
						}
					}
					if (iType3 == 1)
					{
						if (strFileType.IsEmpty())
						{
							strFileType.Format(_T(" %s"), _T("����"));
						}
						else
						{
							strTmpType.Format(_T("%s"), strFileType);
							strFileType.Format(_T("%s/%s"), strTmpType, _T("����"));
						}
					}
					m_ctrlListRecord.SetItemText(nCount, 7, strFileType);            // ����
				}
				m_ctrlListRecord.SetRedraw();
				
			}
			st_vod_destroySession(hSession);
			
			SetBaseInfo(FILETYPE_PIC_VOD, m_pGuInfo, &m_vod_info);

		}
		break;
	default:
		break;
	}
	
}




///===��ʼ���б�ؼ�===================================================///
//
void CDlgPlayList::InitListCtrlHeaders()
{
	m_ctrlListRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT);
 	int nIndex = 0;
	m_ctrlListRecord.UpdateData();

	m_ctrlListRecord.InsertColumn(nIndex, _T("���"), LVCFMT_LEFT, 50);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("����ͷID������"), LVCFMT_LEFT, 100);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("��ʼʱ��"), LVCFMT_LEFT, 70);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("����ʱ��"), LVCFMT_LEFT, 70);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("�ļ���"), LVCFMT_LEFT, 100);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("�ļ���С"), LVCFMT_LEFT, 70);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("��ѯλ��"), LVCFMT_LEFT, 70);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("¼������"), LVCFMT_LEFT, 70);

	nIndex++;
	m_ctrlListRecord.InsertColumn(nIndex, _T("ʵ���ļ�·��"), LVCFMT_LEFT, 100);

	m_ctrlListRecord;

	m_ctrlListRecord.UpdateData(FALSE);
}




///=== ¼������б� ==================================================///
//
void CDlgPlayList::OnSelchangeComboRecordServer() 
{
	// TODO: Add your control notification handler code here
	int index = m_ctrlRecordServer.GetCurSel();
	if ( index == -1 )
	{
		return ;
	}
	m_vod_info = m_vodServerInfo[index];	
}




///=== ¼����Դ�ı��¼� ===============================================///
//
void CDlgPlayList::OnSelchangeComboRecordSrc() 
{
	// TODO: Add your control notification handler code here
	if (m_ctrlRecordSrc.GetCurSel() == 0 || m_ctrlRecordSrc.GetCurSel() == 1)
	{
		int nCount = m_ctrlRecordServer.GetCount();
		if ( nCount > 0 )
		{
			for ( int i = nCount - 1; i >= 0; i-- )
			{
				m_ctrlRecordServer.DeleteString(i);
			}
		}
		m_ctrlRecordServer.EnableWindow(FALSE);
	}
	else
	{
		// ��ȡ��ѯ�����ʶ	
		HRESULT hr = CU_NET_LIB::VodServerQuery(g_dwServerId, /*(const unsigned short *)*/m_pGuInfo->DomainID, /*(const unsigned short *)*/m_pGuInfo->GUID, &m_iVodServerNum, m_vodServerInfo);
		if(hr != ST_OK)
		{
			return;
		}
		
		if (m_iVodServerNum == 0 || (m_iVodServerNum > 16 || m_iVodServerNum < 0))
		{
			return;
		}
		else
		{
			while( CB_ERR != m_ctrlRecordServer.DeleteString( 0 ) );
			for (int i = 0; i < m_iVodServerNum; i++)
			{
				m_ctrlRecordServer.InsertString(i, /*(const unsigned short *)*/m_vodServerInfo[i].szVodName);
			}
			m_ctrlRecordServer.SetCurSel(0);
			m_strVodIp.Format(_T("%s"), m_vodServerInfo[0].szVodIp);
			m_nVodPort = m_vodServerInfo[0].nVodPort;

			CMainPage* pDlg = m_pMainPage;
			pDlg->m_strVodIp = m_strVodIp;
			pDlg->m_nVodPort = m_nVodPort;
		}
		
		m_ctrlRecordServer.EnableWindow(TRUE);
	}
	
}



///=== ���õ�ǰҵ����Ϣ =====================================///
// [in]pGuInfo: ҵ����Ϣ
void CDlgPlayList::SetGuInfo(CU_NET_LIB::GUINFO *pGuInfo)
{
	m_pGuInfo = pGuInfo;
	

	m_szPuid = pGuInfo->PUID;
	m_szGuid = pGuInfo->GUID;
	m_szGuName = pGuInfo->GUName;
	UpdateData(FALSE);
}




///===��ȡ¼������===========================================================///
//
int CDlgPlayList::GetSearchType()
{
	int iType = 0;
	int iRecordType = m_ctrlRecordType.GetCurSel();
	switch(iRecordType)
	{
	case 0:
		iType = 1|(1<<1)|(1<<2);
		break;
	case 1:
		iType = (1<<1);
		break;
	case 2:
		iType = (1<<2);
		break;
	case 3:
		iType = 1;
		break;
	default:
		iType = 1|(1<<1)|(1<<2);
		break;
	}
	
	return iType;
}




///===��ȡͼƬ����========================================================///
// 
int CDlgPlayList::GetSearchTypePic()
{
	int iType = 0;
	int iRecordType = m_ctrlRecordType.GetCurSel();
	switch(iRecordType)
	{
	case 0:
		iType = (1<<4)|(1<<5)|(1<<6);
		break;
	case 1:
		iType = (1<<5);
		break;
	case 2:
		iType = (1<<6);
		break;
	case 3:
		iType = 1<<4;
		break;
	default:
		iType = (1<<4)|(1<<5)|(1<<6);
		break;
	}
	
	return iType;
}





///==================================================================////
//
void CDlgPlayList::OnRclickListFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ShowRBMenu();
	
	*pResult = 0;
}



///=== �Ҽ��˵� ==================================================///
//
void CDlgPlayList::ShowRBMenu()
{
	if ( m_ctrlListRecord.GetItemCount() < 1 )
	{
		return;
	}

	CMenu menu;

	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, IDM_PLAY, _T("��"));
	menu.AppendMenu(MF_STRING, IDM_DOWNLOAD, _T("����"));

	if( m_nType == FILETYPE_PIC_LOCAL || m_nType == FILETYPE_REC_LOCAL )
	{
		menu.EnableMenuItem(IDM_DOWNLOAD, MF_GRAYED);
	}

	CPoint point(GetMessagePos());
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

	menu.DestroyMenu();
}




///=== ����㲥/��ͼƬ ================================================///
//
void CDlgPlayList::OnMenuPlay()
{
	CWaitCursor wait;
    CString strLoadText;
	TCHAR szFileName[1024] = {0};

	int nIndex = m_ctrlListRecord.GetSelectionMark();
	if ( nIndex < 0 )
	{
		return;
	}

	m_ctrlListRecord.GetItemText(nIndex, 8, szFileName, sizeof(szFileName)-1);
	TCHAR szName[1024] = {0};
	m_ctrlListRecord.GetItemText(nIndex, 4, szName, sizeof(szName)-1);
	
	if (m_nType == FILETYPE_REC_VOD)
	{
		if(0 == (m_guInfo.right & RIGHT_PLAYBACK))	//if(FALSE == guInfo.EnBackPlay)
		{
			AfxMessageBox(_T("����ȨԶ�̻ط�Ȩ�ޣ��������Ա��ϵ��"));
			return;
		}
		CNetVodDlg dlg(this);
		dlg.SetBaseInfo(TRUE, &m_guInfo, &m_vod_info, szFileName);
		dlg.DoModal();
	}
	else if (m_nType == FILETYPE_REC_PU)
	{
		if(0 == (m_guInfo.right & RIGHT_PLAYBACK))	//if(FALSE == guInfo.EnBackPlay)
		{
			AfxMessageBox(_T("����ȨԶ�̻ط�Ȩ�ޣ��������Ա��ϵ��"));
			return;
		}
		CNetVodDlg dlg(this);
		dlg.SetBaseInfo(FALSE, &m_guInfo, &m_vod_info, szFileName);
		dlg.DoModal();
	}
	else if (m_nType == FILETYPE_REC_LOCAL)
	{
		int nIndex = m_ctrlListRecord.GetSelectionMark();
		if(nIndex <0)
			return;
		TCHAR szFileName[1024] = {0};
		m_ctrlListRecord.GetItemText(nIndex, 8, szFileName, sizeof(szFileName)-1);
		
		CString strPlayExe;
		char strPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, /*(unsigned short *)*/strPath);
		char exePath[MAX_PATH];

		sprintf(exePath,"%s\\%s",strPath,"topFilePlay.exe");
		//strPlayExe = theApp.m_szAppPath + "topFilePlay.exe";
		//strPlayExe += ".\\";
		strPlayExe += "D:\\project\\CuSDK\\CuSDK\\topFilePlay.exe"; 
		
		STARTUPINFO stinfo; //�������ڵ���Ϣ
		PROCESS_INFORMATION procinfo; //���̵���Ϣ
		memset(&stinfo, 0, sizeof(STARTUPINFO));
		stinfo.cb = sizeof(STARTUPINFO);
		stinfo.dwFlags = STARTF_USESHOWWINDOW;
		stinfo.wShowWindow = SW_SHOWDEFAULT;
		BOOL result = CreateProcess(strPlayExe,szFileName,NULL,NULL,
			FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL, &stinfo,&procinfo);
		if ( result == FALSE )
		{
			AfxMessageBox(_T("Error!"));
			return;
		}
	}
	else if(m_nType == FILETYPE_PIC_PU || m_nType == FILETYPE_PIC_VOD || m_nType == FILETYPE_PIC_LOCAL)
	{
		CDlgPicView dlg;
		dlg.SetFilePath(szFileName);
		dlg.DoModal();
	}
}



void CDlgPlayList::OnMenuDownLoad()
{
	CWaitCursor wait;
    CString  strLoadText;
	int nIndex = m_ctrlListRecord.GetSelectionMark();
	if(nIndex <0)
		return;
	
	TCHAR szFileName[1024] = {0};
	m_ctrlListRecord.GetItemText(nIndex, 8, szFileName, sizeof(szFileName)-1);
	CString strFileSize = m_ctrlListRecord.GetItemText(nIndex, 5);  
	ULONGLONG lFileSize = atoi((const char *)(LPCTSTR)strFileSize);
	
	CString strModify;
	char szFilter[256] = {0};

	ResetFileName(m_nType, szFileName, strModify);
	
	
	CFileDialog  dlg(FALSE, 0, strModify, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, 
		_T("Media Files (*.avi)|*.avi|(*.dat)|*.dat|(*.jpg)|*.jpg|(*.bmp)|*.bmp|All Files (*.*)|*.*||"), this);
	if(IDOK != dlg.DoModal())
		return;
	CString strFileSave = dlg.GetPathName();
	
	if(m_nType == FILETYPE_REC_PU || m_nType == FILETYPE_PIC_PU || m_nType == FILETYPE_REC_VOD || m_nType == FILETYPE_PIC_VOD)   // VOD ǰ��
	{
		try
		{
			CFileDownloadDlg* pDlg = new CFileDownloadDlg;
			if(pDlg == NULL)
				throw(0);
			
			pDlg->m_lSize = lFileSize;
			if (m_nType == FILETYPE_REC_PU || m_nType == FILETYPE_PIC_PU)
			{
				HRESULT hr;
				CU_NET_LIB::MDU_ROUTE_INFO mduInfo;
				memset(&mduInfo, 0, sizeof(CU_NET_LIB::MDU_ROUTE_INFO));
				hr = CU_NET_LIB::QueryPuRealRoute(g_dwServerId, m_guInfo, mduInfo);
				
				if( ST_OK != hr)
				{
					AfxMessageBox(_T("��ѯPU·��ʧ�ܣ�"));
					return;
				}
				//////////////////////////////////////////////////////////////////////////
				pDlg->m_strPuid.Format(_T("%s"), m_guInfo.PUID);
				pDlg->m_mduInfo = mduInfo;
				pDlg->m_guInfo = m_guInfo;
				pDlg->m_nFrontOrCen = m_nType;
				pDlg->m_strMsuDomainID.Format(_T("%s"), m_vod_info.szDomainID);
			}
			else
			{
				HRESULT hr;
				UINT uPort = 0;
				char szMduIp[32] = {0};
				CU_NET_LIB::MDU_ROUTE_INFO mduInfo;
				memset(&mduInfo, 0, sizeof(CU_NET_LIB::MDU_ROUTE_INFO));
				hr = CU_NET_LIB::QueryPuRealRoute(g_dwServerId, m_guInfo, mduInfo);
				
				if( ST_OK != hr)
				{
					AfxMessageBox(_T("��ѯPU·��ʧ�ܣ�"));
					return;
				}
				pDlg->m_mduInfo = mduInfo;
				pDlg->m_guInfo = m_guInfo;
				pDlg->m_strPuid.Format(_T("%s"), m_guInfo.PUID);
				pDlg->m_strMsuID.Format(_T("%s"), m_vod_info.szVodID);
				pDlg->m_strMsuDomainID.Format(_T("%s"), m_vod_info.szDomainID);
			}
			pDlg->m_strFile.Format(_T("%s"), szFileName);
			pDlg->m_strFileSave = strFileSave;
			pDlg->m_nFrontOrCen = m_nType;
			pDlg->Create(CFileDownloadDlg::IDD, this);
			pDlg->ShowWindow(SW_SHOW);
		}
		catch(...)
		{
			AfxMessageBox(_T("�����ڴ��쳣��������������Ӧ�ó���"));
			return;
		}
	}
}





void CDlgPlayList::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	ShowWindow(SW_HIDE);
	
	//CDialog::OnClose();
}

void CDlgPlayList::SetMainPage(CMainPage *pMainPage)
{
	m_pMainPage = pMainPage;
}

CMainPage* CDlgPlayList::GetMainPage()
{
	return m_pMainPage;
}
