
// SocketDemoServerView.h : interface of the CSocketDemoServerView class
//

#pragma once


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

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SocketDemoServerView.cpp
inline CSocketDemoServerDoc* CSocketDemoServerView::GetDocument() const
   { return reinterpret_cast<CSocketDemoServerDoc*>(m_pDocument); }
#endif

