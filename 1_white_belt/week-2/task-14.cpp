#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
    set<string> sett;
    for (const auto& [key, value] : m) {
        sett.insert(value);
    }
    return sett;
}