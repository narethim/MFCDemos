#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"
#include "SocketDemoServerDoc.h"

#include "ServerSocket.h"


// Default ctor
CServerSocket::CServerSocket() :
	m_nPort(6666), m_bConnection(false)
{
	m_strSockName  = _T("Device");
	m_strIPAddress = _T("127.0.0.1");
}

// ctor with 1 argument
CServerSocket::CServerSocket(TCHAR* strName) :
	m_nPort(6666), m_bConnection(false)
{
	m_strSockName = strName;
	m_strIPAddress = _T("127.0.0.1");
}

// ctor with 3 arguments
CServerSocket::CServerSocket(TCHAR* strName, TCHAR* strIP, UINT nPort) :
	m_nPort(nPort), m_bConnection(false)
{
	m_strSockName = strName;
	m_strIPAddress = strIP;
}


// Copy ctor
CServerSocket::CServerSocket(const CServerSocket& obj) :
	m_nPort(obj.m_nPort), m_bConnection(obj.m_bConnection) 
{
	static int nCount = 0;

	m_strSockName = obj.m_strSockName;
	m_strIPAddress= obj.m_strIPAddress;
	m_ReceivingSocket = obj.m_ReceivingSocket;
	TRACE(_T("CServerSocket::CServerSocket() Copy ctor nCount=%d\n"), nCount++);
}

// dtor
CServerSocket::~CServerSocket()
{
}

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CServerSocket::OnAccept()- nErrorCode=%d\n"), nErrorCode);

	bool bRet = Accept(m_ReceivingSocket);
	if (bRet) {
		TRACE(_T("\t Connection accepted %s:%d\n"), GetIPAddress(), GetPort());
		//
		// The following is to update 'pDoc->m_bSocketConnect' and tell other views to update the UI with this info 
		// 
		CSocketDemoServerDoc* pDoc = nullptr;
		CSocketDemoServerApp* pApp = (CSocketDemoServerApp*)AfxGetApp();

		pDoc = pApp->m_pServerView->GetDocument();

		//int i = 0;
		//for (CServerSocket server : pDoc->m_vectServerSocket) {
		//	if (server.GetPort() == GetPort()) {
		//		pDoc->m_vectServerSocket[i].SetConnection(true);	// Indicated that this socket is connected
		//	}
		//	i++;
		//}

		std::vector<CServerSocket>::iterator pos;
		for (pos = pDoc->m_vectServerSocket.begin(); pos != pDoc->m_vectServerSocket.end(); ++pos)
		{
			//TRACE(_T("\t pos->GetName()=%s == GetName()=%s\n"), pos->GetName(), GetName());
			if (pos->GetName() == GetName()) {
				pos->SetConnection(true);	// Indicated that this socket is connected
			}
		}


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
			strOutput.Format(_T("%s, %s, Socket (%s:%d) connected"), 
				startTime.Format("%D %H:%M:%S").GetBuffer(), GetName().GetBuffer(), strIP.GetBuffer(), nPort);

			pWndOutput->OutputBuildWindow(strOutput);   // Build message window
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
