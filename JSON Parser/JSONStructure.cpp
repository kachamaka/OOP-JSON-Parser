#include <iostream>
#include <fstream>

#include "JSONStructure.h"

JSONStructure::JSONStructure(const String& raw) {
	rawData = raw;
}

const String& JSONStructure::get() const {
	return rawData;
}

void JSONStructure::clear() {
	rawData = "";
	latestKey = "";
}

void JSONStructure::addLine(String str) {
	rawData += str;
}

void JSONStructure::validateValue(const String& value) {
	if (!isJSONString(value)) {
		if (!isNumber(value) && !isJSON3ValuedLogic(value)) {
			String errorMsg = "Invalid JSON: Invalid value near: ";
			errorMsg += value;
			throw std::invalid_argument(errorMsg);
		}
	}
}
void JSONStructure::validateKey(const String& key) {
	if (!isJSONString(key)) {
		String errorMsg = "Invalid JSON: Invalid key near: ";
		errorMsg += key != "" ? key : latestKey;
		throw std::invalid_argument(errorMsg);
	}
	latestKey = key;
}

void JSONStructure::validateKeyValue(Size_T start, Size_T end, bool objectValue) {
	if (objectValue) {
		String keyWithValue = rawData.substr(start, end - start);
		Size_T middle = getColonPos(keyWithValue);
		if (middle == String::npos) {
			validateValue(keyWithValue);
		}
		else {
			String key = keyWithValue.substr(0, middle);
			String value = keyWithValue.substr(middle + 1);

			validateValue(value);
			validateKey(key);
		}
	}
	else {
		String value = rawData.substr(start, end - start);
		validateValue(value);
	}
}

Size_T JSONStructure::validateJSON(
	Size_T start ,
	char openCh,
	char closeCh,
	char openAltCh,
	char closeAltCh) {
	bool inQuotes = false;
	bool objVal = openCh == '{' ? true : false;
	Size_T end = 0;
	for (Size_T i = start; i < rawData.size(); i++) {
		if (rawData[i] == '\"' && rawData[i - 1] != '\\') {
			inQuotes = !inQuotes;
		}
		if (!inQuotes) {

			if (rawData[i] == ',') {
				if (rawData[i + 1] == ',') {
					String errorMsg = "Invalid JSON: Invalid property near: ";
					errorMsg += rawData.substr(start, i + 1 - start);
					throw std::invalid_argument(errorMsg);
				}

				end = i;

				if (start < end) {
					validateKeyValue(start, end, objVal);
				}
				else {
					//invalid
					String errorMsg = "Invalid JSON: Error near: ";
					errorMsg += rawData.substr(start, i + 1 - start);
					throw std::invalid_argument(errorMsg);
				}
				start = i + 1;
			}
			if (rawData[i] == openCh) {
				if (rawData[i + 1] == closeCh) {
					i = i + 2;
					end = i;
					start = i + 1;
				}
				else if (rawData[i + 1] == openCh) {
					//invalid
					String errorMsg = "Invalid JSON: Double opening braces/brackets near: ";
					errorMsg += rawData.substr(start, i + 1 - start);
					throw std::invalid_argument(errorMsg);
				}
				else {
					end = i;

					if (start < end) {
						//nested object name
						String key = rawData.substr(start, end - start - 1);
						validateKey(key);
					}

					i = validateJSON(i + 1, openCh, closeCh, openAltCh, closeAltCh);
					if (rawData[i + 1] == ',') {
						i++;
						start = i + 1;
					}
					if (rawData[i + 1] == closeCh || rawData[i + 1] == closeAltCh) {
						i++;
						start = i;
					}
				}
			}
			if (rawData[i] == openAltCh) {
				if (rawData[i + 1] == openAltCh) {
					//invalid
					String errorMsg = "Invalid JSON: Double opening braces/brackets near: ";
					errorMsg += rawData.substr(start, i + 1 - start);
					throw std::invalid_argument(errorMsg);
				}

				end = i;
				if (start < end) {
					//nested object name
					String key = rawData.substr(start, end - start - 1);
					validateKey(key);
				}

				i = validateJSON(i + 1, openAltCh, closeAltCh, openCh, closeCh);

				if (rawData[i + 1] == ',') {
					i++;
					start = i + 1;
				}
				if (rawData[i + 1] == closeCh || rawData[i + 1] == closeAltCh) {
					i++;
					start = i;
				}
			}
			if (rawData[i] == closeCh) {
				if (rawData[i - 1] == ',') {
					String errorMsg = "Invalid JSON: Comma at end of object near: ";
					errorMsg += rawData.substr(start, i + 1 - start);
					throw std::invalid_argument(errorMsg);
				}
				end = i;
				if (start < end) {
					validateKeyValue(start, end, objVal);
				}
				return i;
			}
		}
		else {
			if (i == rawData.size() - 1) {
				String errorMsg = "Invalid JSON: No closing quotes near: ";
				errorMsg += rawData.substr(start, i + 1 - start);
				throw std::invalid_argument(errorMsg);
			}
		}
	}
	return 0;
}

void JSONStructure::validate() {
	validateJSON();
}
