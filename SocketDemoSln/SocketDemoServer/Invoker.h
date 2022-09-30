#pragma once

#include <iostream>

#include "Command.h"

/**
 * The Invoker is associated with one or several commands. It sends a request to
 * the command.
 */

class CInvoker
{
private:
	/**
	 * @var Command
	 */
	Command* on_start_ = nullptr;

	/**
	 * @var Command
	 */
	Command* on_finish_ = nullptr;

public:

	~CInvoker();

	/**
	 * Initialize commands.
	 */
	void SetOnStart(Command* command);
	void SetOnFinish(Command* command);

	/**
	 * The Invoker does not depend on concrete command or receiver classes. The
	 * Invoker passes a request to a receiver indirectly, by executing a command.
	 */
	void DoSomethingImportant();
};

