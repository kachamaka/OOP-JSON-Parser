#pragma once

#include "Command.h"

class SetCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
}; 
