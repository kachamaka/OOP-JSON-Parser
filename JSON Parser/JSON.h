#pragma once

#include "JSONObject.h"
#include "Helpers.h"

/// @brief Class for the initial JSON object
class JSON {
	JSONObject* jsonObj = nullptr;

	JSON();
	~JSON();

	/// @brief Checks if path ends with .json
	/// @param path - Path string
	static void checkPathExtension(const String& path);

	/// @brief Parses value according to the value type
	/// @param value - Variable with type and value
	static void parseValue(Pair<ValueType, String>& value);

	/// @brief Parses path to key from the command line input
	/// @param key - Key to be parsed
	/// @param keys - List of all parsed keys
	static void parseKeys(const String& key, Vector<Pair<String, String>>& keys);

	/// @brief Searches for specific property according to the path of the keys
	/// @param keys - Keys leading to a specific property
	/// @param currentProp - Current property updated upon examining a single key
	/// @param currentObj - Parrent object of the current property
	static void getPropertyFromKeyPath(const Vector<Pair<String, String>>& keys, JSONProperty*& currentProp, JSONObject*& currentObj);

	/// @brief Creates property to the path of the keys
	/// @param keys - Keys forming a specific path
	/// @param value - Value of the newly created property
	/// @param currentObj - Temporary object whose properties are currently being examined during a search cycle
	static void createProperty(const Vector<Pair<String, String>>& keys, const Pair<ValueType, String>& value, JSONObject*& currentObj);

	/// @brief Moves data from one property to another
	/// @param prop1 - Source property
	/// @param prop2 - Destination property
	static void moveProperty(JSONProperty*& prop1, JSONProperty*& prop2);
public:
	static JSON& Get() {
		static JSON json_instance;
		return json_instance;
	}
	JSON(const JSON&) = delete;
	JSON& operator=(const JSON&) = delete;

	/// @brief Constructs JSON object with raw data
	/// @param raw - Raw JSON data
	void construct(const String& raw = "{}");

	/// @brief Prints JSON contents
	/// @param prettyPrint - Option for pretty JSON string
	void print(bool prettyPrint = true) const;

	/// @brief Saves JSON data to path
	/// @param path - Path of the new .json file
	/// @param prettyPrint - Option for pretty JSON string
	void save(const String& path, bool prettyPrint = true) const;

	/// @brief Sets value to a key
	/// @param key - Path to key
	/// @param value - New value for the property with corresponding key
	void set(const String& key, Pair<ValueType, String> value) const;

	/// @brief Creates property with key from the key path and value
	/// @param key - Path to key
	/// @param value - Value for the new property
	void create(const String& key, Pair<ValueType, String> value) const;

	/// @brief Removes property with corresponding key path
	/// @param key - Path to key
	void remove(const String& key) const;

	/// @brief Moves property data from key1 to key2
	/// @param key1 - Source path to property
	/// @param key2 - Destination path to property
	void move(const String& key1, const String& key2) const;

	/// @brief Deletes all JSON objects/properties and their childs
	void clear();

	/// @brief Gets main JSON object
	/// @return Main JSON object
	JSONObject* getJSON() const;

};
