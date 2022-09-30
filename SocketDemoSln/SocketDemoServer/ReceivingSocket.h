#pragma once
#include <afxsock.h>

#include "Receiver.h"
#include "SocketReceiver.h"
#include "Invoker.h"

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
		m_strID       = obj.m_strID;
		m_bConnection = obj.m_bConnection;
	}

	// Accessors
	CString GetName() { return m_strSockName; }
	void SetName(CString name) { m_strSockName = name; }

	CString GetID() { return m_strID; }
	void SetID(CString id) { m_strID = id; }

	// Overrides
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	CString m_strSockName;
	CString m_strID;
	bool m_bConnection;

	CInvoker  m_CInvoker;
	CReceiver m_CReceiver;
	CSocketReceiver m_CSocketReceiver;
};

