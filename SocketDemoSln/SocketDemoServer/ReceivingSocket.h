#pragma once
#include <afxsock.h>

class CReceivingSocket :
	public CSocket
{
public:
	CReceivingSocket();
	CReceivingSocket(CString strName);
	~CReceivingSocket();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	CString m_strSockName;
	bool m_bConnection;
};

