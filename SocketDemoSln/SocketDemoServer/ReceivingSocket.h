#pragma once
#include <afxsock.h>

class CReceivingSocket :
	public CSocket
{
public:
	// ctor
	CReceivingSocket();								// Default ctor
	CReceivingSocket(CString strName);				// ctor with 1 argument
	CReceivingSocket(const CReceivingSocket& obj);	// Copy ctor

	~CReceivingSocket();							// dtor

	// Assignment operator overloading
	void operator = (const CReceivingSocket& obj) {
		m_strSockName = obj.m_strSockName;
		m_bConnection = obj.m_bConnection;
	}

	// Accessors
	CString GetName() { return m_strSockName; }
	void SetName(CString name) { m_strSockName = name; }

	// Overrides
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	CString m_strSockName;
	bool m_bConnection;
};

