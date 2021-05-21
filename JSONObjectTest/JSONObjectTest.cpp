#include <iostream>
#include <stdexcept>

using TestFunction = void(*)();

bool hasError = false;

bool runTest(TestFunction pfn, const char* name) {
	std::cout << "Running test \"" << name << "\"... ";

	hasError = false;
	pfn();

	std::cout << (hasError ? " ERROR\n" : " OK\n");

	return hasError;
}

int main()
{

}

#define TEST_CASE(name) \
void name(); \
bool testvar_##name = runTest(name, #name); \
void name()

//--------------------------------------------------
//test functions
