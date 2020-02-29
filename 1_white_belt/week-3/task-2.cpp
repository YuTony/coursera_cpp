#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<string> v;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        v.push_back(t);
    }
    sort(v.begin(), v.end(),
         [](string x1, string x2) {
             for (int j = 0; j < (x2.size() > x1.size() ? x1.size() : x2.size()); j++) {
                 if (tolower(x1[j]) < tolower(x2[j]))
                     return true;
                 if (tolower(x1[j]) > tolower(x2[j]))
                     return false;
             }
             return false;
         });
    for (const string& t : v) {
        cout << t << ' ';
    }
}