#pragma once

#include <ostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v);

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {});

void Assert(bool b, const string& hint);

class TestRunner {
   public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name);
    ~TestRunner();

   private:
    int fail_count = 0;
};