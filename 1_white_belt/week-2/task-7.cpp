#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    string com;
    int k;
    vector<bool> v;
    for (int i = 0; i < n; i++) {
        cin >> com;
        if (com == "WORRY") {
            cin >> k;
            v[k] = true;
        } else if (com == "QUIET") {
            cin >> k;
            v[k] = false;
        } else if (com == "COME") {
            cin >> k;
            if (k > 0) {
                for (int i = 0; i < k; i++) {
                    v.push_back(false);
                }
            } else {
                v.erase(v.end() + k, v.end());
            }
        } else if (com == "WORRY_COUNT") {
            int j = 0;
            for (bool m : v)
                if (m)
                    j++;
            cout << j << endl;
        }
    }
}