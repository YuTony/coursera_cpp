#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int> v) {
    auto it = find_if(v.begin(), v.end(), [](const int &x) {
        return (x < 0);
    });
    if (it != v.begin()) {
        it--;
        for (; it >= v.begin(); it--) {
            cout << *it << ' ';
        }
    }
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}