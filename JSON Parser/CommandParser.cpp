#include "CommandParser.h"

#include <iostream>

#include "Helpers.h"
#include "Exceptions.h"

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
	std::cout << "open <path> - Opens existing file\n";
	std::cout << "close - Closes currently loaded file\n";
	std::cout << "save <pretty|raw> - Saves already existing file with optional format [default is pretty]\n";
	std::cout << "save search <path> - Saves search result\n";
	std::cout << "save search <position> <path> - Saves element from search result on specified position\n";
	std::cout << "saveas <path> <pretty|raw> - Saves as new file\n";
	std::cout << "new - Creates a new instance with an empty base\n";

	std::cout << "print <pretty|raw> - Prints currently loaded JSON's contents with optional format [default is pretty]\n";
	std::cout << "print search - Prints search contents\n";
	std::cout << "print search <position> - Prints element from search result on specified position\n";
	std::cout << "search <key> - Searches by key\n";
	
	std::cout << "set <key> <value> - Sets value to property with specified key [set $.path.to.key \"value\"]\n";
	std::cout << "create <key> <value> - Creates new property with specified key and value [create $.path.to.key \"value\"]\n";
	std::cout << "remove <key> - Removes property with specified key [remove $.path.to.key]\n";
	std::cout << "move <key1> <key2> - Moves property's contents with key1 to property with key2 [move $.path.to.key1 $.path.to.key2]\n";

	std::cout << "cls - Clears console\n";
	std::cout << "exit - Exits the program\n";
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

