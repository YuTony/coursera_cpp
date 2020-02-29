#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    int64_t average = 0;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        average += v[i];
    }
    average /= n;

    int k = 0;
    for (int i : v) {
        if (i > average) k++;
    }

    cout << k << endl;
    for (int i = 0; i < n; i++) {
        if (v[i] > average) cout << i << ' ';
    }
}