
// SocketDemoServerView.cpp : implementation of the CSocketDemoServerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SocketDemoServer.h"
#endif

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
	// TODO: add construction code here

}

CSocketDemoServerView::~CSocketDemoServerView()
{
}

BOOL CSocketDemoServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CSocketDemoServerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
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
