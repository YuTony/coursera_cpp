#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& s);

template <class T>
ostream& operator<<(ostream& os, const set<T>& s);

template <class K, class V>
ostream& operator<<(ostream& os, const map<K, V>& m);

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {});

void Assert(bool b, const string& hint);

class TestRunner {
   public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name);

    ~TestRunner();

   private:
    int fail_count = 0;
};