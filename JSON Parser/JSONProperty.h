#pragma once

#include <string>

#include "JSONObject.h"
#include "Helpers.h"


class JSONProperty {
	String key;
	String value;

	ValueType associatedType;

	JSONObject* childPtr = nullptr;
	JSONObject* parrentPtr = nullptr;

public:
	JSONProperty(String, String);

	const String& getKey() const;
	const String& getValue() const;
	void setValue(const String& val);

	String getPropertyString() const;

	void setParrent(JSONObject*);

	void setChild(JSONObject*);
	JSONObject* getChild() const;
	void deleteChild();

	ValueType getAssociatedType();

};