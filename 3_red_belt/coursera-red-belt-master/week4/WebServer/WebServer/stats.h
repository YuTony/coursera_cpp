#pragma once

#include "http_request.h"

#include <string_view>
#include <vector>
#include <map>
using namespace std;

class Stats {
public:
	Stats();
	void AddMethod(string_view method);
	void AddUri(string_view uri);
	const map<string_view, int>& GetMethodStats() const;
	const map<string_view, int>& GetUriStats() const;

private:
	static const string UNKNOWN_METHOD;
	static const string UNKNOWN_URI;

	static const vector<string> available_methods, available_uris;

	map<string_view, int> methods_count, uri_count;
};

HttpRequest ParseRequest(string_view line);
