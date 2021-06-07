#pragma once

#include "JSONProperty.h"

/// @brief Class for the JSON search results
class JSONSearch {
	Vector<JSONProperty*> searchedProperties;

	JSONSearch() {};

	/// @brief Adds all properties that match the specified key
	/// @param obj - Object to be examined
	/// @param key - Key of desired properties
	void searchObjectProperties(JSONObject* obj, const String& key);
public:
	static JSONSearch& Get() {
		static JSONSearch jsonSearch_instance;
		return jsonSearch_instance;
	}

	JSONSearch(const JSONSearch&) = delete;
	JSONSearch& operator=(const JSONSearch&) = delete;

	/// @brief Gets search result in raw string
	/// @return Raw string of the result of the search
	String getSearchString() const;

	/// @brief Gets search result in a more readable version
	/// @return Search result in a readable version
	String getPrettySearchString() const;
	
	/// @brief Searches for properties with specified key
	/// @param key - Key of desired properties
	void search(const String& key);

	/// @brief Prints search result
	void print() const;

	/// @brief Prints property on specified position from the search result data
	/// @param pos - Position of desired property
	void print(Size_T pos) const;
	
	/// @brief Saves search result to specified path
	/// @param path - Path to file
	void save(const String& path) const;

	/// @brief Saves property on specified position from the search result data to specified path
	/// @param pos - Position of desired property
	/// @param path - Path to file
	void save(Size_T pos, const String& path) const;

	/// @brief Gets number of properties found after search
	/// @return Number of properties found
	Size_T size() const;
};

