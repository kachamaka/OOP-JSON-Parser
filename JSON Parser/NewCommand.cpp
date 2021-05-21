#include "NewCommand.h"

#include "JSONParser.h"

void NewCommand::exec() {
	JSONParser::Get().newFile();
}