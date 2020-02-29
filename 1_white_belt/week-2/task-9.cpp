#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        map<char, int> m1, m2;
        cin >> s;
        for (char c : s) {
            m1[c]++;
        }
        cin >> s;
        for (char c : s) {
            m2[c]++;
        }
        cout << (m1 == m2 ? "YES" : "NO") << endl;
    }
    return 0;
}