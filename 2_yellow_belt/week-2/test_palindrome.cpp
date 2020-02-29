#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
   public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

   private:
    int fail_count = 0;
};

bool IsPalindrom(std::string s) {
    const int len = s.size();
    for (int i = 0; i < len/2; i++) {
        if (s[i] != s[len - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestEasy() {
    AssertEqual(IsPalindrom("hello"), false);
    AssertEqual(IsPalindrom("lolo"), false);
    AssertEqual(IsPalindrom("ababa"), true);
    AssertEqual(IsPalindrom("asdf  fdsa"), true);
    AssertEqual(IsPalindrom("so mbbm os"), true);
}

void TestExtreme() {
    AssertEqual(IsPalindrom(""), true);
    AssertEqual(IsPalindrom("l"), true);
    AssertEqual(IsPalindrom("ll"), true);
    AssertEqual(IsPalindrom("lll"), true);
    AssertEqual(IsPalindrom("l l"), true);
    AssertEqual(IsPalindrom("lll   "), false);
    AssertEqual(IsPalindrom("   lll"), false);
    AssertEqual(IsPalindrom("asdffdsa  "), false);
    AssertEqual(IsPalindrom("so mbbm ol"), false);
    AssertEqual(IsPalindrom("so mbvm os"), false);
    AssertEqual(IsPalindrom("so+ mbbm +os"), true);
    AssertEqual(IsPalindrom("so- mbbm -os"), true);
    AssertEqual(IsPalindrom("so& mbbm &os"), true);
    AssertEqual(IsPalindrom("so mbbv os"), false);
    AssertEqual(IsPalindrom("so mbklm os"), false);
    AssertEqual(IsPalindrom("so bbklm os"), false);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestEasy, "TestEasy");
    runner.RunTest(TestExtreme, "TestExtreme");
    return 0;
}
