#include "JSONObject.h"

#include <iostream>
#include <stdexcept>

#include "Helpers.h"
#include "JSONProperty.h"

Size_T JSONObject::getClosingCharPos(const String& raw, Size_T startPos, char openChar, char closeChar) {
	int count = 0;
	bool inQuotes = false;
	for (Size_T i = startPos; i < raw.size(); i++) {
		if (raw[i] == '\"') {
			if (raw[i - 1] != '\\') {
				inQuotes = !inQuotes;
			}
		}
		if (!inQuotes) {
			if (raw[i] == openChar) {
				count++;
			}
			if (raw[i] == closeChar) {
				count--;
			}
			if (count == 0) {
				return i;
			}
		}
	}
	return String::npos;
}

JSONObject::JSONObject(const String& raw) {
	if (raw == "") {
		return;
	}
	if (raw[0] == '{') {
		objType = ObjectType::obj;
		bool inQuotes = false;
		Size_T start = 1;
		for (Size_T i = 1; i < raw.size(); i++) {
			if (raw[i] == '\"') {
				if (raw[i - 1] != '\\') {
					inQuotes = !inQuotes;
				}
			}
			if (!inQuotes) {
				if (raw[i] == ',') {
					if (start == i) {
						start = i + 1;
						continue;
					}
					String propName = raw.substr(start, i - start);
					Size_T colonPos = getColonPos(propName);
					if (colonPos == String::npos) {
						String msg = "JSON Parse error... Error near " + raw.substr(start, i - start + 1);
						throw std::invalid_argument(msg);
					}
					String key = propName.substr(0, colonPos);
					String value = propName.substr(colonPos + 1);
					JSONProperty* prop = new JSONProperty(key, value);

					properties.push_back(prop);
					start = i + 1;
				}
				else if (raw[i] == '{') {
					String key = raw.substr(start, i - start - 1);
					JSONProperty* prop = new JSONProperty(key, "");

					Size_T closingPos = getClosingCharPos(raw, i, '{', '}');
					String newRaw = raw.substr(i, closingPos + 1 - i);

					JSONObject* nestedObj = new JSONObject(newRaw);
					nestedObj->parrentPtr = this;

					prop->setChild(nestedObj);

					properties.push_back(prop);

					i = closingPos;
					start = closingPos + 1;
				}
				else if (raw[i] == '[') {
					String key = raw.substr(start, i - start - 1);
					JSONProperty* prop = new JSONProperty(key, "");

					Size_T closingPos = getClosingCharPos(raw, i, '[', ']');
					String newRaw = raw.substr(i, closingPos + 1 - i);

					JSONObject* nestedObj = new JSONObject(newRaw);
					nestedObj->parrentPtr = this;

					prop->setChild(nestedObj);

					properties.push_back(prop);

					i = closingPos;
					start = closingPos + 1;
				}
				else if (raw[i] == '}') {
					if (start != i) {
						String propName = raw.substr(start, i - start);
						Size_T colonPos = getColonPos(propName);
						if (colonPos == String::npos) {
							String msg = "JSON Parse error... Error near " + raw.substr(start, i - start + 1);
							throw std::invalid_argument(msg);
						}
						String key = propName.substr(0, colonPos);
						String value = propName.substr(colonPos + 1);
						JSONProperty* prop = new JSONProperty(key, value);

						properties.push_back(prop);
					}
					start = i + 1;
				}
			}
		}
	}
	else if (raw[0] == '[') {
		objType = ObjectType::arr;
		bool inQuotes = false;
		Size_T start = 1;
		for (Size_T i = 1; i < raw.size(); i++) {
			if (raw[i] == '\"') {
				if (raw[i - 1] != '\\') {
					inQuotes = !inQuotes;
				}
			}
			if (!inQuotes) {
				if (raw[i] == ',') {
					if (start == i) {
						start = i + 1;
						continue;
					}
					String value = raw.substr(start, i - start);

					JSONProperty* prop = new JSONProperty("", value);

					properties.push_back(prop);
					start = i + 1;
				}else if (raw[i] == '{') {
					JSONProperty* prop = new JSONProperty("", "");
					
					Size_T closingPos = getClosingCharPos(raw, i, '{', '}');
					String newRaw = raw.substr(i, closingPos + 1 - i);

					JSONObject* nestedObj = new JSONObject(newRaw);
					nestedObj->parrentPtr = this;
					
					prop->setChild(nestedObj);

					properties.push_back(prop);

					i = closingPos;
					start = closingPos + 1;
				}
				else if (raw[i] == '[') {
					JSONProperty* prop = new JSONProperty("", "");

					Size_T closingPos = getClosingCharPos(raw, i, '[', ']');
					String newRaw = raw.substr(i, closingPos + 1 - i);

					JSONObject* nestedObj = new JSONObject(newRaw);
					nestedObj->parrentPtr = this;

					prop->setChild(nestedObj);

					properties.push_back(prop);

					i = closingPos;
					start = closingPos + 1;
				}
				else if (raw[i] == ']') {
					if (start != i) {
						String value = raw.substr(start, i - start);

						JSONProperty* prop = new JSONProperty("", value);

						properties.push_back(prop);
					}
					start = i + 1;
				}
			}
		}
	}
	else {
		throw std::invalid_argument("Invalid JSON data");
	}
}

