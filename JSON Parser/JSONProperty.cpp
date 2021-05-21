#include "JSONProperty.h"
#include "Helpers.h"

#include <iostream>

JSONProperty::JSONProperty(String key, String value): key(key), value(value) {
	if (isJSONString(value)) {
		associatedType = ValueType::string;
	}
	else if (isInt(value)) {
		associatedType = ValueType::integer;
	}
	else if (isDouble(value)) {
		associatedType = ValueType::doubl;
	}
	else if (isBool(value)) {
		associatedType = ValueType::boolean;
	}
	else if (isNull(value)) {
		associatedType = ValueType::null;
	}
	else {
		associatedType = ValueType::obj;
	}
}

const String& JSONProperty::getKey() const {
	return key;
}

const String& JSONProperty::getValue() const {
	return value;
}

void JSONProperty::setValue(const String& newVal) {
	value = newVal;
}

String JSONProperty::getPropertyString() const {
	String propStr;
	if (key != "") {
		if (value != "") {
			propStr += key + ':' + value;
		}
		else {
			propStr += key + ':' + childPtr->getObjectString();
		}
	}
	else {
		if (value != "") {
			propStr += value;
		}
		else {
			propStr += childPtr->getObjectString();
		}
	}
	return propStr;
}

void JSONProperty::setParrent(JSONObject* newParrent) {
	parrentPtr = newParrent;
}

void JSONProperty::setChild(JSONObject* newChild) {
	if (newChild->type() == ObjectType::obj) {
		associatedType = ValueType::obj;
	}
	else {
		associatedType = ValueType::arr;
	}
	childPtr = newChild;
}

//void JSONProperty::setAssociatedType(Type t) {
//	associatedType = t;
//}
ValueType JSONProperty::getAssociatedType() {
	return associatedType;
}

JSONObject* JSONProperty::getChild() const {
	return childPtr;
}

void JSONProperty::deleteChild() {
	delete childPtr;
	childPtr = nullptr;
}