#include <iostream>
#include <stdexcept>

#include "../JSON Parser/JSON.h"
#include "../JSON Parser/JSONProperty.h"

using TestFunction = void(*)();

bool hasError = false;

bool runTest(TestFunction pfn, const char* name) {
	std::cout << "Running test \"" << name << "\"... ";

	hasError = false;
	pfn();

	std::cout << (hasError ? " ERROR\n" : " OK\n");

	return hasError;
}

int main() {

}

#define TEST_CASE(name) \
void name(); \
bool testvar_##name = runTest(name, #name); \
void name()

//--------------------------------------------------
//test functions

JSON& json = JSON::Get();
String raw = "{\"testProperty\":42,\"Owner\":\"kachamaka\",\"myArr\":[],\"myObj\":{}}";

TEST_CASE(testJSONConstruct) {
	try {
		json.construct(raw);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONGet) {
	try {
		JSONObject* obj = json.getJSON();
		if (obj->getObjectString() != raw) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

void createProperty(const String& key, const Pair<ValueType, String>& val) {
	try {
		json.create(key, val);
		JSONProperty* lastProp = (*json.getJSON())[json.getJSON()->size() - 1];
		if (val.first == ValueType::string) {
			if (lastProp->getValue() != ('\"' + val.second + '\"')) {
				hasError = true;
			}
		}
		else {
			if (val.first == ValueType::obj || val.first == ValueType::arr) {
				if (lastProp->getChild()->getObjectString() != val.second) {
					hasError = true;
				}
			}
			else {
				if (lastProp->getValue() != val.second) {
					hasError = true;
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONCreateString) {
	Pair<ValueType, String> val = std::make_pair(ValueType::string, "ivan");
	createProperty("$.testProperty1", val);
}
TEST_CASE(testJSONCreateInt) {
	Pair<ValueType, String> val = std::make_pair(ValueType::integer, "42");
	createProperty("$.testProperty2", val);
}
TEST_CASE(testJSONCreateDouble) {
	Pair<ValueType, String> val = std::make_pair(ValueType::integer, "42.0");
	createProperty("$.testProperty3", val);
}
TEST_CASE(testJSONCreateBool) {
	Pair<ValueType, String> val = std::make_pair(ValueType::boolean, "false");
	createProperty("$.testProperty4", val);
}
TEST_CASE(testJSONCreateNull) {
	Pair<ValueType, String> val = std::make_pair(ValueType::null, "null");
	createProperty("$.testProperty5", val);
}
TEST_CASE(testJSONCreateEmptyObject) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "{}");
	createProperty("$.testProperty6", val);
}
TEST_CASE(testJSONCreateInvalidObject) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "{,}");
	createProperty("$.testProperty7", val);
}
TEST_CASE(testJSONCreateObject) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "{\"id\":42}");
	createProperty("$.testProperty8", val);
}
TEST_CASE(testJSONCreateEmptyArray) {
	Pair<ValueType, String> val = std::make_pair(ValueType::arr, "[]");
	createProperty("$.testProperty9", val);
}
TEST_CASE(testJSONCreateInvalidArray) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "[,]");
	createProperty("$.testProperty10", val);
}
TEST_CASE(testJSONCreateArray) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "[\"pesho\", 42]");
	createProperty("$.testProperty11", val);
}

void clearJSON() {
	try {
		json.clear();
		if (json.getJSON() != nullptr) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	json.construct(raw);
}
TEST_CASE(testJSONClear) {
	clearJSON();
}

void setProperty(const String& key, const Pair<ValueType, String>& val) {
	try {
		json.set(key, val);
		JSONProperty* prop = (*json.getJSON())[0];

		if (val.first == ValueType::string) {
			if (prop->getValue() != ('\"' + val.second + '\"')) {
				hasError = true;
			}
		}
		else {
			if (val.first == ValueType::obj || val.first == ValueType::arr) {
				if (prop->getChild()->getObjectString() != val.second) {
					hasError = true;
				}
			}
			else {
				if (prop->getValue() != val.second) {
					hasError = true;
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONSetString) {
	Pair<ValueType, String> val = std::make_pair(ValueType::string, "test?");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetInt) {
	Pair<ValueType, String> val = std::make_pair(ValueType::integer, "16");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetDouble) {
	Pair<ValueType, String> val = std::make_pair(ValueType::doubl, "16.0");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetBool) {
	Pair<ValueType, String> val = std::make_pair(ValueType::boolean, "true");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetNull) {
	Pair<ValueType, String> val = std::make_pair(ValueType::null, "null");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetEmptyObject) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "{}");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetInvalidObject) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "{,}");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetObject) {
	Pair<ValueType, String> val = std::make_pair(ValueType::obj, "{\"myProp\":\"invalid?\"}");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetEmptyArray) {
	Pair<ValueType, String> val = std::make_pair(ValueType::arr, "[]");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetInvalidArray) {
	Pair<ValueType, String> val = std::make_pair(ValueType::arr, "[,]");
	setProperty("$.testProperty", val);
}
TEST_CASE(testJSONSetArray) {
	Pair<ValueType, String> val = std::make_pair(ValueType::arr, "[1,\"a\"]");
	setProperty("$.testProperty", val);
}

void removeProperty(const String& key) {
	try {
		json.remove(key);
		JSONProperty* lastProp = (*json.getJSON())[json.getJSON()->size() - 1];
		if (lastProp->getKey() == '\"' + key + '\"') {
			hasError = true;
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONRemoveInvalid) {
	removeProperty("$.nonExistentProperty");
}
TEST_CASE(testJSONRemove) {
	removeProperty("$.myObj");
}

TEST_CASE(testJSONMove) {
	try {
		json.move("$.testProperty", "$.myArr");
		JSONProperty* lastProp = (*json.getJSON())[json.getJSON()->size() - 1];
		if (lastProp->getChild()->getObjectString() != (*json.getJSON())[0]->getChild()->getObjectString()) {
			hasError = true;
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
