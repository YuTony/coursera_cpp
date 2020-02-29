#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, vector<int> v) {
    bool start = true;
    for (int x : v) {
        if (!start) cout << " ";
        start = false;
        cout << x;
    }
    return os;
}

int main() {
    int n;
    cin >> n;
    vector<int> ans(n);
    for (int i = n; i >= 1; i--) {
        ans[n - i] = i;
    }
    do {
        cout << ans << endl;
    } while (prev_permutation(ans.begin(), ans.end()));
}