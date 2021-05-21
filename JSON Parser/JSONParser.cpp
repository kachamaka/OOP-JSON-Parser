#include <fstream>

#include <iostream>

#include "Helpers.h"
#include "JSONParser.h"

#include "JSONSearch.h"
#include "JSON.h"

JSON& json = JSON::Get();
JSONSearch& jsonSearch = JSONSearch::Get();

void JSONParser::checkLoaded() const {
	if (!loaded) {
		throw std::invalid_argument("There is still no file loaded...");
	}
}

void JSONParser::clearData() {
	jsonRawData.clear();
	saved = false;
	changes = false;
	loaded = false;
	loadedFile = "";
	json.clear();
}

void JSONParser::constructJSON() const {
	json.construct(jsonRawData.get());
}

void JSONParser::open(const String& path) {
	if (loaded) {
		close();
	}

	if (path.substr(path.find_last_of(".") + 1) != "json") {
		throw std::invalid_argument("Couldn't open file. Extension mismatch...");
	}

	std::ifstream file;
	file.open(path);
	if (file.fail()) {
		throw std::invalid_argument("Error opening file...");
	}
	String buffer;
	while (std::getline(file, buffer)) {
		parseLine(buffer);
		jsonRawData.addLine(buffer);
	}
	file.close();
	loaded = true;
	validate();

	constructJSON();

	loadedFile = path.substr(path.find_last_of("\\/") + 1);

	std::cout << "File successfully opened!\n";	
}

void JSONParser::newFile() {
	json.clear();
	jsonRawData.clear();
	json.construct("{}");
	loaded = true;
	std::cout << "New file created!\n";
}

void JSONParser::close() {
	checkLoaded();
	if (changes && !saved) {
		std::cout << "Unsaved changes... Save and quit? [Y/n/abort] ";
		String confirm;
		std::getline(std::cin, confirm);
		confirm = toLower(confirm);
		if (confirm == "y" || confirm == "yes") {
			if (loadedFile == "") {
				std::cout << "Please enter new file path... \n";
				String path;
				std::getline(std::cin, path);
				saveas(path, 1);
			}
			else {
				save(1);
			}
		}
		else if (confirm == "n" || confirm == "no") {
			clearData();
		}
		else {
			throw std::invalid_argument("Aborting...");
		}
	}
	else {
		clearData();
	}
	std::cout << "File successfully closed!\n";
}

void JSONParser::save(bool prettyPrint) {
	checkLoaded();
	if (loadedFile == "") {
		throw std::invalid_argument("File has no current file path...");
	}
	//save json
	json.save(loadedFile, prettyPrint);
	saved = true;
	std::cout << "File save successfully!\n";
}

void JSONParser::saveas(const String& path, bool prettyPrint) {
	checkLoaded();
	json.save(path, prettyPrint);
	loadedFile = path;
	saved = true;
	std::cout << "File save successfully!\n";
}

void JSONParser::print(bool prettyPrint) {
	checkLoaded();
	json.print(prettyPrint);
}

void JSONParser::validate() {
	checkLoaded();

	try {
		jsonRawData.validate();
	}
	catch (...) {
		clearData();
		throw;
	}
	//std::cout << "Valid JSON!\n";
}

void JSONParser::search(const String& key) const {
	checkLoaded();
	jsonSearch.search(key);
	if (jsonSearch.size() == 0) {
		std::cout << "No such keys found...\n";
	}
	else {
		std::cout << "Keys found!\n";
	}
	
}

void JSONParser::printSearch() const {
	checkLoaded();
	jsonSearch.print();
}

void JSONParser::printSearch(Size_T pos) const {
	checkLoaded();
	jsonSearch.print(pos);
}

void JSONParser::saveSearch(const String& path) const {
	checkLoaded();
	jsonSearch.save(path);
	std::cout << "Search results saved successfully!\n";
}

void JSONParser::saveSearch(Size_T pos, const String& path) const {
	checkLoaded();
	jsonSearch.save(pos, path);
	std::cout << "Search results saved successfully!\n";
}

void JSONParser::set(const String& key, Pair<ValueType, String> value) {
	checkLoaded();
	json.set(key, value);
	changes = true;
	std::cout << "Property set successfully!\n";
}

void JSONParser::create(const String& key, Pair<ValueType, String> value) {
	checkLoaded();
	json.create(key, value);
	changes = true;
	std::cout << "Property created successfully!\n";
}

void JSONParser::remove(const String& key) {
	checkLoaded();
	json.remove(key);
	changes = true;
	std::cout << "Property removed successfully!\n";
}

void JSONParser::move(const String& key1, const String& key2) {
	checkLoaded();
	json.move(key1, key2);
	changes = true;
	std::cout << "Property moved successfully!\n";
}