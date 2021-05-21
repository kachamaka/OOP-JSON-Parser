#include <iostream>
#include <fstream>

#include "Helpers.h"
#include "JSONSearch.h"
#include "JSON.h"

void JSONSearch::searchObjectProperties(JSONObject* obj, const String& key) {
	if (obj == nullptr) {
		return;
	}
	for (Size_T i = 0; i < obj->size(); i++) {
		if ((*obj)[i]->getKey() == key) {
			searchedProperties.push_back((*obj)[i]);
		}
		else {
			searchObjectProperties((*obj)[i]->getChild(), key);
		}
	}
}

String JSONSearch::getSearchString() const {
	String objStr = "{";
	for (Size_T i = 0; i < searchedProperties.size(); i++) {
		objStr += searchedProperties[i]->getPropertyString();
		if (i != searchedProperties.size() - 1) {
			objStr += ',';
		}
	}
	objStr += '}';
	return objStr;
}

String JSONSearch::getPrettySearchString() const {
	String objStr = getSearchString();
	return formatPretty(objStr);
}

void JSONSearch::search(const String& key) {
	searchedProperties.clear();
	JSONObject* mainJSON = JSON::Get().getJSON();
	String quotedKey = "\"" + key + "\"";
	searchObjectProperties(mainJSON, quotedKey);
}

void JSONSearch::print() const {
	std::cout << "{\n";
	for (Size_T i = 0; i < searchedProperties.size(); i++) {
		std::cout << searchedProperties[i]->getPropertyString();

		if (i != searchedProperties.size() - 1) {
			std::cout << ",";
		}
		std::cout << "\n";
	}
	std::cout << "}\n";
}

void JSONSearch::print(Size_T pos) const {
	if (pos >= searchedProperties.size()) {
		throw std::out_of_range("Out of range");
	}
	std::cout << searchedProperties[pos]->getPropertyString();

	std::cout << "\n";
}

void JSONSearch::save(const String& path) const {
	std::ofstream file(path);
	if (!file) {
		throw std::invalid_argument("Couldn't open file");
	}
	String data = getPrettySearchString();
	file << data;
	file.close();
}

void JSONSearch::save(Size_T pos, const String& path) const {
	std::ofstream file(path);
	if (!file) {
		throw std::invalid_argument("Couldn't open file");
	}
	String data = "{" + searchedProperties[pos]->getPropertyString() + "}";
	file << data;
	file.close();
}

Size_T JSONSearch::size() const {
	return searchedProperties.size();
}