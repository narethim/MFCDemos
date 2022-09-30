#include "pch.h"

#include "MFCServer.h"
#include "Receiving2Socket.h"


void CReceiving2Socket::OnReceive(int nErrorCode)
{
	TRACE(_T("CReceiving2Socket::OnReceive() - Data Received\n"));

	//	char strRec[256] = "";
	TCHAR strRec[256] = L"";

	int nCount = CSocket::Receive(strRec, 256);
	if (nCount > 0) {
		TRACE(L"\t strRec=%s\n", strRec);
		CString strData(strRec);

		// ((CMFCServerApp*)AfxGetApp())->m_pServerView->AddMsg( (CString)strRec );

		((CMFCServerApp*)AfxGetApp())->m_pServerView->AddMsg(strData);
	}
	CSocket::OnReceive(nErrorCode);
}


void CReceiving2Socket::OnClose(int nErrorCode)
{
	TRACE("CReceiving2Socket::OnClose() - \n");

	TRACE("\t Call CSocket::Detach() to detach it from Server2Socket\n");
	CSocket::Detach();

	CSocket::OnClose(nErrorCode);
}
