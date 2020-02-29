#include <algorithm>
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

struct NAME {
    int year;
    string name;
};

class Person {
   public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names.push_back({year, first_name});
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names.push_back({year, last_name});
    }
    string GetFullName(int year) {
        sort(begin(first_names), end(first_names), [](NAME x, NAME y) {
            return (x.year > y.year);
        });
        sort(begin(last_names), end(last_names), [](NAME x, NAME y) {
            return (x.year > y.year);
        });
        if ((first_names.size() > 0) && first_names[end(first_names) - begin(first_names) - 1].year <= year) {
            auto num_fn = find_if(begin(first_names), end(first_names), [&](NAME x) {
                return (x.year <= year);
            });
            if ((last_names.size() > 0) && (last_names[end(last_names) - begin(last_names) - 1].year <= year)) {
                auto num_ln = find_if(begin(last_names), end(last_names), [&](NAME x) {
                    return (x.year <= year);
                });
                return first_names[num_fn - begin(first_names)].name + ' ' + last_names[num_ln - begin(last_names)].name;
            } else {
                return first_names[num_fn - begin(first_names)].name + " with unknown last name";
            }
        } else {
            if ((last_names.size() > 0) && (last_names[end(last_names) - begin(last_names) - 1].year <= year)) {
                auto num_ln = find_if(begin(last_names), end(last_names), [&](NAME x) {
                    return (x.year <= year);
                });
                return last_names[num_ln - begin(last_names)].name + " with unknown first name";
            } else {
                return "Incognito";
            }
        }
    }

   private:
    vector<NAME> first_names, last_names;
};

void easy() {
    Person p;
    p.ChangeFirstName(1900, "abc");
    AssertEqual(p.GetFullName(1900), "abc with unknown last name");
    p.ChangeLastName(1899, "aba");
    AssertEqual(p.GetFullName(1898), "Incognito");
    AssertEqual(p.GetFullName(1899), "aba with unknown first name");
    AssertEqual(p.GetFullName(1900), "abc aba");
    AssertEqual(p.GetFullName(1901), "abc aba");
    p.ChangeLastName(1800, "aba1");
    AssertEqual(p.GetFullName(1890), "aba1 with unknown first name");
    p.ChangeFirstName(1905, "abc1");
    AssertEqual(p.GetFullName(1910), "abc1 aba");
}

int main() {
    TestRunner runner;
    runner.RunTest(easy, "test_easy");
    return 0;
}
