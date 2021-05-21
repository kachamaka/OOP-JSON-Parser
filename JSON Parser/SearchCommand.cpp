#include "Exceptions.h"
#include "SearchCommand.h"
#include "JSONParser.h"

void SearchCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	if (arguments.size() != 2) {
		throw invalidCommand;
	}
	JSONParser::Get().search(arguments[1].second);
}