#pragma once

#include "Helpers.h"

class JSONProperty;

/// @brief Class for the object type
enum class ObjectType {
	obj,
	arr,
};

/// @brief Class for JSON Object
class JSONObject {
	Vector<JSONProperty*> properties;

	ObjectType objType = ObjectType::obj;

	JSONObject* parrentPtr = nullptr;

	/// @brief Gets the position of the closing char of an object/array disregarding its contents
	/// @param raw - Raw JSON data
	/// @param startPos - Starting position of the search
	/// @param openChar - Open char like '{' or '['
	/// @param closeChar - Closing char like '}' or ']'
	/// @return Closing char position as described above
	static Size_T getClosingCharPos(const String& raw, Size_T startPos, char openChar = '{', char closeChar = '}');
public:
	/// @brief Constructor for JSON Object with raw JSON data
	/// @param objData - Raw JSON data
	JSONObject(const String& objData = "{}");

	/// @brief Gets object type
	/// @return Object type
	const ObjectType& type() const;

	/// @brief Gets number of properties an object has
	/// @return Number of properties
	Size_T size() const;

	/// @brief Parses JSON Object with its properties to JSON raw string
	/// @return JSON raw string
	String getObjectString() const;

	/// @brief Parses JSON Object string and formats it to a more readable version
	/// @return pretty JSON
	String getPrettyObjectString() const;

	/// @brief Adds property to JSON Object
	/// @param prop - Pointer to property to be added
	void addProperty(JSONProperty* prop);

	/// @brief Removes property and its contents
	/// @param prop - Pointer to property to be removed
	void removeProperty(JSONProperty* prop);

	/// @brief Delete all of current object's properties
	void clear();

	/// @brief Indexes current object's properties
	/// @param pos - Position of property
	/// @return Pointer to the property on the desired position
	JSONProperty* operator[](Size_T pos);
};

