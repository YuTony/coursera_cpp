#include "stats.h"

#include <iostream>
#include <sstream>
using namespace std;

const string Stats::UNKNOWN_METHOD = "UNKNOWN";
const string Stats::UNKNOWN_URI = "unknown";

const vector<string> Stats::available_methods = { "GET", "POST", "PUT", "DELETE" };
const vector<string> Stats::available_uris = { "/", "/order", "/product", "/basket", "/help" };

Stats::Stats() {
	for (const string& available_method : available_methods) {
		methods_count[available_method] = 0;
	}
	methods_count[UNKNOWN_METHOD] = 0;

	for (const string& available_uri : available_uris) {
		uri_count[available_uri] = 0;
	}
	uri_count[UNKNOWN_URI] = 0;
}

void Stats::AddMethod(string_view method) {
	string method_name(method);
	
	bool found = false;
	for (const string& available_method : available_methods) {
		if (method_name == available_method) {
			method = available_method;
			found = true;
			break;
		}
	}
	if (!found) {
		method = UNKNOWN_METHOD;
	}

	methods_count[method]++;
}

void Stats::AddUri(string_view uri) {
	string uri_str(uri);

	bool found = false;
	for (const string& available_uri : available_uris) {
		if (uri_str == available_uri) {
			uri = available_uri;
			found = true;
			break;
		}
	}
	if (!found) {
		uri = UNKNOWN_URI;
	}

	uri_count[uri]++;
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methods_count;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_count;
}

HttpRequest ParseRequest(string_view line) {
	if (line[0] == ' ') {
		size_t cur = 0;
		while ((cur != line.npos) && (line[cur] == ' ')) cur++;
		if (cur != line.npos) line.remove_prefix(cur);
	}

	size_t space = line.find(' ');
	string_view method = line.substr(0, space);
	while ((space != line.npos) && (line[space] == ' ')) space++;
	if (space != line.npos) line.remove_prefix(space);

	space = line.find(' ');
	string_view uri = line.substr(0, space);
	while ((space != line.npos) && (line[space] == ' ')) space++;
	if (space != line.npos) line.remove_prefix(space);

	space = line.find(' ');
	string_view protocol = line.substr(0, space);

	return { method, uri, protocol };
}
