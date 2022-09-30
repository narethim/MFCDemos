#pragma once
#include <afxsock.h>
class CReceiving2Socket :
	public CSocket
{
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

