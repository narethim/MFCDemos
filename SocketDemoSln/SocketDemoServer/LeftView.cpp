
// LeftView.cpp : implementation of the CLeftView class
//

#include "pch.h"
#include "framework.h"
#include "SocketDemoServer.h"

#include "SocketDemoServerDoc.h"
#include "LeftView.h"

#include "MainFrm.h"
#include "SocketDemoServerView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CLeftView construction/destruction

CLeftView::CLeftView()
{
	int nSize = sizeof(m_hTreeLevel1) / sizeof(HTREEITEM);
	for (int i = 0; i < nSize; i++) {
		m_hTreeLevel1[i] = 0;
	}
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

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
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	treeCtrl.SetImageList(&m_ImagesList, TVSIL_NORMAL);

	PopulateTree();
}


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CSocketDemoServerDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSocketDemoServerDoc)));
	return (CSocketDemoServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView message handlers


void CLeftView::PopulateTree()
{
//	HTREEITEM hTreeLevel1[100]; //, hTreeLevel2[10]; //, hTreeLevel3;
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	treeCtrl.DeleteAllItems();

	InsertInitialTree(m_hTreeLevel1);

	treeCtrl.Expand(treeCtrl.GetRootItem(), TVE_EXPAND);

	//
	// Excercise the output to Debug output dockable windows
	//
	//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//COutputWnd * pWndOutput = pFrame->GetOutputWnd();
	//// Test  - Debug tab
	//if (pWndOutput != nullptr) {
	//	CString str("CLeftView::PopulateTree(): OutputDebugWindow() - Debug");
	//	pWndOutput->OutputDebugWindow(str);   // Debug message window
	//}

	CTreeView::UpdateWindow();
}


void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	// ----
	TRACE( _T("CLeftView::OnTvnSelchanged()\n") );

	// get tree
	CTreeCtrl& treectrl = GetTreeCtrl();

	// get list
	// ------------------------------------------------------------------------------
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	//	CTestAdminView * pView = (CTestAdminView*)pFWnd->m_wndSplitter.GetPane(0, 1);
	CSocketDemoServerView * pView = (CSocketDemoServerView*)pFWnd->GetRightPane();
	ASSERT(pView != NULL);
	CListCtrl& listctrl = pView->GetListCtrl();

	// what item got selected?
	TV_ITEM strTvItem;
	char szText[64]; // 64 should be enuf
	strTvItem.mask = TVIF_CHILDREN | TVIF_TEXT | TVIF_IMAGE;
	strTvItem.hItem = pNMTreeView->itemNew.hItem;
	strTvItem.pszText = (LPTSTR)szText;
	strTvItem.cchTextMax = 64;
	treectrl.GetItem(&strTvItem);

	//prep a structure for the list
	LV_ITEM lvitem;
	// text and image
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	// must be zero for the 0th column
	lvitem.iSubItem = 0;
	// fill in pszText, iItem and iImage later 

	// Children? cChildren is a code - not a count
	if (strTvItem.cChildren == 1)
	{
		// I am going to re-fill the list, so reset it now
		listctrl.DeleteAllItems();

		// yes, we have children - populate list with them
		strTvItem.mask = TVIF_TEXT | TVIF_IMAGE;

		HTREEITEM hChild;
		hChild = treectrl.GetNextItem(pNMTreeView->itemNew.hItem, TVGN_CHILD);

		int i = 0;
		while (hChild != NULL)
		{
			// Non-leaf node

			strTvItem.hItem = hChild;

			treectrl.GetItem(&strTvItem);

			// make list entry

			// form the list control structure
			// -----------------------------------------------------------
			lvitem.pszText = strTvItem.pszText;         // text 
			lvitem.iItem = i;	                        // point to the row number
			lvitem.iImage = strTvItem.iImage;           // image - same list at the tree's
			int nRet = listctrl.InsertItem(&lvitem);  // do the insert

			//int nRet = listctrl.InsertItem(i, lvitem.pszText, lvitem.iImage);  // do the insert

			// a check
			if (nRet != -1)
			{
				// fill other columns with stuff

				// do col 1
				BOOL bRet = listctrl.SetItemText(i, 1, _T("Drive Stuff"));
				ASSERT(bRet);

				// do col 2
				bRet = listctrl.SetItemText(i, 2, _T("My Stuff"));
				ASSERT(bRet);

				// do col 3
				bRet = listctrl.SetItemText(i, 3, _T("More Stuff"));
				ASSERT(bRet);

				hChild = treectrl.GetNextItem(hChild, TVGN_NEXT);
			}
			i++;
		}
	}
	else if (strTvItem.cChildren == 0)
	{
		// leaf node

		/*  DO NOTHING */
	}
	//---

	*pResult = 0;
}


int CLeftView::InsertInitialTree(HTREEITEM hTreeLevel1[3])
{
	HTREEITEM hTreeRoot;
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	hTreeRoot = treeCtrl.InsertItem(_T("root"), 0, 1);

	m_hTreeLevel1[0] = treeCtrl.InsertItem(_T("Device 1"), 0, 1, hTreeRoot);
	m_hTreeLevel1[1] = treeCtrl.InsertItem(_T("Device 2"), 0, 1, hTreeRoot);
	m_hTreeLevel1[2] = treeCtrl.InsertItem(_T("Device 3"), 0, 1, hTreeRoot);

	return 0;
}


void CLeftView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CLeftView::OnUpdate()\n"));
	GetDocument()->m_bSocketConnect;

	TRACE(_T("CLeftView::OnUpdate() - GetDocument()->m_bSocketConnect=%s\n"), 
		GetDocument()->m_bSocketConnect ? _T("Connected") : _T("Disonnected"));

	// Update Socket connection status icon.
	if (m_hTreeLevel1[0]) {
		if (GetDocument()->m_bSocketConnect) {
			GetTreeCtrl().SetItemImage(m_hTreeLevel1[0], (int)IDB_BALL_G, (int)IDB_BALL_G);

			//CString str = GetTreeCtrl().GetItemText(m_hTreeLevel1[0]);
			//str += _T(" connected");
			//GetTreeCtrl().SetItemText(m_hTreeLevel1[0], str);
		}
		else {
			GetTreeCtrl().SetItemImage(m_hTreeLevel1[0], (int)IDB_BALL_R, (int)IDB_BALL_R);

			//CString str = GetTreeCtrl().GetItemText(m_hTreeLevel1[0]);
			//str += _T(" disconnected");
			//GetTreeCtrl().SetItemText(m_hTreeLevel1[0], str);
		}
	}


}
