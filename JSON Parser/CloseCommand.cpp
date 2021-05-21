#include "CloseCommand.h"
#include "JSONParser.h"

void CloseCommand::exec() {
	JSONParser::Get().close();
}