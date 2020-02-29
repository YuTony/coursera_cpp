#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

#define ASSERT_EQUAL(x, y) {            \
  ostringstream os;                     \
  os << #x << " != " << #y << ", "      \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, os.str());          \
}

#define ASSERT(x) {                     \
  ostringstream os;                     \
  os << #x << " is false, "             \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, os.str());                  \
}

#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func)

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& s);

template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::map<K, V>& m);

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint);

void Assert(bool b, const std::string& hint);

class TestRunner {
public:
	template <typename TestFunc>
	void RunTest(TestFunc func, const std::string& test_name);

	~TestRunner();

private:
	int fail_count = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
	out << "{";
	bool first = true;
	for (const auto& x : v) {
		if (!first) {
			out << ", ";
		}
		first = false;
		out << x;
	}
	return out << "}";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& s) {
	out << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			out << ", ";
		}
		first = false;
		out << x;
	}
	return out << "}";
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::map<K, V>& m) {
	out << "{";
	bool first = true;
	for (const auto& item : m) {
		if (!first) {
			out << ", ";
		}
		first = false;
		out << item.first << ": " << item.second;
	}
	return out << "}";
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
	if (!(t == u)) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

template <typename TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string& test_name) {
	try {
		func();
		std::cerr << test_name << " OK" << endl;
	}
	catch (const std::exception& ex) {
		++fail_count;
		std::cerr << test_name << " fail: " << ex.what() << endl;
	}
	catch (...) {
		++fail_count;
		std::cerr << "Unknown exception caught " << endl;
	}
}
