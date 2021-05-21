#pragma once

#include "Helpers.h"

class JSONStructure {
	String rawData;

	String latestKey;

	Size_T validateJSON(Size_T start = 1, char openCh = '{', char closeCh = '}', char openAltCh = '[', char closeAltCh = ']');

	void validateKeyValue(Size_T start, Size_T end, bool objectValue);

	void validateKey(const String& value);
	static void validateValue(const String& val);
public:
	JSONStructure() {};

	JSONStructure(const String& raw);

	const String& get() const;

	void clear();
	void addLine(String);
	void print(bool prettyPrint);
	void validate();
};