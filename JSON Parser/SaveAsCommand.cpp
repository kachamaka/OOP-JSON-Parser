#include "Exceptions.h"
#include "SaveAsCommand.h"
#include "JSONParser.h"

void SaveAsCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	JSONParser& jsonParser = JSONParser::Get();
	if (arguments.size() > 3 || arguments.size() < 2) {
		throw invalidCommand;
	}
	else if (arguments.size() == 3) {
		if (toLower(arguments[2].second) == "pretty") {
			jsonParser.saveas(arguments[1].second, 1);
		}
		else if (toLower(arguments[2].second) == "raw") {
			jsonParser.saveas(arguments[1].second, 0);
		}
		else {
			throw invalidCommand;
		}
	}
	else {
		jsonParser.saveas(arguments[1].second, 1);
	}
}
