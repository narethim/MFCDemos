
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

#include "ServerSocket.h"

#include <vector>


class CSocketDemoServerDoc : public CDocument
{
protected: // create from serialization only
	CSocketDemoServerDoc() noexcept;
	DECLARE_DYNCREATE(CSocketDemoServerDoc)

// Attributes
public:
	std::vector<CServerSocket> m_vectServerSocket;

	CServerSocket* m_serverSocketArr[11];
//	TCHAR * m_serverNameArr[3] = { _T("Server 1"), _T("Server 2"), _T("Server 3") };
	TCHAR * m_serverNameArr[11] = { _T("Vp"), _T("Vss"), _T("Vdd"), _T("Vad"), _T("Vbsc"), _T("Vrfsw1"), _T("Vrfsw2"), _T("Vrfsw3"), _T("RFMUX"), _T("DIO"), _T("PNA") };
	TCHAR * m_serverIDArr[11]   = { _T("Vp"), _T("Vss"), _T("Vdd"), _T("Vad"), _T("Vbsc"), _T("Vrfsw1"), _T("Vrfsw2"), _T("Vrfsw3"), _T("RFMUX"), _T("DIO"), _T("PNA") };
	UINT    m_serverPortArr[11] = { 6661, 6662, 6663, 6664, 6665, 6666, 6667, 6668, 6669, 6670, 6671 };

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
