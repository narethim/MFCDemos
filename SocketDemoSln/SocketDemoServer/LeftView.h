
// LeftView.h : interface of the CLeftView class
//


#pragma once

class CSocketDemoServerDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CSocketDemoServerDoc* GetDocument();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void PopulateTree();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	int InsertInitialTree(HTREEITEM hTreeLevel1[3]);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CSocketDemoServerDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CSocketDemoServerDoc*>(m_pDocument); }
#endif

