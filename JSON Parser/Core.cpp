#include <iostream>
#include <stdexcept>

#include "Core.h"
#include "CommandParser.h"


void Core::start() {
	CommandParser parser;
	std::string line;
	while (std::getline(std::cin, line)) {
		try {
			parser.parse(line);
			if (parser.isExit()) {
				//close json and save???
				return;
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			parser.resetConsole();
		}
	}
}
