#pragma once
#include <afxsock.h>

#include "ReceivingSocket.h"

class CServerSocket :
	public CSocket
{
public:

	CServerSocket();
	CServerSocket(TCHAR* strName);
	CServerSocket(TCHAR* strName, TCHAR* strIP, UINT nPort);
	~CServerSocket();

	bool GetConnection() { return m_bConnection; }
	void SetConnection(bool bVal) { m_bConnection = bVal; }
	UINT GetPort() { return m_nPort; }
	LPCTSTR GetIPAddress() { return m_strIPAddress; }

	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	CReceivingSocket m_ReceivingSocket;

private:
	TCHAR m_strSockName[64];
	TCHAR m_strIPAddress[24];
	UINT  m_nPort;
	bool  m_bConnection;
};

