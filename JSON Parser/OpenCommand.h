#pragma once

#include "Command.h"
#include "CommandParser.h"

class OpenCommand : protected Command, protected CommandParser {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};