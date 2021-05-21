#include "PrintCommand.h"

#include "Exceptions.h"
#include "JSONParser.h"

void PrintCommand::exec(const Vector<Pair<ValueType, String>> arguments) {
	JSONParser& jsonParser = JSONParser::Get();
	if (arguments.size() > 3) {
		throw invalidCommand;
	}
	else if (arguments.size() == 3) {
		if (toLower(arguments[1].second) == "search") {
			if (isInt(arguments[2].second)) {
				std::size_t pos = std::stoi(arguments[2].second);
				jsonParser.printSearch(pos);
			}
			else {
				throw invalidCommand;
			}
		}
		else {
			throw invalidCommand;
		}
	}
	else if (arguments.size() == 2) {
		if (toLower(arguments[1].second) == "raw") {
			jsonParser.print(0);
		}
		else if (toLower(arguments[1].second) == "pretty") {
			jsonParser.print();
		}
		else if (toLower(arguments[1].second) == "search") {
			jsonParser.printSearch();
		}
		else {
			throw invalidCommand;
		}
	}
	else {
		jsonParser.print();
	}
}