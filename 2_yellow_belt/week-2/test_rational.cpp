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

// class Rational {
//    public:
//     Rational() {
//         p = 0;
//         q = 1;
//     }

//     Rational(int numerator, int denominator) {
//         int t = abs(gcd(numerator, denominator));
//         if (denominator < 0) {
//             t = -t;
//         }
//         p = numerator / t;
//         q = denominator / t;
//     }

//     int Numerator() const {
//         return p;
//     }

//     int Denominator() const {
//         return q;
//     }

//    private:
//     int gcd(int x, int y) const {
//         while (x) {
//             y %= x;
//             swap(y, x);
//         }
//         return y;
//     }
//     int p, q;
// };

void AssertRat(Rational& r, int x, int y) {
    AssertEqual(r.Numerator(), x);
    AssertEqual(r.Denominator(), y);
}

void TestDefault() {
    Rational r;
    AssertRat(r, 0, 1);
}

void TestReduction() {
    Rational r(3, 9);
    AssertRat(r, 1, 3);
    r = {-3, 9};
    AssertRat(r, -1, 3);
    r = {3, -9};
    AssertRat(r, -1, 3);
    r = {-3, -9};
    AssertRat(r, 1, 3);
    r = {0, 9};
    AssertRat(r, 0, 1);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefault, "TestDefault");
    runner.RunTest(TestReduction, "TestReduction");
    return 0;
}
