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

void constructObject(const String& raw) {
	try {
		JSONObject obj(raw);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONObjectConstructorWithObject) {
	constructObject(raw);
}
TEST_CASE(testJSONObjectConstructorWithArray) {
	constructObject(rawArr);
}
TEST_CASE(testJSONObjectConstructorWithNonObject) {
	constructObject("val?");
}

TEST_CASE(testJSONObjectGetTypeObj) {
	try {
		JSONObject obj(raw);
		if (obj.type() != ObjectType::obj) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONObjectGetTypeArr) {
	try {
		JSONObject obj(rawArr);
		if (obj.type() != ObjectType::arr) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONObjectSize) {
	try {
		JSONObject obj(raw);
		if (obj.size() != 4) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONObjectGetObjectString) {
	try {
		JSONObject obj(raw);
		if (obj.getObjectString() != raw) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

JSONObject* obj = new JSONObject;
TEST_CASE(testJSONObjectAddProperty) {
	try {
		obj->addProperty(new JSONProperty("testProp", "testVal"));
		if ((*obj)[0]->getKey() != "testProp" || (*obj)[0]->getValue() != "testVal") {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}
TEST_CASE(testJSONObjectRemoveProperty) {
	try {
		obj->removeProperty((*obj)[0]);
		if (obj->size() != 0) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONObjectClear) {
	try {
		JSONObject obj(raw);
		obj.clear();
		if (obj.size() != 0) {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONObjectOperatorAt) {
	try {
		JSONObject obj(raw);
		if (obj[0]->getKey() != "\"prop\"" || obj[0]->getValue() != "42") {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}