#pragma once

#include "Command.h"

/// @brief Command child class for the remove command
class RemoveCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};
