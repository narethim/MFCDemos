
// SocketDemoServerDoc.h : interface of the CSocketDemoServerDoc class
//


#pragma once

constexpr  int IDB_F_CLOSE_Y = 0;
constexpr  int IDB_F_OPEN_Y = 1;
constexpr  int IDB_BALL_R = 2;
constexpr  int IDB_BALL_G = 3;
constexpr  int IDB_BALL_B = 4;
constexpr  int IDB_BOX_W = 5;
constexpr  int IDB_BOX_Y = 6;
constexpr  int IDB_BOX_R = 7;
constexpr  int IDB_BOX_G = 8;
constexpr  int IDB_BOX_B = 9;
constexpr  int IDB_REMOTE_C = 10;
constexpr  int IDB_REMOTE_D = 11;


class CSocketDemoServerDoc : public CDocument
{
protected: // create from serialization only
	CSocketDemoServerDoc() noexcept;
	DECLARE_DYNCREATE(CSocketDemoServerDoc)

// Attributes
public:
	bool m_bSocketConnect = false;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSocketDemoServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
