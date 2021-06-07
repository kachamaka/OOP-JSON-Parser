#pragma once

#include "Command.h"

/// @brief Command child class for the move command
class MoveCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};
