#pragma once

#include "Command.h"

/// @brief Command child class for the save command
class SaveCommand: protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};