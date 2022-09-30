#include "pch.h"
#include "Invoker.h"


CInvoker::~CInvoker() {
	if (this->on_start_) {
		delete on_start_;
	}

	if (this->on_finish_) {
		delete on_finish_;
	}
}

void CInvoker::SetOnStart(Command* command) {
	this->on_start_ = command;
}

void CInvoker::SetOnFinish(Command* command) {
	this->on_finish_ = command;
}

void CInvoker::DoSomethingImportant()
{
	//std::cout << "CInvoker: Does anybody want something done before I begin?\n";

	if (this->on_start_) {
		this->on_start_->Execute();
	}

	//std::cout << "CInvoker: ...doing something really important...\n";
	//std::cout << "CInvoker: Does anybody want something done after I finish?\n";

	if (this->on_finish_) {
		this->on_finish_->Execute();
	}
}