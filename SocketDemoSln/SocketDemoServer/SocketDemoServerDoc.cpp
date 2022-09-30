
// SocketDemoServerDoc.cpp : implementation of the CSocketDemoServerDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SocketDemoServer.h"
#endif

#include "SocketDemoServerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSocketDemoServerDoc

IMPLEMENT_DYNCREATE(CSocketDemoServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CSocketDemoServerDoc, CDocument)
END_MESSAGE_MAP()


// CSocketDemoServerDoc construction/destruction

CSocketDemoServerDoc::CSocketDemoServerDoc() noexcept
{
	// TODO: add one-time construction code here

}

CSocketDemoServerDoc::~CSocketDemoServerDoc()
{
	//for (int i = 0; i < 4; i++) {
	for (int i = 0; i < sizeof(m_serverSocketArr) / sizeof(&m_serverSocketArr[0]); i++) {
			delete m_serverSocketArr[i];
	}

}

BOOL CSocketDemoServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	TRACE(_T("CSocketDemoServerDoc::OnNewDocument() \n"));
	m_vectServerSocket.reserve(10);

//	for (int i = 0; i < 4; i++) {
	for (int i = 0; i < sizeof(m_serverSocketArr) / sizeof(&m_serverSocketArr[0]); i++) {
		m_serverSocketArr[i] = new CServerSocket(m_serverNameArr[i], _T("127.0.0.1"), m_serverPortArr[i]);
		m_serverSocketArr[i]->GetSocketPtr()->SetName(m_serverNameArr[i]);
		m_serverSocketArr[i]->GetSocketPtr()->SetID(m_serverIDArr[i]);

		m_vectServerSocket.push_back( *m_serverSocketArr[i] );
	}

//	for (int i = 0; i < 4; i++) {
	for (int i = 0; i < sizeof(m_serverSocketArr) / sizeof(&m_serverSocketArr[0]); i++) {

		// m_vectServerSocket[i];
		UINT nPort = m_vectServerSocket[i].GetPort();
		LPCTSTR lpszSocketAddress = m_vectServerSocket[i].GetIPAddress();

		//
		// Create and listen m_serverSocket[0]
		//
		BOOL bRet = m_vectServerSocket[i].Create(nPort, 1, lpszSocketAddress);
		if (bRet) {
			TRACE(_T(" m_vectServerSocket[%d].Create(nSocketPort=%d, nSocketType=1, lpszSocketAddress=%s) SUCCESS\n"), i,
				nPort, lpszSocketAddress);

			bRet = m_vectServerSocket[i].Listen();
			if (bRet) {
				TRACE(_T(" m_vectServerSocket[%d].Listen() SUCCESS\n"), i);
			}
			else {
				TRACE(_T("ERROR:  m_vectServerSocket[%d].Listen() FAILED\n"), i);
			}
		}
		else {
			TRACE(_T("ERROR: m_vectServerSocket[%d].Create(nSocketPort=%d, nSocketType=1, lpszSocketAddress=%s) FAILED\n"), i,
				nPort, lpszSocketAddress);
		}
	}


	return TRUE;
}




// CSocketDemoServerDoc serialization

void CSocketDemoServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSocketDemoServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSocketDemoServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSocketDemoServerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSocketDemoServerDoc diagnostics

#ifdef _DEBUG
void CSocketDemoServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSocketDemoServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSocketDemoServerDoc commands
