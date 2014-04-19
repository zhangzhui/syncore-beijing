// PicScrollView.cpp : implementation file
//

#include "stdafx.h"
#include "CuOcx.h"
#include "PicScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicScrollView

IMPLEMENT_DYNCREATE(CPicScrollView, CScrollView)

CPicScrollView::CPicScrollView()
{
	m_pPic = NULL;
	SetScrollSizes(MM_TEXT, CSize(100, 100));
}

CPicScrollView::~CPicScrollView()
{
	ReleasePic();
}


BEGIN_MESSAGE_MAP(CPicScrollView, CScrollView)
	//{{AFX_MSG_MAP(CPicScrollView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicScrollView drawing

void CPicScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}



///===重写=================================================///
// add by xuyz 2011-09-17
void CPicScrollView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	if (m_pPic != NULL)
	{	
		CRect rcClient;
		GetClientRect(rcClient);
		
		long xMax = max(rcClient.Width(), m_cxPic);
		long yMax = max(rcClient.Height(), m_cyPic);
		
		long PicLeft = (xMax-m_cxPic) / 2;
		long PicTop = (yMax-m_cyPic) / 2;
		m_pPic->Render(*pDC, PicLeft, PicTop, m_cxPic, m_cyPic,
			0, m_hmHeight, m_hmWidth, -m_hmHeight, NULL);
		
		if (xMax > m_cxPic || yMax > m_cyPic)
		{
			pDC->ExcludeClipRect(CRect(PicLeft, PicTop, PicLeft+m_cxPic, PicTop+m_cyPic));
			
			pDC->FillSolidRect(0, 0, xMax, yMax, RGB(255,255,255));
		}
	}


}

///===释放接口===========================================///
// add by xuyz 2011-09-16
void CPicScrollView::ReleasePic()
{
	if (m_pPic != NULL)
	{
		m_pPic->Release();
		m_pPic = NULL;
	}
}



///===加载图片================================================///
// 参数: 文件实例
// add by xuyz 2011-09-17
void CPicScrollView::LoadPic(CFile& file)
{	
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	
	CArchiveStream arcstream(&ar);
	
	ReleasePic();
	
	if (FAILED(OleLoadPicture(&arcstream, 0, FALSE, IID_IPicture, (void**)&m_pPic)))
	{
		return;
	}
	
	m_pPic->get_Width(&m_hmWidth);     
	m_pPic->get_Height(&m_hmHeight); 
    
	CClientDC dc(this);
	
	CSize sz(m_hmWidth,m_hmHeight);
	dc.HIMETRICtoDP(&sz);
	m_cxPic = sz.cx;
	m_cyPic = sz.cy;
	
	SetScrollSizes(MM_TEXT, sz);
	
	Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CPicScrollView diagnostics

#ifdef _DEBUG
void CPicScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPicScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPicScrollView message handlers

///===重写=======================================================================///
// 添加: 徐育征 2011-9-17
int CPicScrollView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd,nHitTest,message);
}

///===重写=======================================================================///
// 添加: 徐育征 2011-09-17
BOOL CPicScrollView::OnEraseBkgnd(CDC* pDC)
{
	if( m_pPic == NULL)
	{
		return TRUE;
	}
	
	return CPicScrollView::OnEraseBkgnd(pDC);
}
