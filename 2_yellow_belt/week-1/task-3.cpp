#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, r;
    cin >> n >> r;
    uint64_t m = 0;
    for (int i = 0; i < n; i++) {
        int w, h, d;
        cin >> w >> h >> d;
        m += w * h * d * r;
    }
    cout << m << endl;
}