#pragma once

#include "Helpers.h"

/// @brief Class for examining raw JSON data
class JSONStructure {
	String rawData;

	String latestKey;

	/// @brief Validates raw JSON data recursively
	/// @param start - Start position
	/// @param openCh - Opening char of specified block
	/// @param closeCh - Closing char of specified block
	/// @param openAltCh - Alternative opening char of specified block
	/// @param closeAltCh - Alternative closing char of specified block
	/// @return Position for the parrent recursive cycle 
	Size_T validateJSON(Size_T start = 1, char openCh = '{', char closeCh = '}', char openAltCh = '[', char closeAltCh = ']');

	/// @brief Validates key with value according the type of the latter
	/// @param start - Start position for the key and value substring
	/// @param end - End position for the key and value substring
	/// @param objectValue - Specifier if value is object
	void validateKeyValue(Size_T start, Size_T end, bool objectValue);

	/// @brief Validates key
	/// @param key - Key to be validated
	void validateKey(const String& key);

	/// @brief Validates value
	/// @param val - Value to be validated
	static void validateValue(const String& val);
public:
	JSONStructure() {};

	/// @brief Initializes raw JSON data
	/// @param raw - Raw JSON data
	JSONStructure(const String& raw);

	/// @brief Gets raw JSON data
	/// @return Raw JSON data
	const String& get() const;

	/// @brief Clears current structure's properties
	void clear();

	/// @brief Adds string to raw JSON data
	/// @param str - Part of the whole JSON
	void addLine(String str);
	
	/// @brief Validates raw JSON data
	void validate();
};