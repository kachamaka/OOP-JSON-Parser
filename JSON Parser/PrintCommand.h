#pragma once

#include "Command.h"

class PrintCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};