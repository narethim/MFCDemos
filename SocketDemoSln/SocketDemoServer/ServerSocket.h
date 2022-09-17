#pragma once
#include <afxsock.h>

#include "ReceivingSocket.h"

class CServerSocket :
	public CSocket
{
public:
	// ctor
	CServerSocket();					// Default ctor
	CServerSocket(TCHAR* strName);		// ctor with 1 argument
	CServerSocket(TCHAR* strName, TCHAR* strIP, UINT nPort);	// ctor with 3 arguments

	CServerSocket(const CServerSocket &obj);	// Copy ctor

	// Assignment operator overloading
	void operator = (const CServerSocket &obj) {
		m_nPort = obj.m_nPort;
		m_bConnection = obj.m_bConnection;

		m_strSockName  = obj.m_strSockName;
		m_strIPAddress = obj.m_strIPAddress;
		m_ReceivingSocket = obj.m_ReceivingSocket;
	}

	// dtor
	~CServerSocket();

	// Accessors
	bool GetConnection() { return m_bConnection; }
	void SetConnection(bool bVal) { m_bConnection = bVal; }
	UINT GetPort() { return m_nPort; }
	CString GetIPAddress() { return m_strIPAddress; }
	CString GetName() { return m_strSockName; }
	CReceivingSocket* GetSocketPtr() { return &m_ReceivingSocket; }

	// Overrides
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

private:
	// Attribute
	CReceivingSocket m_ReceivingSocket;
	CString m_strSockName;
	CString m_strIPAddress;

	UINT  m_nPort;
	bool  m_bConnection;
};

