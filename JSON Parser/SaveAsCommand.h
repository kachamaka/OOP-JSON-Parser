#pragma once

#include "Command.h"

/// @brief Command child class for the saveas command
class SaveAsCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};