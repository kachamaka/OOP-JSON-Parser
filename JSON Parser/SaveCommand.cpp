#include "Exceptions.h"
#include "SaveCommand.h"
#include "JSONParser.h"

void SaveCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	JSONParser& jsonParser = JSONParser::Get();
	if (arguments.size() > 4) {
		throw invalidCommand;
	}
	else if (arguments.size() == 4) {
		if (toLower(arguments[1].second) == "search") {
			if (isInt(arguments[2].second)) {
				//save search <position> <path>
				std::size_t pos = std::stoi(arguments[2].second);
				jsonParser.saveSearch(pos, arguments[3].second);
			}
			else {
				throw invalidCommand;
			}
		}
		else {
			throw invalidCommand;
		}
	}
	else if (arguments.size() == 3) {
		//save search <path>
		if (toLower(arguments[1].second) == "search") {
			jsonParser.saveSearch(arguments[2].second);
		}
		else {
			throw invalidCommand;
		}
	}
	else if (arguments.size() == 2) {
		if (toLower(arguments[1].second) == "pretty") {
			jsonParser.save(1);
		}
		else if (toLower(arguments[1].second) == "raw") {
			jsonParser.save(0);
		}
		else {
			throw invalidCommand;
		}
	}
	else {
		jsonParser.save(1);
	}
}