const ObjectType& JSONObject::type() const {
	return objType;
}

Size_T JSONObject::size() const {
	return properties.size();
}

String JSONObject::getObjectString() const {
	String objStr;
	if (objType == ObjectType::obj) {
		objStr += "{";
	}
	if (objType == ObjectType::arr) {
		objStr += "[";
	}
	for (Size_T i = 0; i < properties.size(); i++) {
		if (properties[i]->getValue() != "") {
			if (properties[i]->getKey() != "") {
				objStr += properties[i]->getKey() + ':' + properties[i]->getValue();
			}
			else {
				objStr += properties[i]->getValue();
			}
			if (i != properties.size() - 1) {
				objStr += ',';
			}
		}
		else {
			//no value
			if (properties[i]->getChild() != nullptr) {
				if (properties[i]->getKey() != "") {
					objStr += properties[i]->getKey() + ':' + properties[i]->getChild()->getObjectString();
				}
				else {
					//ghost property
					objStr += properties[i]->getChild()->getObjectString();
				}
			}
			else {
				objStr += properties[i]->getKey() + ':' + "\"\"";
			}
			if (i != properties.size() - 1) {
				objStr += ',';
			}
		}
	}


	if (objType == ObjectType::obj) {
		objStr += "}";
	}
	if (objType == ObjectType::arr) {
		objStr += "]";
	}
	return objStr;
}

String JSONObject::getPrettyObjectString() const {
	String objStr = getObjectString();
	String prettyStr = formatPretty(objStr);
	return prettyStr;
}

void JSONObject::addProperty(JSONProperty* prop) {
	properties.push_back(prop);
}

void JSONObject::removeProperty(JSONProperty* prop) {
	for (Size_T i = 0; i < properties.size(); i++) {
		if (properties[i] == prop) {
			properties[i] = properties[size() - 1];
			if (prop->getChild() != nullptr) {
				prop->getChild()->clear();
				delete prop->getChild();
			}
			delete prop;
			properties.pop_back();
			break;
		}
	}
}

void JSONObject::clear() {
	for (Size_T i = 0; i < properties.size(); i++) {
		if (properties[i]->getChild() != nullptr) {
			properties[i]->getChild()->clear();
			delete properties[i]->getChild();
		}
		delete properties[i];
	}
	properties.clear();
}

JSONProperty* JSONObject::operator[](Size_T pos) {
	if (pos >= properties.size()) {
		throw std::out_of_range("Out of range");
	}
	return properties[pos];
}