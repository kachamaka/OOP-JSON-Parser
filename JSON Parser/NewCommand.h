#pragma once

#include "Command.h"

class NewCommand : protected Command {

public:
	virtual void exec() final;
};