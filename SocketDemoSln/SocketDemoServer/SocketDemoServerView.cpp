
// SocketDemoServerView.cpp : implementation of the CSocketDemoServerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SocketDemoServer.h"
#endif

#include "MainFrm.h"
#include "SocketDemoServerDoc.h"
#include "SocketDemoServerView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketDemoServerView

IMPLEMENT_DYNCREATE(CSocketDemoServerView, CListView)

BEGIN_MESSAGE_MAP(CSocketDemoServerView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSocketDemoServerView construction/destruction

CSocketDemoServerView::CSocketDemoServerView() noexcept
{
	((CSocketDemoServerApp*)AfxGetApp())->m_pServerView = this;
}

CSocketDemoServerView::~CSocketDemoServerView()
{
}

BOOL CSocketDemoServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_REPORT;

	return CListView::PreCreateWindow(cs);
}

void CSocketDemoServerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing

	UINT bmparray[] = {
		IDB_EX_F_CLOSE_Y, IDB_EX_F_OPEN_Y,
		IDB_EX_BALL_R, IDB_EX_BALL_G, IDB_EX_BALL_B,
		IDB_EX_BOX_W, IDB_EX_BOX_Y, IDB_EX_BOX_R, IDB_EX_BOX_G,IDB_EX_BOX_B,
		IDB_EX_REMOTE_C, IDB_EX_REMOTE_D
	};
	CBitmap bitmap;
	m_ImagesList.Create(16, 16, TRUE, 5, 5);

	for (int i = 0; i < (sizeof(bmparray) / sizeof(UINT)); i++) {
		bitmap.LoadBitmap(bmparray[i]);
		m_ImagesList.Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();
	}
	TRACE(_T("imageCount=%d\n"), m_ImagesList.GetImageCount());

	CWinApp* pApp = AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	// COutputWnd * pWndOutput = pFrame->GetOutputWnd();
	m_pWndOutput = pFrame->GetOutputWnd();

	//  its list control through a call to GetListCtrl().
	TRACE(_T("CSocketDemoServerView::OnInitialUpdate()\n"));

	// get list
	CListCtrl& cThisList = GetListCtrl();

	cThisList.SetImageList(&m_ImagesList, LVSIL_SMALL); // LVSIL_NORMAL will not show icon, LVSIL_SMALL will

	// enable full row select
	DWORD dwStylebits = cThisList.GetExtendedStyle();
	dwStylebits |= LVS_EX_FULLROWSELECT | LVS_SORTDESCENDING | LVS_EX_GRIDLINES;
	cThisList.SetExtendedStyle(dwStylebits);


	// build list columns
	CRect cr;
	GetClientRect(&cr);

	// set up the grid column titles
	CString s;
	LV_COLUMN lvcol;
	lvcol.cx = 100;
	lvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.pszText = _T("Name");
	lvcol.iSubItem = 0;
	cThisList.InsertColumn(0, &lvcol);

	// second col
//	lvcol.fmt = LVCFMT_RIGHT;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.pszText = _T("Size");
	lvcol.cx = 150;
	lvcol.iSubItem = 1;
	cThisList.InsertColumn(1, &lvcol);

	// third col
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.pszText = _T("Type");
	lvcol.cx = 150;
	lvcol.iSubItem = 2;
	cThisList.InsertColumn(2, &lvcol);

	// fourth col
	lvcol.pszText = _T("Modified");
	lvcol.cx = 500;
	lvcol.iSubItem = 3;
	cThisList.InsertColumn(3, &lvcol);

	////
	//// Excercise the output to Build, Debug, and Find output dockable windows
	////

	//// Test - Build tab
	//if (m_pWndOutput != nullptr) {
	//	CString str("Test: OutputBuildWindow - Build");
	//	m_pWndOutput->OutputBuildWindow(str);   // Build message window
	//}

	//// Test  - Debug tab
	//if (m_pWndOutput != nullptr) {
	//	CString str("Test: OutputDebugWindow() - Debug");
	//	m_pWndOutput->OutputDebugWindow(str);   // Debug message window
	//}

	//// Test - Find tab
	//if (m_pWndOutput != nullptr) {
	//	CString str("Test: OutputFindWindow() - Find");
	//	m_pWndOutput->OutputFindWindow(str);   // Find message window
	//}

}

void CSocketDemoServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSocketDemoServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSocketDemoServerView diagnostics

#ifdef _DEBUG
void CSocketDemoServerView::AssertValid() const
{
	CListView::AssertValid();
}

void CSocketDemoServerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSocketDemoServerDoc* CSocketDemoServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSocketDemoServerDoc)));
	return (CSocketDemoServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CSocketDemoServerView message handlers
void CSocketDemoServerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);
}


void CSocketDemoServerView::AddMsg(CString message)
{
	TRACE(_T("CSocketDemoServerView::AddMsg() message=%s\n"), message);

	m_msgArray.Add(message);

	// Test  - Debug tab
	if (m_pWndOutput != nullptr) {
		CTime startTime = CTime::GetCurrentTime();		// NIM
		CString strOutput;

		strOutput.Format(_T("%s, RECV, %s"), startTime.Format("%D %H:%M:%S"), message.GetBuffer() );
		m_pWndOutput->OutputDebugWindow(strOutput);    // Debug message window
	}

	// m_pDocument->UpdateAllViews(this);
}


void CSocketDemoServerView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CSocketDemoServerView::OnUpdate()\n"));
}
