#include "JSON.h"

#include <iostream>
#include <fstream>

#include "Helpers.h"
#include "Exceptions.h"
#include "JSONStructure.h"
#include "JSONProperty.h"

JSON::JSON() {

}

JSON::~JSON() {
	clear();
}

void JSON::clear() {
	if (jsonObj != nullptr) {
		jsonObj->clear();
		delete jsonObj;
	}

	//maybe unneccessary
	jsonObj = nullptr;
}

void JSON::construct(const String& raw) {
	JSONObject* startingObj = new JSONObject(raw);
	jsonObj = startingObj;
}

void JSON::print(bool prettyPrint) const {
	if (!prettyPrint) {
		std::cout << jsonObj->getObjectString() << "\n";
	}
	else {
		std::cout << jsonObj->getPrettyObjectString() << "\n";
	}
}

void JSON::save(const String& path, bool prettyPrint) const {
	checkPathExtension(path);

	std::ofstream file(path);
	if (!file) {
		throw std::invalid_argument("Couldn't open file");
	}

	String data;
	if (prettyPrint) {
		data = jsonObj->getPrettyObjectString();
	}
	else {
		data = jsonObj->getObjectString();
	}

	file << data;
	file.close();
}

void JSON::set(const String& key, Pair<ValueType, String> value) const {

	//value parsing and checks
	parseValue(value);

	Vector<Pair<String, String>> keys;
	parseKeys(key, keys);

	JSONObject* currentObj = jsonObj;
	JSONProperty* currentProp = nullptr;

	getPropertyFromKeyPath(keys, currentProp, currentObj);

	if (currentProp == nullptr) {
		throw invalidPathToKey;
	}
	else {
		//std::cout << currentProp->getKey() << "<->" << currentProp->getValue() << "\n";
		if (value.first == ValueType::obj || value.first == ValueType::arr) {
			JSONObject* newObj = new JSONObject(value.second);
			currentProp->setValue("");
			if (currentProp->getChild() != nullptr) {
				currentProp->deleteChild();
			}
			currentProp->setChild(newObj);
		}
		else {
			currentProp->setValue(value.second);
		}
	}
}

void JSON::create(const String& key, Pair<ValueType, String> value) const {
	//value parsing and checks
	parseValue(value);

	Vector<Pair<String, String>> keys;
	parseKeys(key, keys);

	JSONObject* currentObj = jsonObj;

	createProperty(keys, value, currentObj);
}

void JSON::remove(const String& key) const {

	Vector<Pair<String, String>> keys;
	parseKeys(key, keys);

	JSONObject* currentObj = jsonObj;
	JSONProperty* currentProp = nullptr;

	getPropertyFromKeyPath(keys, currentProp, currentObj);

	if (currentProp == nullptr) {
		throw invalidPathToKey;
	}
	else {
		currentObj->removeProperty(currentProp);
	}
}

void JSON::move(const String& key1, const String& key2) const {

	Vector<Pair<String, String>> keys1;
	parseKeys(key1, keys1);
	JSONObject* obj1 = jsonObj;
	JSONProperty* prop1 = nullptr;
	getPropertyFromKeyPath(keys1, prop1, obj1);


	Vector<Pair<String, String>> keys2;
	parseKeys(key2, keys2);
	JSONObject* obj2 = jsonObj;
	JSONProperty* prop2 = nullptr;
	getPropertyFromKeyPath(keys2, prop2, obj2);

	if (prop1 == nullptr || prop2 == nullptr) {
		throw invalidPathToKey;
	}
	else {
		moveProperty(prop1, prop2);
	}
}

JSONObject* JSON::getJSON() const {
	return jsonObj;
}

void JSON::checkPathExtension(const String& path) {
	if (path.substr(path.find_last_of(".") + 1) != "json") {
		throw std::invalid_argument("Couldn't save file. Extension mismatch...");
	}
}

void JSON::parseValue(Pair<ValueType, String>& value) {
	if (value.first == ValueType::obj || value.first == ValueType::arr) {
		String val = value.second;
		parseLine(val);
		escapeChars(val);
		JSONStructure rawJSON(val);
		bool isObject = true;
		try {
			JSONObject obj(rawJSON.get());
		}
		catch (...) {
			isObject = false;
			value.first = ValueType::string;
		}
		if (isObject) {
			try {
				rawJSON.validate();
			}
			catch (...) {
				throw std::invalid_argument("Please enter valid object");
			}
		}
	}
	if (value.first == ValueType::string) {
		if (value.second[0] != '\"' || value.second[value.second.size() - 1] != '\"') {
			value.second = '\"' + value.second + '\"';
		}
	}

}

void JSON::parseKeys(const String& key, Vector<Pair<String, String>>& keys) {
	std::size_t start = 2;
	for (std::size_t i = 2; i < key.size(); i++) {
		std::size_t dotPos = getNextDotPosInKeyPath(key, i);
		String keyOfProperty;
		if (dotPos == String::npos) {
			keyOfProperty = key.substr(start);
		}
		else {
			keyOfProperty = key.substr(start, dotPos - start);
		}

		Pair<String, String> keyWithArrayIndex;
		if (keyOfProperty[keyOfProperty.size() - 1] == ']') {
			std::size_t middle = getArrayStartIndexFromStringKey(keyOfProperty);
			keyWithArrayIndex = std::make_pair(keyOfProperty.substr(0, middle), keyOfProperty.substr(middle));
		}
		else {
			keyWithArrayIndex = std::make_pair(keyOfProperty, "");
		}

		if (keyWithArrayIndex.first[0] != '\"' && keyWithArrayIndex.first[keyWithArrayIndex.first.size() - 1] != '\"') {
			keyWithArrayIndex.first = '\"' + keyWithArrayIndex.first + '\"';
		}

		keys.push_back(keyWithArrayIndex);

		if (dotPos == String::npos) {
			break;
		}
		i = dotPos;
		start = i + 1;
	}
}

