#pragma once

#include "Helpers.h"
#include "JSONObject.h"

/// @brief Class for JSON Properties
class JSONProperty {
	String key;
	String value;

	ValueType associatedType;

	JSONObject* childPtr = nullptr;
	JSONObject* parrentPtr = nullptr;

public:
	/// @brief Constructing JSON Property
	/// @param key - Key of property
	/// @param value - Value of property
	JSONProperty(String key, String value);

	/// @brief Gets property key
	/// @return Property key
	const String& getKey() const;

	/// @brief Gets property value
	/// @return Property value
	const String& getValue() const;

	/// @brief Sets property value
	/// @param val - New property value
	void setValue(const String& val);

	/// @brief Gets raw string of property
	/// @return Raw property string
	String getPropertyString() const;

	/// @brief Sets new property child
	/// @param newChild - Pointer to new child
	void setChild(JSONObject* newChild);

	/// @brief Gets pointer to child
	/// @return Pointer to child
	JSONObject* getChild() const;

	/// @brief Deletes child pointer
	void deleteChild();

	/// @brief Gets type of property's value
	/// @return Property's value type /if property has child it returns child's type/
	ValueType getAssociatedType();
};