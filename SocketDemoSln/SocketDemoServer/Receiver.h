#pragma once

#include <iostream>
#include <string>

/**
 * The Receiver classes contain some important business logic. They know how to
 * perform all kinds of operations, associated with carrying out a request. In
 * fact, any class may serve as a Receiver.
 */

class CReceiver
{
public:
	void DoSomething(const std::string& a) {
		std::cout << "Receiver: Working on (" << a << ".)\n";

		TRACE(_T("CReceiver::DoSomething() = Receiver: Working on (%s)\n"), CString(a.c_str()) );
	}
	void DoSomethingElse(const std::string& b) {
		//std::cout << "Receiver: Also working on (" << b << ".)\n";

		TRACE(_T("CReceiver::DoSomethingElse() = Receiver: Working on (%s)\n"), CString(b.c_str()) );
	}
};