void JSON::getPropertyFromKeyPath(const Vector<Pair<String, String>>& keys, JSONProperty*& currentProp, JSONObject*& currentObj) {
	for (std::size_t i = 0; i < keys.size(); i++) {
		bool found = false;
		for (std::size_t j = 0; j < currentObj->size(); j++) {
			//loop properties
			JSONProperty* prop = (*currentObj)[j];
			if (keys[i].first == prop->getKey()) {
				//match
				found = true;

				if (keys[i].second == "") {
					//if no array index
					if (i == keys.size() - 1) {
						currentProp = prop;
					}
					else {
						if (prop->getChild() != nullptr) {
							currentObj = prop->getChild();
						}
						else {
							throw invalidPathToKey;
						}
					}
				}
				else {
					if (prop->getChild() != nullptr) {
						if (prop->getChild()->type() == ObjectType::arr) {
							std::size_t pos = std::stoi(keys[i].second.substr(1, keys[i].second.size() - 1));
							currentObj = prop->getChild();
							if (i == keys.size() - 1) {
								currentProp = (*currentObj)[pos];
							}
							else {
								if ((*currentObj)[pos]->getChild() != nullptr) {
									currentObj = (*currentObj)[pos]->getChild();
								}
								else {
									throw invalidPathToKey;
								}
							}
						}
						else {
							throw invalidPathToKey;
						}
					}
					else {
						throw invalidPathToKey;
					}
				}
				break;
			}
		}
		if (!found) {
			throw invalidPathToKey;
		}
	}
}

void JSON::createProperty(const Vector<Pair<String, String>>& keys, const Pair<ValueType, String>& value, JSONObject*& currentObj) {
	for (std::size_t i = 0; i < keys.size(); i++) {
		bool found = false;
		for (std::size_t j = 0; j < currentObj->size(); j++) {
			JSONProperty* prop = (*currentObj)[j];
			if (keys[i].first == prop->getKey()) {
				found = true;
				//match
				if (keys[i].second == "") {
					if (i == keys.size() - 1) {
						throw pathToKeyExists;
					}
					else {
						if (prop->getChild() != nullptr) {
							currentObj = prop->getChild();
						}
						else {
							throw invalidPathToKey;
						}
					}
				}
				else {
					if (prop->getChild() != nullptr) {
						if (prop->getChild()->type() == ObjectType::arr) {
							std::size_t pos = std::stoi(keys[i].second.substr(1, keys[i].second.size() - 1));
							currentObj = prop->getChild();
							if (i == keys.size() - 1) {
								if (pos < currentObj->size()) {
									throw pathToKeyExists;
								}
								else if (pos == currentObj->size()) {
									JSONProperty* newProp = new JSONProperty("", "");
									if (value.first == ValueType::obj || value.first == ValueType::arr) {
										JSONObject* newObj = new JSONObject(value.second);
										newProp->setChild(newObj);
									}
									else {
										newProp->setValue(value.second);
									}
									currentObj->addProperty(newProp);
									//std::cout << newProp->getKey() << " " << newProp->getValue() << " ??\n";
									return;
								}
								else {
									throw invalidPathToKey;
								}
							}
							else {
								if ((*currentObj)[pos]->getChild() != nullptr) {
									currentObj = (*currentObj)[pos]->getChild();
								}
								else {
									throw invalidPathToKey;
								}
							}
						}
						else {
							throw invalidPathToKey;
						}
					}
					else {
						throw invalidPathToKey;
					}
				}
				break;
			}
		}

		if (!found) {
			JSONProperty* newProp = new JSONProperty(keys[i].first, "");
			currentObj->addProperty(newProp);

			if (i == keys.size() - 1) {
				if (value.first == ValueType::obj || value.first == ValueType::arr) {
					JSONObject* newObj = new JSONObject(value.second);
					newProp->setChild(newObj);
				}
				else {
					newProp->setValue(value.second);
				}
			}
			else {
				JSONObject* newObj = new JSONObject("{}");
				newProp->setChild(newObj);
				currentObj = newObj;
			}

		}
	}
}

void JSON::moveProperty(JSONProperty*& prop1, JSONProperty*& prop2) {
	if (prop2->getChild() != nullptr) {
		if (prop1->getChild() != nullptr) {
			prop2->getChild()->clear();
			prop2->deleteChild();

			JSONObject* newChild = new JSONObject(prop1->getChild()->getObjectString());
			prop2->setChild(newChild);
		}
		else {
			prop2->getChild()->clear();
			prop2->deleteChild();

			prop2->setValue(prop1->getValue());
		}
	}
	else {
		if (prop1->getChild() != nullptr) {
			prop2->setValue("");

			JSONObject* newChild = new JSONObject(prop1->getChild()->getObjectString());
			prop2->setChild(newChild);
		}
		else {
			prop2->setValue(prop1->getValue());
		}
	}
}
