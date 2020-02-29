#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

template <typename kt, typename vt>
vt& GetRefStrict(map<kt, vt> &m, kt k) {
    if (m.count(k) == 0) throw runtime_error("");
    return m.at(k);
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;  // выведет newvalue
}