#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"
#include "SocketDemoServerDoc.h"

#include "ServerSocket.h"

CServerSocket::CServerSocket(TCHAR* strName) :
	m_nPort(6666), m_bConnection(false)
{
	wcscpy_s(m_strSockName, strName);
	wcscpy_s(m_strIPAddress, _T("127.0.0.1"));
}

CServerSocket::CServerSocket(TCHAR* strName, TCHAR* strIP, UINT nPort) :
	m_nPort(nPort), m_bConnection(false)
{
	wcscpy_s(m_strSockName, strName);
	wcscpy_s(m_strIPAddress, strIP);
}



CServerSocket::CServerSocket() :
	m_nPort(6666), m_bConnection(false)
{
	wcscpy_s(m_strSockName, _T("Device") );
	wcscpy_s(m_strIPAddress, _T("127.0.0.1") );
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CServerSocket::OnAccept()- nErrorCode=%d\n"), nErrorCode);

	bool bRet = Accept(m_ReceivingSocket);
	if (bRet) {
		TRACE(_T("\t Connection accepted\n"));
		//
		// The following is to update 'pDoc->m_bSocketConnect' and tell other views to update the UI with this info 
		// 
		CSocketDemoServerDoc* pDoc = nullptr;
		CSocketDemoServerApp* pApp = (CSocketDemoServerApp*)AfxGetApp();

		pDoc = pApp->m_pServerView->GetDocument();
		pDoc->m_serverSocket[0].SetConnection(true);					// Indicated that this socket is connected
		pDoc->UpdateAllViews(pApp->m_pServerView);		// tell other views to update the UI

		// Log to Debug output window  Test - Debug tab
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		COutputWnd * pWndOutput = pFrame->GetOutputWnd();
		if (pWndOutput != nullptr) {
			CString strIP;
			UINT nPort;
			CString strOutput;
			CTime startTime = CTime::GetCurrentTime();		// NIM

			this->GetSockName(strIP, nPort);
			strOutput.Format(_T("%s, Socket (%s:%d) connected"), startTime.Format("%D %H:%M:%S"), strIP, nPort);

			pWndOutput->OutputDebugWindow(strOutput);   // Build message window
		}
	}

	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CServerSocket::OnReceive()- nErrorCode=%d - Data Received\n"), nErrorCode);

	CSocket::OnReceive(nErrorCode);
}
