#pragma once

#include "Helpers.h"
#include "JSONStructure.h"

/// @brief Class for all of the JSON Parser functionality
class JSONParser {
	JSONStructure jsonRawData;

	String loadedFile;

	bool loaded = false;
	bool changes = false;
	bool saved = false;

	JSONParser() {};
	~JSONParser() {};

	/// @brief Checks if a file has been loaded
	void checkLoaded() const;

	/// @brief Resets everything to an initial state
	void clearData();
public:
	static JSONParser& Get() {
		static JSONParser JSON;
		return JSON;
	}

	JSONParser(const JSONParser&) = delete;
	JSONParser& operator=(const JSONParser&) = delete;

	/// @brief Constructs the main JSON
	void constructJSON() const;

	/// @brief Opens file from path 
	/// @param path - Path to file
	void open(const String& path);

	/// @brief Constructs empty JSON and prepares an empty base
	void newFile();

	/// @brief Closes current working session with the JSON
	void close();

	/// @brief Saves JSON to the currently loaded file
	/// @param prettyPrint - Option for pretty JSON string
	void save(bool prettyPrint = true);

	/// @brief Saves JSON to a file on the specified path
	/// @param path - Path to file
	/// @param prettyPrint - Option for pretty JSON string
	void saveas(const String& path, bool prettyPrint = true);

	/// @brief Prints currently loaded JSON contents
	/// @param prettyPrint - Option for pretty JSON string
	void print(bool prettyPrint = true);

	/// @brief Validates JSON raw data
	void validate();

	/// @brief Searches for properties with specific key
	/// @param key - Property key
	void search(const String& key) const;

	/// @brief Prints result from last search
	void printSearch() const;

	/// @brief Prints result on the specific position from last search
	/// @param pos - Position for desired property
	void printSearch(Size_T pos) const;

	/// @brief Saves result from search to specified path
	/// @param path - Path to file
	void saveSearch(const String& path) const;
	
	/// @brief Saves result from search on specific position to specified path
	/// @param pos - Position for desired property
	/// @param path - Path to file
	void saveSearch(Size_T pos, const String& path) const;

	/// @brief Sets value of property with specified key
	/// @param key - Key of property
	/// @param value - New value of property
	void set(const String& key, Pair<ValueType, String> value);

	/// @brief Creates new property with specified key and value
	/// @param key - Key for new property
	/// @param value - Value for new property
	void create(const String& key, Pair<ValueType, String> value);

	/// @brief Removes property with specified key
	/// @param key - Key of property
	void remove(const String& key);

	/// @brief Copies value of property with key1 to property with key2
	/// @param key1 - Key of source property
	/// @param key2 - Key of destination property
	void move(const String& key1, const String& key2);
};