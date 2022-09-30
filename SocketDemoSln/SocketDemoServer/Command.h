#pragma once

/**
 * The Command interface declares a method for executing a command.
 */
class Command
{
public:

	// Virtual dtor
	virtual ~Command() {
	}

	virtual void Execute() const = 0;
};

