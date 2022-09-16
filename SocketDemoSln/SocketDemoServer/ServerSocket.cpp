#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"
#include "SocketDemoServerDoc.h"

#include "ServerSocket.h"


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
		pDoc->m_bSocketConnect = true;					// Indicated that this socket is connected
		pDoc->UpdateAllViews(pApp->m_pServerView);		// tell other views to update the UI

		// Log to Debug output window  Test - Debug tab
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		COutputWnd * pWndOutput = pFrame->GetOutputWnd();
		if (pWndOutput != nullptr) {
			CString strIP;
			UINT nPort;
			CString strOutput("Socket");

			this->GetSockName(strIP, nPort);
			strOutput.Format(_T("%s (%s:%d) connected"), strOutput, strIP, nPort);

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
