#include <iostream>
#include <stdexcept>

#include "../JSON Parser/JSONObject.h"
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


String raw = "{\"prop\":42,\"test\":\"okay\",\"ID\":[1,2,3],\"testObj\":{\"myProp\":\"OK\",\"value\":64}}";
String rawArr = "[\"val\",42, null]";

void constructProperty(const String& key, const String& value) {
	try {
		JSONProperty prop(key, value);
		if (prop.getKey() != key || prop.getValue() != value) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONPropertyConstructWithString) {
	String key = "propName";
	String value = "valName";
	constructProperty(key, value);
}
TEST_CASE(testJSONPropertyConstructWithInt) {
	String key = "propName";
	String value = "42";
	constructProperty(key, value);
}
TEST_CASE(testJSONPropertyConstructWithDouble) {
	String key = "propName";
	String value = "42.0";
	constructProperty(key, value);
}
TEST_CASE(testJSONPropertyConstructWithBool) {
	String key = "propName";
	String value = "false";
	constructProperty(key, value);
}
TEST_CASE(testJSONPropertyConstructWithNull) {
	String key = "propName";
	String value = "null";
	constructProperty(key, value);
}

TEST_CASE(testJSONPropertyGetPropertyString) {
	try {
		String key = "myKey";
		String val = "*insert something here*";
		JSONProperty prop(key, val);
		if (prop.getPropertyString() != key + ':' + val) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONPropertySetGetDeleteChild) {
	try {
		String key = "myKey";
		String val = "*insert something here*";
		JSONProperty prop(key, val);
		String raw = "{\"myObj\":42}";
		JSONObject* obj = new JSONObject(raw);
		prop.setChild(obj);

		if (prop.getChild()->getObjectString() != raw) {
			hasError = true;
		}
		prop.deleteChild();
		if (prop.getChild() != nullptr) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}