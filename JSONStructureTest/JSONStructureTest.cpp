#include <iostream>
#include <stdexcept>

#include "../JSON Parser/JSONStructure.h"
#include "../JSON Parser/JSONObject.h"
#include "../JSON Parser/Exceptions.h"

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

String raw = "{\"ID\":\"042\",\"version\":1,\"changes\":false,\"developer\":\"kachamaka\",\"secret key\":42}";

bool validateJSONStructure(const String& raw) {
	try {
		JSONStructure json(raw);
		json.validate();
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		return false;
	}
	return true;
}
TEST_CASE(testJSONStructureValidateValid) {
	String raw = "{\"ID\":\"042\",\"version\":1,\"changes\":false,\"developer\":\"kachamaka\",\"secret key\":42}";
	if (!validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateValidWithRandomQuotes) {
	String raw = "{\"p\"r aand osome \"text\" dadwd op\":\"val\",\"id\":42}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateInvalidWithDoubleComma) {
	String raw = "{\"prop\":\"val\",,\"id\":42}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateInvalidWithDoubleOpenningBraces) {
	String raw = "{{\"prop\":\"val\",\"id\":42}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateInvalidWithDoubleObject) {
	String raw = "{{\"prop\":\"val\",\"id\":42,{{}}}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateInvalidWithUnbalancedBraces) {
	String raw = "{{\"prop\":\"val\",\"id\":42,{{}}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateInvalidWithInvalidPropertyValue) {
	String raw = "{{\"prop\":\"val\",\"id\":4\"2}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}
TEST_CASE(testJSONStructureValidateInvalidWithBadStructure) {
	String raw = "{{\"prop\":\"val\",}\"id\":42}";
	if (validateJSONStructure(raw)) {
		hasError = true;
	}
}