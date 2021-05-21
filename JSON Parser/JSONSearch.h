#pragma once

#include <cstddef>
#include <vector>
#include <string>

#include "JSONProperty.h"

class JSONSearch {
	Vector<JSONProperty*> searchedProperties;

	JSONSearch() {};

	void searchObjectProperties(JSONObject* obj, const String& key);
public:
	static JSONSearch& Get() {
		static JSONSearch jsonSearch_instance;
		return jsonSearch_instance;
	}

	JSONSearch(const JSONSearch&) = delete;
	JSONSearch& operator=(const JSONSearch&) = delete;

	String getSearchString() const;
	void search(const String& key);

	void print() const;
	void print(Size_T pos) const;

	void save(const String& path) const;
	void save(Size_T pos, const String& path) const;

	Size_T size() const;
};

