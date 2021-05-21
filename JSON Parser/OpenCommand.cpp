#include "Exceptions.h"
#include "OpenCommand.h"
#include "JSONParser.h"

void OpenCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	if (arguments.size() > 2) {
		throw invalidCommand;
	}
	String path = arguments[1].second;
	transformPath(path);
	JSONParser::Get().open(path);
}