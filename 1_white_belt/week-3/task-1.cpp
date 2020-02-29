#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        v.push_back(t);
    }
    sort(v.begin(), v.end(),
         [](int x1, int x2) {
             return (abs(x1) < abs(x2));
         });
    for (const int& t : v) {
        cout << t << ' ';
    }
}