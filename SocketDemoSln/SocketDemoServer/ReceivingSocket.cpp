#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"
#include "ReceivingSocket.h"

// Default ctor
CReceivingSocket::CReceivingSocket() :
	m_strSockName("Device"), m_bConnection(false)
{

}

// ctor with 1 argument
CReceivingSocket::CReceivingSocket(CString strName) :
	m_strSockName(strName), m_bConnection(false)
{

}

// Copy ctor
CReceivingSocket::CReceivingSocket(const CReceivingSocket& obj) :
	m_bConnection(obj.m_bConnection), m_strSockName(obj.m_strSockName)
{
	// m_strSockName = obj.m_strSockName;
}

// Default dtor
CReceivingSocket::~CReceivingSocket()
{
}


void CReceivingSocket::OnReceive(int nErrorCode)
{
	TRACE(_T("CReceivingSocket::OnReceive() - Data Received\n"));

	//	char strRec[256] = "";
	TCHAR strRec[256] = L"";

	int nCount = CSocket::Receive(strRec, 256);
	if (nCount > 0) {
		TRACE(L"\t strRec=%s\n", strRec);
		CString strData(strRec);

		strData.Format(_T("%s, %s"), GetName().GetBuffer(), strRec);

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
	// TRACE("CReceivingSocket::OnClose() - \n");

	TRACE(_T("\t Call CSocket::Detach() to detach %s from ServerSocket\n"), GetName());
	SOCKET retSocket = CSocket::Detach();

	//---
	//
	// The following is to update 'pDoc->m_bSocketConnect' and tell other views to update the UI with this info
	//  
	CSocketDemoServerDoc* pDoc = nullptr;
	CSocketDemoServerApp* pApp = (CSocketDemoServerApp*)AfxGetApp();
	pDoc = pApp->m_pServerView->GetDocument();

	std::vector<CServerSocket>::iterator pos;
	for (pos = pDoc->m_vectServerSocket.begin(); pos != pDoc->m_vectServerSocket.end(); ++pos)
	{
		// TRACE(_T("\t pos->GetName()=%s == GetName()=%s\n"), pos->GetName(), GetName());
		if (pos->GetName() == GetName()) {
			pos->SetConnection(false);	// Indicated that this socket is disconnected
		}
	}

	pDoc->UpdateAllViews(pApp->m_pServerView);	// tell other views to update the UI

	//---
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	COutputWnd * pWndOutput = pFrame->GetOutputWnd();

	if (pWndOutput != nullptr) {
		CTime startTime = CTime::GetCurrentTime();		// NIM
		CString strOutput;
		CString strDateTime  = startTime.Format("%D %H:%M:%S");

		strOutput.Format(_T("%s, %s, Socket closed - disconnected"), strDateTime.GetBuffer(), GetName().GetBuffer());
		
		pWndOutput->OutputDebugWindow(strOutput);   // Build message window
	}
	//---

	CSocket::OnClose(nErrorCode);
}
