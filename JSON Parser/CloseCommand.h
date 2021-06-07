#pragma once

#include "Command.h"

/// @brief Command child class for the close command
class CloseCommand : protected Command {

public:
	virtual void exec() final;
};