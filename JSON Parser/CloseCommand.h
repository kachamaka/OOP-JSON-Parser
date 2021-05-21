#pragma once

#include "Command.h"

class CloseCommand : protected Command {

public:
	virtual void exec() final;
};