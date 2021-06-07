#pragma once

#include "Helpers.h"

/// @brief Command class parrent for all the commands
class Command {
public:
	/// @brief Function for command execution
	/// @param arguments - Corresponding arguments for the specific command class
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) {};
	virtual ~Command() {};
};