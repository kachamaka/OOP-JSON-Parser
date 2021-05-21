#include <iostream>
#include <stdexcept>

#include "../JSON Parser/JSONSearch.h"
#include "../JSON Parser/JSON.h"

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
JSONSearch& jsonSearch = JSONSearch::Get();

String raw = "{\"testProperty\":\"something\",\"Owner\":\"kachamaka\",\"ID\":1,\"value\":\"myValue\",\"nested\":{\"value\":42}}";

TEST_CASE(testJSONSearch) {
	try {
		json.construct(raw);
		jsonSearch.search("testProperty");
		if (jsonSearch.getSearchString() != "{\"testProperty\":\"something\"}") {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONSearchWithMultipleInstances) {
	try {
		json.construct(raw);
		jsonSearch.search("value");
		if (jsonSearch.getSearchString() != "{\"value\":\"myValue\",\"value\":42}") {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

TEST_CASE(testJSONSearchWithInvalidProperty) {
	try {
		json.construct(raw);
		jsonSearch.search("aaaaaa");
		if (jsonSearch.getSearchString() != "{}") {
			hasError = true;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}