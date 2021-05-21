#include "Helpers.h"

#include <regex>

const std::regex intRegex("[-]?[1-9][0-9]*|0");
const std::regex doubleRegex("[-]?[0-9]+.[0-9]+([eE][-]?[0-9]+)?");

String toLower(const String& s) {
	String str = s;
	for (Size_T i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] - 'A' + 'a';
		}
	}
	return str;
}

String findPairSubString(const String& str, char openingChar, char closingChar, Size_T& startingPos) {
	Size_T openingPos = str.find(openingChar, startingPos);
	if (openingPos == String::npos) {
		return "";
	}
	Size_T closingPos = 0;
	int numOfChars = 0;
	bool hasChanged = false;
	for (Size_T i = openingPos; i < str.size(); i++) {
		if (str[i] == openingChar) {
			numOfChars++;
			hasChanged = true;
		}
		if (str[i] == closingChar) {
			numOfChars--;
			if (numOfChars < 0) {
				return "";
			}
		}
		if (hasChanged) {
			if (numOfChars == 0) {
				closingPos = i;
				break;
			}
		}
	}
	if (closingPos >= openingPos) {
		String substr = str.substr(openingPos, closingPos - openingPos + 1);
		startingPos = closingPos;
		return substr;
	}
	return "";
}

Size_T getNextDotPosInKeyPath(const String& raw, Size_T pos) {
	bool inQuotes = false;
	for (Size_T i = pos; i < raw.size(); i++) {
		if (raw[i] == '\\') {
			if (i == raw.size() - 1) {
				throw std::invalid_argument("Invalid input");
			}
			else {
				if (raw[i + 1] == '\"') {
					inQuotes = !inQuotes;
				}
			}
		}
		if (!inQuotes) {
			if (raw[i] == '.') {
				return i;
			}
		}
	}
	return String::npos;
}

Size_T getColonPos(const String& raw) {
	bool inQuotes = false;
	for (Size_T i = 0; i < raw.size(); i++) {
		if (raw[i] == '\"') {
			if (i == 0) {
				inQuotes = true;
			}
			else {
				if (raw[i - 1] != '\\') {
					inQuotes = !inQuotes;
				}
			}
		}
		if (!inQuotes) {
			if (raw[i] == ':') {
				return i;
			}
		}
	}
	return String::npos;
}

Size_T getArrayStartIndexFromStringKey(const String& raw) {
	for (int i = raw.size() - 1; i >= 0; i--) {
		if (raw[i] == '[') {
			return i;
		}
	}
	return String::npos;
}

ValueType getType(const String& val) {
	if (isInt(val)) {
		return ValueType::integer;
	}
	else if (isDouble(val)) {
		return ValueType::doubl;
	}
	else if (isBool(val)) {
		return ValueType::boolean;
	}
	else if (isNull(val)) {
		return ValueType::null;
	}
	else {
		if (val[0] == '{' && val[val.size() - 1] == '}') {
			return ValueType::obj;
		}
		else if (val[0] == '[' && val[val.size() - 1] == ']') {
			return ValueType::arr;
		}
		else {
			return ValueType::string;
		}
	}
}

void parseLine(String& str) {
	String newStr;
	bool inQuotes = false;
	for (Size_T i = 0; i < str.size(); i++) {
		if (str[i] == '\"') {
			if (i == 0) {
				inQuotes = true;
			}
			else {
				if (str[i - 1] != '\\') {
					inQuotes = !inQuotes;
				}
			}
		}
		if (!inQuotes) {
			if (std::isspace(str[i])) {
				continue;
			}
		}
		newStr += str[i];
	}
	str = newStr;
}

void escapeChars(String& str) {
	String newStr;
	for (Size_T i = 0; i < str.size(); i++) {
		if (str[i] == '\\') {
			if (i <= str.size() - 2 && str[i + 1] == '\\') {
				newStr += '\\';
			}
			continue;
		}
		newStr += str[i];
	}
	str = newStr;
}

void addTabs(String& str, int numOfTabs) {
	for (int i = 0; i < numOfTabs; i++) {
		str += ' ';
		str += ' ';
	}
}
String formatPretty(const String& rawData) {
	String formattedData;
	int numOfTabs = 0;
	bool inQuotes = false;
	for (Size_T i = 0; i < rawData.size(); i++) {
		if (rawData[i] == '\"' && rawData[i - 1] != '\\') {
			inQuotes = !inQuotes;
		}
		if (!inQuotes) {
			if (rawData[i] == '{' || rawData[i] == '[') {
				if (rawData[i + 1] == '}') {
					formattedData += "{}";
					i = i + 1;
					continue;
				}
				if (rawData[i + 1] == ']') {
					formattedData += "[]";
					i = i + 1;
					continue;
				}
				numOfTabs++;
			}
			if (rawData[i] == '}' || rawData[i] == ']') {
				numOfTabs--;
			}

			if ((rawData[i] == '}' && rawData[i - 1] != '{') || (rawData[i] == ']' && rawData[i - 1] != '[')) {
				formattedData += '\n';
				addTabs(formattedData, numOfTabs);
			}

			formattedData += rawData[i];
			if (rawData[i] == ':') {
				formattedData += ' ';
			}

			if (rawData[i] == '{' || rawData[i] == '[') {
				formattedData += '\n';
				if (rawData[i + 1] == '}' || rawData[i + 1] == ']') {
					addTabs(formattedData, numOfTabs - 1);
				}
				else {
					addTabs(formattedData, numOfTabs);
				}
			}
			if (rawData[i] == ',') {
				formattedData += '\n';
				addTabs(formattedData, numOfTabs);
			}
		}
		else {
			formattedData += rawData[i];
		}

	}
	return formattedData;
}

bool isInt(const String& str) {
	return std::regex_match(str, intRegex);
}
bool isDouble(const String& str) {
	return std::regex_match(str, doubleRegex);
}
bool isNumber(const String& str) {
	return isInt(str) || isDouble(str);
}
bool isBool(const String& str) {
	return str == "true" || str == "false";
}
bool isNull(const String& str) {
	return str == "null";
}
bool isJSONString(const String& str) {
	if (str[0] != '\"' || str[str.size() - 1] != '\"') {
		return false;
	}

	short quotesCount = 0;
	for (Size_T i = 0; i < str.size(); i++) {
		if (str[i] == '\"') {
			if (i > 0) {
				if (str[i - 1] != '\\') {
					quotesCount++;
				}
			}
			else {
				quotesCount++;
			}
		}
		if (str[i] == '\\') {
			if (str[i + 1] == 't' ||
				str[i + 1] == 'r' ||
				str[i + 1] == 'n' ||
				str[i + 1] == 'f' ||
				str[i + 1] == 'b' ||
				str[i + 1] == '/' ||
				str[i + 1] == '\\' ||
				str[i + 1] == '\"') {
				i++;
				continue;
			}
			else {
				return false;
			}
		}
	}
	return quotesCount == 2;
}
bool isJSON3ValuedLogic(const String& str) {
	return isBool(str) || isNull(str);
}
