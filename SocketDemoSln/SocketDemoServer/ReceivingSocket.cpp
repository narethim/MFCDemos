#include "pch.h"

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

	TRACE("\t Call CSocket::Detach() to detach it from Server2Socket\n");
	CSocket::Detach();

	CSocket::OnClose(nErrorCode);
}
