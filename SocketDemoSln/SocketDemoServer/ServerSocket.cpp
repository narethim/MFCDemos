#include "pch.h"
#include "ServerSocket.h"


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CServerSocket::OnAccept()\n"));
	TRACE(_T("\t Connection accepted\n"));
	//	AfxMessageBox(L"Connection accepted");

	Accept(m_ReceivingSocket);

	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE(_T("CServerSocket::OnReceive()\n"));
	TRACE(_T("\t Data Received\n"));
	// AfxMessageBox(L"Data Received");
	CSocket::OnReceive(nErrorCode);
}
