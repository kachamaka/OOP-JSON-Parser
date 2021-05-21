#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "Helpers.h"
#include "Exceptions.h"

#include "CommandParser.h"

#include "OpenCommand.h"
#include "CloseCommand.h"
#include "NewCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "PrintCommand.h"
#include "SearchCommand.h"
#include "SetCommand.h"
#include "CreateCommand.h"
#include "RemoveCommand.h"
#include "MoveCommand.h"


void CommandParser::parse(String line) {
	validateInput(line);

	parseArgments(line);

	//---------------------------------- print args -- test fnc -> delete later
	//for (std::size_t i = 0; i < arguments.size(); i++) {
	//	std::cout << "Arg " << i << " -> " << getTypeToString(arguments[i].first) << " : " << arguments[i].second << std::endl;
	//}
	//-----------------------------------

	command = toLower(arguments[0].second);

	try {
		executeCommand();
	}
	catch (...) {
		resetConsole();
		throw;
	}

	resetConsole();
}

void CommandParser::executeCommand() {
	if (arguments.size() == 0) {
		throw invalidCommand;
	}

	if (command == "?" || command == "help") {
		printCommands();
	}
	else if (command == "cls" || command == "clear") {
		clearConsole();
	}
	else if (command == "exit") {
		CloseCommand close;
		close.exec();
		exit = true;
	}
	else if (command == "open") {
		OpenCommand open;
		open.exec(arguments);
	}
	else if (command == "close") {
		CloseCommand close;
		close.exec();
	}
	//else if (command == "validate") {
	//	jsonParser.validate();
	//}
	else if (command == "new") {
		NewCommand newCmd;
		newCmd.exec();
	}
	else if (command == "save") {
		SaveCommand save;
		save.exec(arguments);
	}
	else if (command == "saveas") {
		SaveAsCommand saveAs;
		saveAs.exec(arguments);
	}
	else if (command == "print") {
		PrintCommand print;
		print.exec(arguments);
	}
	else if (command == "search") {
		SearchCommand search;
		search.exec(arguments);
	}
	else if (command == "create") {
		CreateCommand create;
		create.exec(arguments);
	}
	else if (command == "set") {
		SetCommand set;
		set.exec(arguments);
	}
	else if (command == "move") {
		MoveCommand move;
		move.exec(arguments);
	}
	else if (command == "remove") {
		RemoveCommand remove;
		remove.exec(arguments);
	}
	else {
		//no command
		throw invalidCommand;
	}
}

void CommandParser::transformPath(String& s) {
#ifdef _WIN32
	String newS;
	for (std::size_t i = 0; i < s.size(); i++) {
		newS += s[i];
		if (s[i] == '\\') {
			newS += "\\";
		}
	}
	s = newS;
#endif
}

void CommandParser::resetConsole() {
	command = "";
	arguments.clear();
}

void CommandParser::clearConsole() {
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}

void CommandParser::printCommands() {
	std::cout << "open <path> - Open existing file\n";
	std::cout << "close - Close currently loaded file\n";
	std::cout << "save <pretty|raw> - Save already existing file\n";
	std::cout << "save search <path> - Save search result\n";
	std::cout << "save search <position> <path> - Save search element result\n";
	std::cout << "saveas <name> <pretty|raw> - Save as new file\n";
	std::cout << "new - Create an empty instance\n";

	std::cout << "print <pretty|raw> - Print contents\n";
	std::cout << "print search - Print searched contents\n";
	std::cout << "print search <position> - Print element from searched contents\n";
	std::cout << "search <key> - Search by key\n";
	//edit or set? 
	std::cout << "set <key> <value> - Set value to a key [set $.key \"value\"]\n";
	std::cout << "create <key> <value> - Create new key with value [create $.key \"value\"]\n";
	std::cout << "remove <key> - Remove key with value [remove $.key]\n";
	std::cout << "move <key1> <key2> - Move value from key1 to key2 [move $.key1 $.key2]\n";

	std::cout << "cls - Clear console\n";
	std::cout << "exit - Exit\n";
}

void CommandParser::validateInput(const String& input) {
	//validation in generic case
	if (input.size() == 0) {
		throw invalidInput;
	}
}

void CommandParser::addArgument(String arg) {
	ValueType type = getType(arg);
	arguments.push_back(std::make_pair(type, arg));
}

bool CommandParser::isExit() const {
	return exit;
}

void CommandParser::parseArgments(const std::string& line) {
	std::size_t argStart = 0;
	std::size_t argEnd = 0;

	bool inQuotes = false;
	bool inWord = false;

	char startingChar = '\0';
	std::size_t updatedPos = 0;

	std::size_t len = line.size();
	for (std::size_t i = 0; i < len; i++) {
		if (!inWord) {
			if (!inQuotes) {
				if (line[i] == ' ') {
					if (i == len - 2 && line[i + 1] != ' ') {
						String arg;
						arg += line[len - 1];
						addArgument(arg);
						break;
					}
					else {
						argStart = i;
						continue;
					}
				}
				else if (line[i] == '$') {
					bool inQuotes = false;
					for (std::size_t j = i; j < len; j++) {
						if (line[j] == '\"') {
							if (line[j - 1] != '\\') {
								inQuotes = !inQuotes;
							}
						}
						if (!inQuotes) {
							if (line[j] == ' ' || j == line.size() - 1) {
								std::size_t length = j == line.size() - 1 ? j - i + 1 : j - i;
								String arg = line.substr(i, length);
								addArgument(arg);
								i = j;
								break;
							}
						}
					}
				}
				else {
					if (line[i] == '\"' || line[i] == '{' || line[i] == '[') {
						if (i == len - 1) {
							String arg;
							arg += line[i];
							addArgument(arg);
						}
						argStart = i;
						startingChar = line[i];
						inQuotes = true;
						continue;
					}
					else {
						if (i == len - 1) {
							String arg;
							arg += line[i];
							addArgument(arg);
						}
						argStart = i;
						inWord = true;
						continue;
					}
				}
			}
			else {
				if (startingChar == '\"') {
					if (line[i] == '\"') {
						if (line[i] == '\"' && i > 0 && line[i - 1] == '\\') {
							continue;
						}
						if ((i < len - 1 && line[i + 1] == ' ') || i == len - 1) {
							argEnd = i;
							String addArg = line.substr(argStart, argEnd - argStart + 1);
							addArgument(addArg);
							updatedPos = i;
							inQuotes = false;
						}
					}
				}
				else {
					String substr;
					Pair<char, char> pairedChars;
					if (startingChar == '{') {
						pairedChars = std::make_pair('{', '}');
					}
					if (startingChar == '[') {
						pairedChars = std::make_pair('[', ']');
					}
					substr = findPairSubString(line, pairedChars.first, pairedChars.second, updatedPos);
					if (substr == "") {
						throw invalidInput;
					}
					addArgument(substr);

					i = updatedPos;
					argStart = i;
					inQuotes = false;
				}
			}
		}
		else {
			if (line[i] == ' ' || i == len - 1) {
				argEnd = (i == len - 1 ? i + 1 : i);
				String addLine = line.substr(argStart, argEnd - argStart);
				addArgument(addLine);
				updatedPos = i;
				inWord = false;
			}
		}
	}
}

