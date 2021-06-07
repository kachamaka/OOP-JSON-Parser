#pragma once

#include "Command.h"

/// @brief Command child class for the new command
class NewCommand : protected Command {

public:
	virtual void exec() final;
};