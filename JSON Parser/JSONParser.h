#pragma once

#include "Helpers.h"
#include "JSONStructure.h"

class JSONParser {
	JSONStructure jsonRawData;

	String loadedFile;

	bool loaded = false;
	bool changes = false;
	bool saved = false;

	JSONParser() {};
	~JSONParser() {};

	void checkLoaded() const;
	void clearData();
public:
	static JSONParser& Get() {
		static JSONParser JSON;
		return JSON;
	}

	JSONParser(const JSONParser&) = delete;
	JSONParser& operator=(const JSONParser&) = delete;

	void constructJSON() const;

	void open(const String& path);
	void newFile();
	void close();
	void save(bool prettyPrint = true);
	void saveas(const String& path, bool prettyPrint = true);
	void print(bool prettyPrint = true);
	//void validate();

	//search cmds
	void search(const String& key) const;
	void printSearch() const;
	void printSearch(Size_T pos) const;
	void saveSearch(const String& path) const;
	void saveSearch(Size_T pos, const String& path) const;

	//set cmds
	void set(const String& key, Pair<ValueType, String> value);

	//create cmd
	void create(const String& key, Pair<ValueType, String> value);

	//remove cmd
	void remove(const String& key);

	//move cmd
	void move(const String& key1, const String& key2);
};