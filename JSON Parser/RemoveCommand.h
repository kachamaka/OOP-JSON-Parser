#pragma once

#include "Command.h"

class RemoveCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};
