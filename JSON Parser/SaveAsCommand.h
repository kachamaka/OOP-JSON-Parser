#pragma once

#include "Command.h"

class SaveAsCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};