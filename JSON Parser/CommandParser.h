#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Helpers.h"

class CommandParser {
	String command;
	std::vector<Pair<ValueType, String>> arguments;

	void addArgument(String arg);

	void executeCommand();

	void parseArgments(const std::string& line);

	static void printCommands();
	static void clearConsole();
	static void validateInput(const String& input);

protected:
	bool exit = false;
	static void transformPath(String& s);
public:
	void parse(String line);
	void resetConsole();
	bool isExit() const;
};