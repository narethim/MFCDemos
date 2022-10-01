#pragma once

#include "pch.h"

//#include "ReceivingSocket.h"

#include <iostream>
#include <string>

class CReceivingSocket;		// forward declaration

/**
 * The Receiver classes contain some important business logic. They know how to
 * perform all kinds of operations, associated with carrying out a request. In
 * fact, any class may serve as a Receiver.
 */

class CSocketReceiver
{
public:
	void ProcessCommand(const CString& a);
	
	void ProcessCommand2(CReceivingSocket* psocket, const CString& a);

private:
	void HandleDIOMessage(CReceivingSocket* psocket, const CString& a);

	void HandleVssMessage(CReceivingSocket* psocket, const CString& a);
	void HandleVpMessage(CReceivingSocket* psocket, const CString& a);
	void HandleVddMessage(CReceivingSocket* psocket, const CString& a);
};

