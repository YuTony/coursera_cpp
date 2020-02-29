#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    set<string> s;
    string w;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w;
        s.insert(w);
    }
    cout << s.size();
    return 0;
}