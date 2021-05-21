#pragma once

#include "JSONObject.h"
#include "Helpers.h"

class JSON {
	JSONObject* jsonObj = nullptr;

	JSON();
	~JSON();

	static void checkPathExtension(const String& path);
	static void parseValue(Pair<ValueType, String>& value);
	static void parseKeys(const String& key, Vector<Pair<String, String>>& keys);
	static void getPropertyFromKeyPath(const Vector<Pair<String, String>>& keys, JSONProperty*& currentProp, JSONObject*& currentObj);
	static void createProperty(const Vector<Pair<String, String>>& keys, const Pair<ValueType, String>& value, JSONObject*& currentObj);
	static void moveProperty(JSONProperty*& prop1, JSONProperty*& prop2);
public:
	static JSON& Get() {
		static JSON json_instance;
		return json_instance;
	}
	JSON(const JSON&) = delete;
	JSON& operator=(const JSON&) = delete;

	void construct(const String& raw);

	void print(bool prettyPrint = true) const;
	void save(const String& path, bool prettyPrint = true) const;

	void set(const String& key, Pair<ValueType, String> value) const;
	void create(const String& key, Pair<ValueType, String> value) const;
	void remove(const String& key) const;
	void move(const String& key1, const String& key2) const;

	void clear();

	JSONObject* getJSON() const;

};
