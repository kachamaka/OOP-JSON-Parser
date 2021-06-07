#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

/// @brief Simpler std::pair syntax
/// @tparam F - First class
/// @tparam S - Second class
template <class F, class S>
using Pair = std::pair<F, S>;

/// @brief Simpler std::vector syntax
/// @tparam T - Template class
template <class T>
using Vector = std::vector<T>;

/// @brief Simpler std::string syntax
using String = std::string;

/// @brief Simpler std::size_t syntax
using Size_T = std::size_t;

/// @brief All possible JSON value types
enum class ValueType {
	string,
	integer,
	doubl,
	boolean,
	null,
	obj,
	arr
};

/// @brief Modify string to lower case
/// @param s - String to be modified
/// @return String in lower case
String toLower(const String& s);

/// @brief Searches for a substring enclosed with a pair of two characters 
/// like [] and {} in order to accept objects or arrays as command arguments for some of the commands
/// @param str - String to be examined
/// @param openingChar - Opening char like '[' or '{'
/// @param closingChar - Closing char like ']' or '}'
/// @param startingPos - Starting position of the search
/// @return Substring that meets the conditions in the description
String findPairSubString(const String& str, char openingChar, char closingChar, Size_T& startingPos);

/// @brief Gets position of the next dot char in the path to the key of a JSON property
/// @param raw - Raw path to key from the command line
/// @param pos - Starting position for the search
/// @return Position of the next dot in the raw path
Size_T getNextDotPosInKeyPath(const String& raw, Size_T pos = 0);

/// @brief Gets first colon position in a string
/// @param raw - String to be examined
/// @return First colon position
Size_T getColonPos(const String& raw);

/// @brief Gets position of the first '[' char in a string
/// @param raw - String with possible brackets like "property[42]"
/// @return Position of the first '[' char
Size_T getArrayStartIndexFromStringKey(const String& raw);

/// @brief Parses string by removing all white spaces and producing a raw string
/// @param str - Input string to be modified into raw single-line string
void parseLine(String& str);

/// @brief Escapes the backslash char
/// @param str - String to be modified
void escapeChars(String& str);

/// @brief Adds tabs to the end of a string
/// @param str - String to be modified
/// @param numOfTabs - Number of tabs to be added
void addTabs(String& str, int numOfTabs);

/// @brief Formats single-line JSON string to a more readable version
/// @param rawData - Raw JSON string
/// @return Formatted JSON string
String formatPretty(const String& rawData);

/// @brief Gets type of raw value string
/// @param val - Raw value string
/// @return Type of raw value string
ValueType getType(const String& val);

/// @brief Checks if raw string is integer
/// @param str - Raw string
/// @return If raw string is integer
bool isInt(const String& str);

/// @brief Checks if raw string is double
/// @param str - Raw string
/// @return If raw string is double
bool isDouble(const String& str);

/// @brief Checks if raw string is number
/// @param str - Raw string
/// @return If raw string is a number
bool isNumber(const String& str);

/// @brief Checks if raw string is boolean
/// @param str - Raw string
/// @return If raw string is a boolean
bool isBool(const String& str);

/// @brief Checks if raw string is null
/// @param str - Raw string
/// @return If raw string is null
bool isNull(const String& str);

/// @brief Checks if raw string is string according to JSON conventions
/// @param str - Raw string
/// @return If raw string is JSON string
bool isJSONString(const String& str);

/// @brief Checks if raw string is boolean or null
/// @param str - Raw string
/// @return If raw string is boolean or null
bool isJSON3ValuedLogic(const String& str);
