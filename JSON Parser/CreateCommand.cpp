#include "CreateCommand.h"
#include "Exceptions.h"
#include "JSONParser.h"

void CreateCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	if (arguments.size() != 3) {
		throw invalidCommand;
	}
	if (arguments[1].second[0] != '$' && arguments[1].second[1] != '.') {
		throw invalidCommand;
	}
	JSONParser::Get().create(arguments[1].second, arguments[2]);
}