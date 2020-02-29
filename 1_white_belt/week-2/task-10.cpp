#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string com, s1, s2;
    map<string, string> m;
    for (int i = 0; i < n; i++) {
        cin >> com;
        if (com == "CHANGE_CAPITAL") {
            cin >> s1 >> s2;
            if (m.count(s1) != 0) {
                if (m[s1] == s2) {
                    cout << "Country " << s1
                         << " hasn't changed its capital" << endl;
                } else {
                    cout << "Country " << s1
                         << " has changed its capital from "
                         << m[s1] << " to "
                         << s2 << endl;
                    m[s1] = s2;
                }
            } else {
                cout << "Introduce new country " << s1
                     << " with capital " << s2 << endl;
                m[s1] = s2;
            }
        } else if (com == "RENAME") {
            cin >> s1 >> s2;
            /*if ((m.count(s1) == 1) && (s1 != s2)) {
                cout << "Country " << s1
                     << " with capital " << m[s1]
                     << " has been renamed to " << s2 << endl;
                m[s2] = m[s1];
                m.erase(s1);
            } else {
                cout << "Incorrect rename, skip" << endl;
            }*/
            if (s1 == s2 || m.count(s1) == 0 || m.count(s2) == 1) {
                cout << "Incorrect rename, skip" << endl;
            } else {
                cout << "Country " << s1
                     << " with capital " << m[s1]
                     << " has been renamed to " << s2 << endl;
                m[s2] = m[s1];
                m.erase(s1);
            }

        } else if (com == "ABOUT") {
            cin >> s1;
            if (m.count(s1) != 0) {
                cout << "Country " << s1
                     << " has capital " << m[s1] << endl;
            } else {
                cout << "Country " << s1
                     << " doesn't exist" << endl;
            }
        } else if (com == "DUMP") {
            if (m.size() == 0) {
                cout << "There are no countries in the world" << endl;
            } else {
                for (const auto& [k, v] : m) {
                    cout << k << '/' << v << ' ';
                }
                cout << endl;
            }
        }
    }
}