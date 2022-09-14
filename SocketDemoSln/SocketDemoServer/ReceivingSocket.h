#pragma once
#include <afxsock.h>
class CReceivingSocket :
	public CSocket
{
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

