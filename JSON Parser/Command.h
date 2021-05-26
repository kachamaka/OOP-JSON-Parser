#pragma once

#include "Helpers.h"

class Command {
public:
	virtual void exec(const Vector<Pair<ValueType, String>> arguments) {};
	virtual ~Command() {};
};