#pragma once

#include "Command.h"

/// @brief Command child class for the search command
class SearchCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};