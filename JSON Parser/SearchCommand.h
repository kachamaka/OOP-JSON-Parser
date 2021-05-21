#pragma once

#include "Command.h"

class SearchCommand : protected Command {

public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) final;
};