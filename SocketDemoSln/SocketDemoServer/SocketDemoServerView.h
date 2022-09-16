
// SocketDemoServerView.h : interface of the CSocketDemoServerView class
//

#pragma once
#include "SocketDemoServerDoc.h"
#include "OutputWnd.h"


class CSocketDemoServerView : public CListView
{
protected: // create from serialization only
	CSocketDemoServerView() noexcept;
	DECLARE_DYNCREATE(CSocketDemoServerView)

// Attributes
public:
	CSocketDemoServerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CSocketDemoServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStringArray m_msgArray;

private:
	COutputWnd * m_pWndOutput;
	CImageList m_ImagesList;

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void AddMsg(CString message);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in SocketDemoServerView.cpp
inline CSocketDemoServerDoc* CSocketDemoServerView::GetDocument() const
   { return reinterpret_cast<CSocketDemoServerDoc*>(m_pDocument); }
#endif

