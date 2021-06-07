#pragma once

#include <stdexcept>

///@brief customized exception directives

#define invalidInput \
std::invalid_argument("Please enter valid input...");

#define invalidCommand \
std::invalid_argument("Please enter a valid command... Type \"?\" for more info");

#define invalidPathToKey \
std::invalid_argument("Invalid path to key...");

#define pathToKeyExists \
std::invalid_argument("Path to key already exists...");