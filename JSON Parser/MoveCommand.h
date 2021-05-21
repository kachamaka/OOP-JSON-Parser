#pragma once

#include "Command.h"

class MoveCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};
