#pragma once

#include "Command.h"

/// @brief Command child class for the set command
class SetCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
}; 
