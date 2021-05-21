#pragma once

#include "Helpers.h"
#include "JSONObject.h"

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

	void setChild(JSONObject*);
	JSONObject* getChild() const;
	void deleteChild();

	ValueType getAssociatedType();

};