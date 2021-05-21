#include "Exceptions.h"
#include "RemoveCommand.h"
#include "JSONParser.h"

void RemoveCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	if (arguments.size() != 2) {
		throw invalidCommand;
	}
	if (arguments[1].second[0] != '$' && arguments[1].second[1] != '.') {
		throw invalidCommand;
	}
	JSONParser::Get().remove(arguments[1].second);
}