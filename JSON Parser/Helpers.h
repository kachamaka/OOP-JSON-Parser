#pragma once

#include <string>
#include <vector>
#include <utility>

template <class F, class S>
using Pair = std::pair<F, S>;

template <class T>
using Vector = std::vector<T>;

using String = std::string;

using Size_T = std::size_t;

enum class ValueType {
	string,
	integer,
	doubl,
	boolean,
	null,
	obj,
	arr
};

String toLower(const String& s);
String findPairSubString(const String& str, char openingChar, char closingChar, Size_T& startingPos);
Size_T getNextDotPosInKeyPath(const String& raw, Size_T pos = 0);
Size_T getColonPos(const String& raw);

Size_T getArrayStartIndexFromStringKey(const String& raw);

void parseLine(String& str);
void escapeChars(String& str);
void addTabs(String& str, int numOfTabs);
String formatPretty(const String& rawData);
ValueType getType(const String& val);

bool isInt(const String& str);
bool isDouble(const String& str);
bool isNumber(const String& str);
bool isBool(const String& str);
bool isNull(const String& str);
bool isJSONString(const String& str);
bool isJSON3ValuedLogic(const String& str);
