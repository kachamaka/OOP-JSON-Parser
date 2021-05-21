#pragma once

#include "Command.h"
#include "CommandParser.h"

class CreateCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};