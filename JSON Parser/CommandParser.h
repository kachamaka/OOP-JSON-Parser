#pragma once

#include "Helpers.h"

/// @brief Command parser class for the console commands
class CommandParser {
	String command;
	std::vector<Pair<ValueType, String>> arguments;

	/// @brief Adds argument to the list of arguments
	/// @param arg - Argument in raw state
	void addArgument(String arg);

	/// @brief Execute the current command
	void executeCommand();

	/// @brief Parses command line input to command and arguments
	/// @param line - Command line
	void parseArgments(const std::string& line);

	/// @brief Prints available commands
	static void printCommands();

	/// @brief Clears console for the cls command
	static void clearConsole();

	/// @brief Validates command line input in generic case
	/// @param input - Command line
	static void validateInput(const String& input);

protected:
	bool exit = false;
	/// @brief Transform path according to corresponding OS
	/// @param s - Path string
	static void transformPath(String& s);
public:
	/// @brief Parses command line and executes command
	/// @param line - Command line
	void parse(String line);

	/// @brief Clears current command and arguments
	void resetConsole();

	/// @brief Checks if program should exit
	/// @return exit state
	bool isExit() const;
};