#pragma once

#include "Command.h"
#include "Receiver.h"

class CComplexCommand :
	public Command
{

private:
	/**
	 * @var Receiver
	 */
	CReceiver* receiver_;

	/**
	 * Context data, required for launching the receiver's methods.
	 */
	std::string a_;
	std::string b_;


public:
	/**
	 * Ctor with 3 params
	 *
	 * Complex commands can accept one or several receiver objects along with any
	 * context data via the constructor.
	 */
	CComplexCommand(CReceiver* receiver, std::string a, std::string b) 
		: receiver_(receiver), a_(a), b_(b) {
	}

	/**
	 * Commands can delegate to any methods of a receiver.
	 */
	void Execute() const override {
		std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
		this->receiver_->DoSomething(this->a_);
		this->receiver_->DoSomethingElse(this->b_);
	}
};

