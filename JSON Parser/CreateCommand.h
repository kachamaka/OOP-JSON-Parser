#pragma once

#include "Command.h"
#include "CommandParser.h"

/// @brief Command child class for the create command
class CreateCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};