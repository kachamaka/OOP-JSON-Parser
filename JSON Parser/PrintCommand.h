#pragma once

#include "Command.h"

/// @brief Command child class for the print command
class PrintCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};