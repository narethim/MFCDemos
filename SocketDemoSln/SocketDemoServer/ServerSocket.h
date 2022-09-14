#pragma once
#include <afxsock.h>

#include "ReceivingSocket.h"

class CServerSocket :
	public CSocket
{
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	CReceivingSocket m_ReceivingSocket;

};

