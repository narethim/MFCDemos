#pragma once
#include "Command.h"

#include <iostream>
#include <string>

class CSimpleCommand :
	public Command
{
private:
	std::string pay_load_;

public:

	// Ctor with 1 param
	explicit CSimpleCommand(std::string pay_load) 
		: pay_load_(pay_load)
	{
	}

	void Execute() const override
	{
		// std::cout << "CSimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
		TRACE(_T("CSimpleCommand::Execute() = %s\n"), CString( this->pay_load_.c_str() ) );
	}
};

