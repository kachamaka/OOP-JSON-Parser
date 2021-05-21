#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "Helpers.h"

class JSONProperty;

enum class ObjectType {
	obj,
	arr,
};

class JSONObject {
	Vector<JSONProperty*> properties;

	ObjectType objType = ObjectType::obj;

	JSONObject* parrentPtr = nullptr;

	static Size_T getClosingCharPos(const String& raw, Size_T startPos, char openChar = '{', char closeChar = '}');
public:
	JSONObject(const String& objData = "{}");

	const ObjectType& type() const;

	Size_T size() const;

	String getObjectString() const;
	String getPrettyObjectString() const;

	void addProperty(JSONProperty* prop);
	void removeProperty(JSONProperty* prop);

	void clear();

	JSONProperty* operator[](Size_T pos);
};

