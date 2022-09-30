#pragma once

#include "pch.h"
#include "Command.h"

// #include "Receiver.h"
#include "SocketReceiver.h"
#include "ReceivingSocket.h"


class CScpiCommand :
	public Command
{
private:
	/**
	 * @var Receiver
	 */
	// CReceiver* receiver_;

	CSocketReceiver* m_pCSocketReceiver;
	CReceivingSocket* m_pCReceivingSocket;

	/**
	 * Context data, required for launching the receiver's methods.
	 */
	//std::string a_;
	//std::string b_;

	CString strData;

public:
	/**
	 * Ctor with 3 params
	 *
	 * Complex commands can accept one or several receiver objects along with any
	 * context data via the constructor.
	 */
	//CScpiCommand(CReceiver* receiver, std::string a, std::string b)
	//	: receiver_(receiver), a_(a), b_(b) {
	//}

	/**
	 * Ctor with 3 params
	 *
	 * Complex commands can accept one or several receiver objects along with any
	 * context data via the constructor.
	 */
	CScpiCommand(CSocketReceiver* receiver, CReceivingSocket* pCReceivingSocket, CString str)
		: m_pCSocketReceiver(receiver), m_pCReceivingSocket(pCReceivingSocket), strData(str) {
	}


	/**
	 * Commands can delegate to any methods of a receiver.
	 */
	void Execute() const override {
		std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";

		//this->receiver_->DoSomething(this->a_);
		//this->receiver_->DoSomethingElse(this->b_);

//		this->m_pCSocketReceiver->ProcessCommand( this->strData );

		this->m_pCSocketReceiver->ProcessCommand2(m_pCReceivingSocket, this->strData);
	}

};

