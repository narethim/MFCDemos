#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"
#include "ReceivingSocket.h"


void CReceivingSocket::OnReceive(int nErrorCode)
{
	TRACE(_T("CReceivingSocket::OnReceive() - Data Received\n"));

	//	char strRec[256] = "";
	TCHAR strRec[256] = L"";

	int nCount = CSocket::Receive(strRec, 256);
	if (nCount > 0) {
		TRACE(L"\t strRec=%s\n", strRec);
		CString strData(strRec);

		// ((CMFCServerApp*)AfxGetApp())->m_pServerView->AddMsg( (CString)strRec );

		((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddMsg(strData);

		//
		// Send reply
		//
		CString strMsgReply(_T("OK"));

		int len = strMsgReply.GetLength();
		TCHAR* pData = strMsgReply.GetBuffer(len);

		nCount = CSocket::Send(pData, len*2);
		if (nCount > 0) {
			TRACE(_T("Send() %d bytes OK\n"), nCount);
		}
		else {
			TRACE(_T("ERROR: Send()\n"));
		}

	}
	CSocket::OnReceive(nErrorCode);
}


void CReceivingSocket::OnClose(int nErrorCode)
{
	TRACE("CReceivingSocket::OnClose() - \n");

	TRACE("\t Call CSocket::Detach() to detach it from ServerSocket\n");
	SOCKET retSocket = CSocket::Detach();

	//---
	//
	// The following is to update 'pDoc->m_bSocketConnect' and tell other views to update the UI with this info
	//  
	CSocketDemoServerDoc* pDoc = nullptr;
	CSocketDemoServerApp* pApp = (CSocketDemoServerApp*)AfxGetApp();
	pDoc = pApp->m_pServerView->GetDocument();
	pDoc->m_bSocketConnect = false;				// Indicated that this socket is disconnected
	pDoc->UpdateAllViews(pApp->m_pServerView);	// tell other views to update the UI

	//---
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	COutputWnd * pWndOutput = pFrame->GetOutputWnd();

	if (pWndOutput != nullptr) {
		CString strOutput("Socket closed - disconnected");
		
		pWndOutput->OutputDebugWindow(strOutput);   // Build message window
	}
	//---

	CSocket::OnClose(nErrorCode);
}
